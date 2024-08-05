# This module, 'client_handler.py', manages the interactions with clients connected to the server.
# It includes functionalities for processing various client requests such as registration,
# public key handling, file transfer, and reconnection. It also handles checksum verification,
# generating and sending AES keys, and sending responses back to the client.

import os
import logging
import socket
import uuid
from Crypto.PublicKey import RSA
from Crypto.Cipher import AES, PKCS1_OAEP
from utils import *

reconnection_attempts = {}
BUFFER_SIZE = 1024
CONNECTION_CLOSED_MESSAGE = 'Server encountered an error.'
CLIENT_CONNECTION_CLOSED_LOG = "Client connection closed."

logging.basicConfig(filename='server.log', level=logging.INFO,
                    format='%(asctime)s - %(levelname)s - %(message)s')


def handle_client_connection(client_socket):
    """Handle the individual client connection. Processes incoming data and routes to the appropriate function."""
    try:
        while True:
            data = client_socket.recv(BUFFER_SIZE)
            if not data:
                break

            try:
                request_type, request_data = parse_client_request(data)
            except ValueError as e:
                logging.error(f"Error parsing client request: {e}")
                continue  # Skip to the next iteration

            # Handling different request types
            if request_type == 'file_transfer':
                process_file_transfer_request(client_socket, request_data)
            elif request_type == 'reconnect':
                process_reconnect_request(client_socket, request_data)
            elif request_type == 'checksum_verification':
                process_checksum_verification(client_socket, request_data)
            elif request_type == 'registration':
                process_registration_request(client_socket, request_data)
            elif request_type == 'public_key':
                process_public_key_request(client_socket, request_data)
            else:
                logging.warning(f"Unknown request type: {request_type}")

    except socket.error as e:
        logging.error(f"Socket error: {e}")
        send_response(client_socket, CONNECTION_CLOSED_MESSAGE)
    except Exception as e:
        logging.error(f"Unexpected error: {e}")
        send_response(client_socket, CONNECTION_CLOSED_MESSAGE)
    finally:
        client_socket.close()
        logging.info(CLIENT_CONNECTION_CLOSED_LOG)


def process_file_transfer_request(client_socket, request):
    """
    Handle file transfer requests from the client. Decrypts and stores the received file.
    """
    try:
        encrypted_file_data = request.get('file_data')
        client_id = request.get('client_id')

        # Validate the presence of necessary data
        if not all([encrypted_file_data, client_id]):
            logging.error("Missing data in file transfer request")
            send_response(client_socket, 'Incomplete request data.')
            return

        # Retrieve the AES key for this client from the database
        aes_key = get_aes_key_for_client(client_id)
        if aes_key is None:
            send_response(client_socket, 'AES key not found.')
            return

        try:
            # Decrypt the file data using the AES key
            decrypted_file_data = decrypt_message_with_aes(
                encrypted_file_data, aes_key)
        except Exception as e:
            logging.error(f"Error decrypting file data: {e}")
            send_response(client_socket, 'Error in file decryption.')
            return

        checksum = request.get('checksum')
        if not checksum:
            logging.error("Missing checksum in file transfer request")
            send_response(client_socket, 'Checksum not provided.')
            return

        if verify_checksum(decrypted_file_data, checksum):
            file_id = uuid.uuid4().bytes
            filename = f"{uuid.uuid4()}.txt"  # Generating a unique filename
            file_path = f"stored_files/{filename}"

            # Check and create 'stored_files' directory if necessary
            if not os.path.exists('stored_files'):
                os.makedirs('stored_files')

            with open(file_path, 'wb') as file:
                file.write(decrypted_file_data)

            file_info = (file_id, client_id, filename, file_path, True)
            store_received_file(file_info)
            send_response(client_socket, 'File received and verified.')
        else:
            send_response(client_socket, 'File checksum mismatch.')

    except KeyError as e:
        logging.error(f"Key error in file transfer request: {e}")
        send_response(client_socket, "Invalid request format.")
    except Exception as e:
        logging.error(f"Unexpected error in file transfer request: {e}")
        send_response(client_socket, "Server encountered an unexpected error.")


def process_reconnect_request(client_socket, data):
    """
    Handles reconnection requests from clients.
    """
    try:
        client_id = data
        if not client_id:
            logging.error("Missing client ID in reconnection request")
            send_response(client_socket, 'Client ID not provided.')
            return

        # Initialize or update reconnection attempts
        reconnection_attempts.setdefault(client_id, 0)
        reconnection_attempts[client_id] += 1

        # Define a maximum reconnection attempt limit
        MAX_RECONNECTION_ATTEMPTS = 3

        if reconnection_attempts[client_id] > MAX_RECONNECTION_ATTEMPTS:
            send_response(client_socket, "Reconnection limit exceeded")
            logging.warning(
                f"Client {client_id} exceeded reconnection attempts.")
            del reconnection_attempts[client_id]  # Reset the count
            return

        try:
            client_info = get_client_info(client_id)
            if client_info:
                update_last_seen(client_id)
                send_response(client_socket, "Reconnection successful")
                logging.info(f"Client {client_id} reconnected successfully.")
            else:
                send_response(client_socket, "Client not recognized")
                logging.warning(
                    f"Unrecognized client attempted to reconnect: {client_id}")
        except Exception as e:
            logging.error(f"Error during reconnection process: {e}")
            send_response(client_socket, "Error in reconnection process.")

        # Reset the count after successful reconnection
        del reconnection_attempts[client_id]

    except KeyError as e:
        logging.error(f"Key error in reconnection request: {e}")
        send_response(client_socket, "Invalid reconnection format.")
    except Exception as e:
        logging.error(f"Unexpected error in reconnection request: {e}")
        send_response(client_socket, "Server encountered an unexpected error.")


def process_public_key_request(client_socket, data):
    """
    Processes public key update requests from clients and sends back an encrypted AES key.
    """
    try:
        try:
            client_id, public_key = data.split(',')

            if not client_id or not public_key:
                raise ValueError("Client ID or public key missing in request.")

            # Update client's public key in the database
            update_client_public_key(client_id, public_key)

            # Generate a random AES key
            aes_key = os.urandom(16)  # 16 bytes for AES-128

            # Encrypt the AES key with the client's public key
            rsa_key = RSA.import_key(public_key)
            cipher = PKCS1_OAEP.new(rsa_key)
            encrypted_aes_key = cipher.encrypt(aes_key)

            # Store the AES key in the database
            update_aes_key_for_client(client_id, aes_key)

            # Send the encrypted AES key back to the client
            send_response(client_socket, encrypted_aes_key)
            logging.info(f"Encrypted AES key sent to client {client_id}")

        except ValueError as e:
            logging.error(f"Data format error in public key request: {e}")
            send_response(client_socket, "Invalid public key request format.")
        except Exception as e:
            logging.error(f"Error processing public key request: {e}")
            send_response(
                client_socket, "Error processing public key request.")

    except Exception as general_e:
        logging.error(f"Unexpected error in public key request: {general_e}")
        send_response(client_socket, "Server encountered an unexpected error.")


def process_checksum_verification(client_socket, data):
    """
    Verifies the checksum of a file received from a client.
    """
    try:
        try:
            client_id, file_name, client_checksum = data.split(',')

            if not client_id or not file_name or not client_checksum:
                raise ValueError(
                    "Missing client ID, file name, or checksum in request.")

            # Fetch file data from the database
            file_data = get_file_data(client_id, file_name)

            if file_data:
                # Calculate the checksum of the retrieved file data
                calculated_checksum = crc32(file_data)

                # Compare the calculated checksum with the client's checksum
                if str(calculated_checksum) == client_checksum:
                    send_response(
                        client_socket, "Checksum verification successful")
                else:
                    send_response(
                        client_socket, "Checksum verification failed")
            else:
                # Handle case where file data is not found
                send_response(client_socket, "File data not found")

        except ValueError as e:
            logging.error(f"Data format error in checksum verification: {e}")
            send_response(
                client_socket, "Invalid checksum verification format.")
        except Exception as e:
            logging.error(f"Error processing checksum verification: {e}")
            send_response(
                client_socket, "Error processing checksum verification.")

    except Exception as general_e:
        logging.error(
            f"Unexpected error in checksum verification: {general_e}")
        send_response(client_socket, "Server encountered an unexpected error.")


def process_registration_request(client_socket, data):
    """
    Processes registration requests from clients.
    """
    try:
        try:
            client_id, username, public_key = data.split(',')

            if not client_id or not username or not public_key:
                raise ValueError(
                    "Missing client ID, username, or public key in request.")

            # Add new client to the database
            add_new_client((client_id, username, public_key))
            send_response(client_socket, "Registration successful")

        except ValueError as e:
            logging.error(f"Data format error in registration request: {e}")
            send_response(
                client_socket, "Invalid registration request format.")
        except sqlite3.IntegrityError:
            # Handle the case where the client_id already exists in the database
            send_response(client_socket, "Client ID already registered.")
        except Exception as e:
            logging.error(f"Error processing registration request: {e}")
            send_response(
                client_socket, "Error processing registration request.")

    except Exception as general_e:
        logging.error(f"Unexpected error in registration process: {general_e}")
        send_response(client_socket, "Server encountered an unexpected error.")
