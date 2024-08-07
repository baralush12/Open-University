# Client Application README

## Overview

This document provides an overview of the classes and methods used in the client application. It is designed to help understand the functionalities and responsibilities of different parts of the application.

## 1. Protocol Class

The `Protocol` class is responsible for creating various types of requests in client-server communication, such as registration, public key exchange, file transfer, etc.

- **Protocol(const std::string& clientID)**: Constructor that initializes the protocol with a client ID.
- **create_registration_request(const std::string& username, const std::string& publicKey)**: Creates a registration request with a username and public key.
- **create_public_key_request(const std::string& publicKey)**: Creates a request for sending the public key to the server.
- **create_file_transfer_request(const std::string& filePath)**: Creates a request for transferring a file.
- **create_checksum_verification_request(const std::string& checksum)**: Creates a request to verify the checksum of a file.
- **create_reconnection_request()**: Generates a reconnection request.

## 2. NetworkManager Class

`NetworkManager` manages network communications, encapsulating details of network operations using the Winsock library.

- **NetworkManager(const std::string& serverIP, int serverPort)**: Constructor that initializes the network manager with server IP and port.
- **connect_to_server()**: Establishes a connection to the server.
- **close_connection()**: Closes the network connection.
- **send_data(const std::vector<char>& data)**: Sends data to the server.
- **receive_data()**: Receives data from the server.
- **connectAndRegister(const std::string& username, const std::string& publicKey)**: Connects and registers the client with the server.
- **create_registration_request(const std::string& username, const std::string& publicKey)**: Creates a registration request.

## 3. FileManager Class

`FileManager` manages file operations such as reading, writing, and sending files.

- **FileManager(const std::string& clientID)**: Constructor initializing the file manager with a client ID.
- **read_file(const std::string& filePath)**: Reads a file from a specified path.
- **write_file(const std::string& filePath, const std::vector<char>& data)**: Writes data to a file.
- **calculate_checksum(const std::vector<char>& data)**: Calculates the checksum of data.
- **save_client_info(const std::string& clientInfo)**: Saves client information.
- **read_transfer_info(const std::string& filePath)**: Reads transfer information from a file.
- **send_file(const std::string& filePath, const std::string& serverAddress)**: Sends a file to a specified server.
- **initializeMeFile(const std::string& clientInfo)**: Initializes a file with client information.

## 4. ErrorHandler Class

`ErrorHandler` handles errors and retry operations in the client application.

- **handle_error(const std::string& errorMessage)**: Handles an error given its message.
- **retry_operation()**: Retries a previously failed operation.

## 5. CryptoManager Class

`CryptoManager` handles cryptographic operations like AES and RSA encryption/decryption.

- **CryptoManager()**: Constructor initializing the crypto manager.
- **encrypt_with_aes(const std::vector<char>& data, const std::vector<char>& key, const std::vector<char>& iv)**: Encrypts data using AES.
- **decrypt_with_aes(const std::vector<char>& encryptedData, const std::vector<char>& key, const std::vector<char>& iv)**: Decrypts data using AES.
- **encrypt_with_rsa(const std::vector<char>& data, const std::string& publicKey)**: Encrypts data using RSA.
- **decrypt_with_rsa(const std::vector<char>& encryptedData, const std::string& privateKey)**: Decrypts data using RSA.
- **generate_rsa_private_key()**: Generates an RSA private key.
- **generate_rsa_public_key(const std::string& privateKey)**: Generates an RSA public key from a private key.
- **publicKeyToString(const std::string& publicKey)**: Converts an RSA public key to a string.
- **generateAESKey()**: Generates an AES key.
- **generateAESIV()**: Generates an AES IV.
- **getUUIDString()**: Returns the UUID string.
- **getPrivateKeyString()**: Returns the private key string.
- **getAESKey()**: Returns the AES key.
- **getAESIV()**: Returns the AES IV.

## 6. CRC Functions

The CRC functions are used for CRC (Cyclic Redundancy Check) calculations.

- **generate_crc_table()**: Generates a CRC lookup table.
- **crc32(const std::vector<char>& data)**: Calculates the CRC32 checksum of data.

## 7. ConfigManager Class

`ConfigManager` manages configuration settings of the client application.

- **ConfigManager(const std::string& configFilePath)**: Constructor initializing the config manager.
- **load_configuration()**: Loads configuration settings.
- **get_server_ip()**: Returns the server IP address.
- **get_server_port()**: Returns the server port.
- **get_client_name()**: Returns the client name.
- **get_file_path_to_send()**: Returns the file path for data transmission.

## 8. run_client_operations Function

This function orchestrates the main operations of the client, like connecting to the server, sending registration requests, and handling responses.

## 9. Main Function

The main function is the entry point of the application. It initializes necessary components and starts client operations.
