# Client-Server Communication Project

## Project Overview

This project consists of a client-side and a server-side application designed for secure client-server communication. The server handles client connections, processes various types of requests, and ensures secure data transfer. The client interacts with the server to perform tasks like file transfer, client registration, public key exchange, and more.

## Client-Side Application

The client-side application handles creating various requests to communicate with the server. It includes functionalities like file transfer, client registration, public key handling, and more.

### Features

- File Transfer
- Client Reconnection
- Public Key Handling
- Client Registration
- Checksum Verification

For detailed information, refer to the [Client README](./Client/README.md).

## Server-Side Application

The server-side application manages client connections and processes requests securely. It handles tasks such as file transfer, public key updates, client registration, and checksum verification.

### Features

- File Transfer
- Client Reconnection
- Public Key Handling
- Client Registration
- Checksum Verification

For detailed information, refer to the [Server README](./Server/README.md).

## How to Run the Applications

### Prerequisites

- Python 3.x
- Necessary Python libraries (listed in the dependencies section)

### Running the Server

1. Navigate to the `Server` directory.
2. Install the required dependencies: `pip install -r requirements.txt`.
3. Run the server: `python server.py`.

### Running the Client

1. Navigate to the `Client` directory.
2. Install the required dependencies: `pip install -r requirements.txt`.
3. Run the client: `python client.py`.

## Dependencies

Both applications require Python 3.x and the following Python libraries:

- `socket`
- `sqlite3`
- `threading`
- `rsa`
- `pycryptodome`
- `logging`

Install the dependencies using:

```bash
pip install -r requirements.txt
```
