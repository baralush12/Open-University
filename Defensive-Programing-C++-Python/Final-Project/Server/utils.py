#   This script contains a collection of utility functions designed to support various operations
#   within the server application. It includes functions for reading server configuration,
#   logging events, generating unique identifiers (UUIDs), encrypting and decrypting messages,
#   and computing CRC32 checksums. The script ensures modular and reusable code, aiding in
#   maintaining and scaling the server application.

import os
from Crypto.Cipher import AES, PKCS1_OAEP
from Crypto.PublicKey import RSA
import logging
import binascii
from database import *

DEFAULT_PORT = 1357


def log_event(event_info):
    """
    Logs an event with the given information.
    Args:
    event_info (str): Information or message to log.
    """
    logging.info(event_info)


def read_port_info():
    """Read the server port from the port.info file."""
    try:
        with open('port.info', 'r') as file:
            port = int(file.read().strip())
            if 1 <= port <= 65535:
                return port
            else:
                raise ValueError(f"Invalid port number in port.info: {port}")
    except FileNotFoundError:
        logging.warning(
            f"port.info file not found. Using default port: {DEFAULT_PORT}.")
        return DEFAULT_PORT
    except ValueError as e:
        logging.error(f"{e} Using default port: {DEFAULT_PORT}.")
        return DEFAULT_PORT


def decrypt_message_with_aes(encrypted_message, key):
    """Decrypts an AES encrypted message."""
    try:
        # Validate input types
        if not isinstance(encrypted_message, bytes) or not isinstance(key, bytes):
            raise ValueError("Inputs must be of type 'bytes'.")

        # Check key length
        if len(key) not in [16, 24, 32]:  # Corresponds to 128, 192, 256 bits
            raise ValueError("Invalid AES key length.")

        # Extract IV and check length
        iv = encrypted_message[:AES.block_size]
        if len(iv) != AES.block_size:
            raise ValueError("Invalid IV length.")

        # Decrypt the message
        cipher = AES.new(key, AES.MODE_CBC, iv)
        decrypted_message = cipher.decrypt(encrypted_message[AES.block_size:])
        padding_length = decrypted_message[-1]

        # Validate padding
        if padding_length < 1 or padding_length > AES.block_size:
            raise ValueError("Invalid padding in decrypted message.")

        return decrypted_message[:-padding_length]

    except Exception as e:
        logging.error(f"AES decryption error: {e}")
        return None


def rsa_encrypt(message, public_key):
    """Encrypts a message using RSA encryption with a given public key."""
    try:
        # Validate input type for message
        if not isinstance(message, bytes):
            raise ValueError("Message must be of type 'bytes'.")

        # Import the public key
        rsa_key = RSA.import_key(public_key)

        if rsa_key.size_in_bits() < 2048:
            logging.warning("RSA key size is less than 2048 bits.")

        # Encrypt the message
        cipher = PKCS1_OAEP.new(rsa_key)
        return cipher.encrypt(message)

    except Exception as e:
        logging.error(f"RSA encryption error: {e}")
        return None  # or raise the exception, depending on how you want to handle errors


def crc32(data):
    """Calculates the CRC32 checksum for the given data."""
    return binascii.crc32(data) & 0xFFFFFFFF


def send_response(client_socket, message):
    """
    Send a response to the client, including any necessary data and status codes.
    """
    client_socket.sendall(message.encode())


def verify_checksum(data, checksum):
    """
    Verify the checksum of the received file to ensure data integrity.
    """
    calculated_checksum = crc32(data)
    return calculated_checksum == checksum


def generate_and_send_aes_key(client_socket, client_id):
    # Fetch the public key from the database
    public_key = get_client_public_key(client_id)

    # Check if the public key is available
    if not public_key:
        logging.error(f"Public key not found for client {client_id}")
        send_response(client_socket, "Error: Public key not found.")
        return

    try:
        # Generate a random AES key
        aes_key = os.urandom(16)  # 16 bytes for AES-128

        # Encrypt the AES key with the public key
        encrypted_aes_key = rsa_encrypt(aes_key, public_key)

        # Send the encrypted AES key back to the client
        send_response(client_socket, encrypted_aes_key)
        logging.info(f"Encrypted AES key sent to client {client_id}")

    except Exception as e:
        logging.error(
            f"Error in generating/sending AES key for client {client_id}: {e}")
        send_response(
            client_socket, "Error: Unable to generate or send AES key.")


def calculate_file_checksum(file_data):
    """Calculate the checksum of the given file data."""
    if file_data is None:
        logging.error("No file data provided for checksum calculation.")
        return None

    if not isinstance(file_data, bytes):
        logging.error(
            "Invalid file data type for checksum calculation. Expected bytes.")
        return None

    try:
        return crc32(file_data) & 0xFFFFFFFF
    except Exception as e:
        logging.error(f"Error calculating checksum: {e}")
        return None


def verify_client_checksum(client_id, client_checksum):
    """
    Verify the checksum received from the client against the server-calculated checksum.
    """
    if client_id is None or client_checksum is None:
        logging.error("Invalid client ID or checksum provided.")
        return False

    file_data = get_file_data_for_client(client_id)
    if file_data is None:
        logging.error(f"No file data found for client ID {client_id}.")
        return False

    calculated_checksum = calculate_file_checksum(file_data)
    if calculated_checksum is None:
        logging.error("Checksum calculation failed.")
        return False

    return str(calculated_checksum) == str(client_checksum)


# Parse the incoming data from the client and determine the type of request.
# Return the request type and the processed data.
def parse_client_request(data):
    """
    Parse the incoming client request data.
    """
    if not data:
        logging.error("Received empty data for client request.")
        return None, None

    if len(data) < 2:
        logging.error(f"Invalid client request data format: {data}")
        return None, None

    request_type = data[0]
    request_data = data[1:]

    logging.info(f"Request type: {request_type}, Request data: {request_data}")
    return request_type, request_data
