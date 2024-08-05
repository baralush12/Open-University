"""
This module, 'database.py', manages interactions with the SQLite database for the defensive server application.
It handles the creation and management of tables for storing client and file information, providing
CRUD (Create, Read, Update, Delete) operations. This includes functions for adding new clients, updating client
details, storing received file data, and maintaining the integrity and accuracy of stored data.
"""

import logging
import sqlite3
from datetime import datetime

DATABASE_PATH = 'defensive.db'


def initialize_database():
    """Initialize the SQLite database and create tables if they don't exist."""
    try:
        with sqlite3.connect(DATABASE_PATH) as conn:
            cursor = conn.cursor()

            # Create the clients table
            cursor.execute('''
                CREATE TABLE IF NOT EXISTS clients (
                    id BLOB PRIMARY KEY,
                    name TEXT,
                    public_key BLOB,
                    last_seen TIMESTAMP,
                    aes_key BLOB
                )
            ''')

            # Create the files table
            cursor.execute('''
                CREATE TABLE IF NOT EXISTS files (
                    id BLOB PRIMARY KEY,
                    client_id BLOB,
                    file_name TEXT,
                    path_name TEXT,
                    verified BOOLEAN,
                    FOREIGN KEY (client_id) REFERENCES clients (id)
                )
            ''')

            conn.commit()
            logging.info("Database initialized successfully.")

    except sqlite3.Error as e:
        logging.error(f"Database initialization failed: {e}")


def add_new_client(client_info):
    """Add a new client to the database."""
    if not isinstance(client_info, tuple) or len(client_info) < 3:
        logging.error(
            "Invalid client_info format. Expected a tuple with at least three elements.")
        return

    try:
        with sqlite3.connect(DATABASE_PATH) as conn:
            cursor = conn.cursor()
            # Assuming client_info is a tuple: (id, name, public_key)
            cursor.execute(
                'INSERT INTO clients (id, name, public_key, last_seen, aes_key) VALUES (?, ?, ?, ?, ?)',
                (client_info[0], client_info[1],
                 client_info[2], datetime.now(), None)
            )
            conn.commit()
            logging.info(f"New client {client_info[1]} added successfully.")

    except sqlite3.IntegrityError:
        logging.error(f"Client with ID {client_info[0]} already exists.")
    except sqlite3.Error as e:
        logging.error(f"Error adding new client: {e}")


def get_client_info(client_id):
    """Retrieve a client's information from the database using their client ID."""
    if not client_id:
        logging.error("Client ID is required to retrieve client information.")
        return None

    try:
        with sqlite3.connect(DATABASE_PATH) as conn:
            cursor = conn.cursor()
            cursor.execute('SELECT * FROM clients WHERE id = ?', (client_id,))
            client_info = cursor.fetchone()

            if client_info:
                logging.info(
                    f"Client info retrieved for client ID: {client_id}")
                return client_info
            else:
                logging.warning(f"No client found with ID: {client_id}")
                return None
    except sqlite3.Error as e:
        logging.error(f"Database error while retrieving client info: {e}")
        return None


def update_client_public_key(client_id, public_key):
    """Update the public key of an existing client in the database."""
    if not client_id or not public_key:
        logging.error("Client ID and Public Key are required for updating.")
        return False

    try:
        with sqlite3.connect(DATABASE_PATH) as conn:
            cursor = conn.cursor()
            cursor.execute('UPDATE clients SET public_key = ? WHERE id = ?',
                           (public_key, client_id))
            conn.commit()
            if cursor.rowcount == 0:
                logging.warning(
                    f"No client updated. Client ID {client_id} not found.")
                return False
            logging.info(f"Public key updated for client ID: {client_id}")
            return True
    except sqlite3.Error as e:
        logging.error(f"Database error while updating public key: {e}")
        return False


def update_file_verification_status(file_id, status):
    """Update the verification status of a stored file in the database."""
    if file_id is None or status is None:
        logging.error("File ID and status are required for updating.")
        return False

    try:
        with sqlite3.connect(DATABASE_PATH) as conn:
            cursor = conn.cursor()
            cursor.execute('UPDATE files SET verified = ? WHERE id = ?',
                           (status, file_id))
            conn.commit()
            if cursor.rowcount == 0:
                logging.warning(
                    f"No file record updated. File ID {file_id} not found.")
                return False
            logging.info(f"Verification status updated for file ID: {file_id}")
            return True
    except sqlite3.Error as e:
        logging.error(
            f"Database error while updating file verification status: {e}")
        return False


def get_aes_key_for_client(client_id):
    """
    Retrieve the AES key for a specific client from the database.
    """
    if client_id is None:
        logging.error("Client ID is required to retrieve AES key.")
        return None

    try:
        with sqlite3.connect(DATABASE_PATH) as conn:
            cursor = conn.cursor()
            cursor.execute(
                "SELECT aes_key FROM clients WHERE id = ?", (client_id,))
            result = cursor.fetchone()
            if result:
                logging.info(f"AES key retrieved for client ID: {client_id}")
                return result[0]
            else:
                logging.warning(f"No AES key found for client ID: {client_id}")
                return None
    except sqlite3.Error as e:
        logging.error(f"Database error while retrieving AES key: {e}")
        return None


def get_client_public_key(client_id):
    """
    Retrieve a client's public key from the database using their client ID.
    """
    if client_id is None:
        logging.error("Client ID is required to retrieve the public key.")
        return None

    try:
        with sqlite3.connect(DATABASE_PATH) as conn:
            cursor = conn.cursor()
            cursor.execute(
                'SELECT public_key FROM clients WHERE id = ?', (client_id,))
            result = cursor.fetchone()
            if result:
                logging.info(
                    f"Public key retrieved for client ID: {client_id}")
                return result[0]
            else:
                logging.warning(
                    f"No public key found for client ID: {client_id}")
                return None
    except sqlite3.Error as e:
        logging.error(f"Database error while retrieving public key: {e}")
        return None


def get_file_data_for_client(client_id):
    """
    Retrieve file data for a specific client from the database.
    """
    if client_id is None:
        logging.error("Client ID is required to retrieve file data.")
        return None

    try:
        with sqlite3.connect(DATABASE_PATH) as conn:
            cursor = conn.cursor()
            cursor.execute(
                'SELECT * FROM files WHERE client_id = ?', (client_id,))
            result = cursor.fetchall()
            if result:
                logging.info(f"File data retrieved for client ID: {client_id}")
                return result
            else:
                logging.warning(
                    f"No file data found for client ID: {client_id}")
                return []
    except sqlite3.Error as e:
        logging.error(f"Database error while retrieving file data: {e}")
        return None


def get_file_data(client_id, file_name):
    """
    Retrieve specific file data associated with a client.
    """
    if not client_id or not file_name:
        logging.error(
            "Both client_id and file_name are required to retrieve file data.")
        return None

    try:
        with sqlite3.connect(DATABASE_PATH) as conn:
            cursor = conn.cursor()
            query = "SELECT * FROM files WHERE client_id = ? AND file_name = ?"
            cursor.execute(query, (client_id, file_name))
            file_data = cursor.fetchone()
            if file_data:
                logging.info(
                    f"File data retrieved for client ID: {client_id}, File Name: {file_name}")
                return file_data
            else:
                logging.warning(
                    f"No file data found for client ID: {client_id}, File Name: {file_name}")
                return None
    except sqlite3.Error as e:
        logging.error(f"Database error while retrieving file data: {e}")
        return None


def update_last_seen(client_id):
    """
    Updates the 'last_seen' timestamp for a given client in the database.
    """
    if not client_id:
        logging.error(
            "Client ID is required to update the last seen timestamp.")
        return False

    try:
        with sqlite3.connect(DATABASE_PATH) as conn:
            cursor = conn.cursor()
            current_time = datetime.now()
            cursor.execute(
                'UPDATE clients SET last_seen = ? WHERE id = ?', (current_time, client_id))
            conn.commit()
            logging.info(
                f"Last seen timestamp updated for client ID: {client_id}")
            return True
    except sqlite3.Error as e:
        logging.error(
            f"Database error while updating last seen timestamp for client ID {client_id}: {e}")
        return False


def store_received_file(file_info):
    """
    Stores information about a file received from a client in the database.
    file_info is expected to be a tuple in the format: (id, client_id, file_name, path_name, verified)
    """
    if not file_info or not isinstance(file_info, tuple) or len(file_info) != 5:
        logging.error("Invalid file information provided for storage.")
        return False

    try:
        with sqlite3.connect(DATABASE_PATH) as conn:
            cursor = conn.cursor()
            cursor.execute('INSERT INTO files (id, client_id, file_name, path_name, verified) VALUES (?, ?, ?, ?, ?)',
                           file_info)
            conn.commit()
            logging.info(
                f"File information stored successfully for file ID: {file_info[0]}")
            return True
    except sqlite3.Error as e:
        logging.error(f"Database error while storing file information: {e}")
        return False


def update_aes_key_for_client(client_id, aes_key):
    """
    Updates the AES key for a given client in the database.
    """
    if not client_id or not aes_key:
        logging.error("Invalid client ID or AES key provided for update.")
        return False

    try:
        with sqlite3.connect(DATABASE_PATH) as conn:
            cursor = conn.cursor()
            cursor.execute(
                'UPDATE clients SET aes_key = ? WHERE id = ?', (aes_key, client_id))
            conn.commit()
            if cursor.rowcount == 0:
                logging.warning(
                    f"No client found with ID: {client_id} for AES key update.")
                return False
            logging.info(
                f"AES key updated successfully for client ID: {client_id}")
            return True
    except sqlite3.Error as e:
        logging.error(
            f"Database error during AES key update for client ID {client_id}: {e}")
        return False
