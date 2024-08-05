Server-Side Application for Client-Server Communication
This application acts as the server-side component of a client-server model. It handles client connections, processes various types of requests such as file transfer, public key handling, client registration, reconnection, and checksum verification.

Features
File Transfer: Handles encrypted file transfer requests from clients.
Client Reconnection: Manages reconnection attempts with error handling.
Public Key Handling: Processes public key update requests and sends back AES keys encrypted with the client's public key.
Client Registration: Handles new client registrations, storing their information in the database.
Checksum Verification: Verifies the integrity of transferred files through checksum verification.

Logging
The server logs events and errors to server.log. This includes information such as connection details, data processing steps, and error messages.

Database
The server uses an SQLite database (defensive.db) to store client information and file data. It contains two main tables: clients and files.

clients: Stores client ID, name, public key, last seen timestamp, and AES key.
files: Stores file ID, client ID, file name, path name, and verification status.
Security
The server uses RSA for public key encryption and AES for file data encryption.
It handles secure storage and retrieval of keys and implements basic error handling to manage unexpected scenarios.

Concurrency
The server can handle multiple client connections concurrently using Python's threading module.
