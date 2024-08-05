# This script is the main entry point for the server application. It sets up the server,
# listens for incoming client connections, and creates new threads to handle these
# connections concurrently. The server's core functionalities are handled in other modules,
# such as 'client_handler' and 'utils'.

import threading
import socket
import logging
from client_handler import handle_client_connection
from database import initialize_database
from utils import read_port_info

# Set up basic logging
logging.basicConfig(filename='server.log', level=logging.INFO,
                    format='%(asctime)s - %(levelname)s - %(message)s')

# Create a console handler and set its level to INFO
console_handler = logging.StreamHandler()
console_handler.setLevel(logging.INFO)

# Create a logging format
formatter = logging.Formatter('%(asctime)s - %(levelname)s - %(message)s')
console_handler.setFormatter(formatter)

# Add the console handler to the root logger
logging.getLogger().addHandler(console_handler)


def main():
    """Main function to set up and run the server."""
    # Initialize the database
    initialize_database()

    # Read the server port from the configuration file or use the default port
    server_port = read_port_info()

    # Set up server socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        server_socket.bind(('', server_port))
        server_socket.listen(5)
        logging.info(f"Server listening on port {server_port}")
    except socket.error as e:
        logging.error(f"Socket error: {e}")
        return

    # Listen for incoming connections
    try:
        while True:
            try:
                client_socket, addr = server_socket.accept()
                logging.info(f"Connection from {addr}")
                threading.Thread(target=handle_client_connection,
                                 args=(client_socket,)).start()
            except socket.error as e:
                logging.error(f"Error accepting connection: {e}")
    except KeyboardInterrupt:
        logging.info("Server shutdown initiated by user.")
    finally:
        server_socket.close()
        logging.info("Server successfully shut down.")


if __name__ == "__main__":
    main()
