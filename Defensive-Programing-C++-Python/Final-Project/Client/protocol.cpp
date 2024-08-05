// The Protocol class is responsible for creating various types of requests 
// according to the specified communication protocol between the client and server.
// It includes methods for constructing registration requests, public key requests,
// file transfer requests, checksum verification requests, and reconnection requests.

#include "protocol.h"
#include "crypto_manager.h"
#include "crc.h"
#include <vector>
#include <cstring>
#include <rsa.h>
#include <secblock.h>
#include <iostream>

Protocol::Protocol(const std::string& id) {
    if (id.empty()) {
        throw std::invalid_argument("Client ID cannot be empty.");
    }
    clientID = id;
}


// Converts an integer to bytes in little-endian format.
std::vector<char> intToBytes(int value, size_t size) {
    if (size > sizeof(int)) {
        throw std::invalid_argument("Size exceeds the byte size of int");
    }

    std::vector<char> bytes(size);
    for (size_t i = 0; i < size; ++i) {
        bytes[i] = (value >> (i * 8)) & 0xFF;
    }
    return bytes;
}

// Helper function to create a header for a request
std::vector<char> createHeader(const std::string& clientID, uint8_t version, uint16_t code, size_t payloadSize) {
    // Define maximum client ID length and payload size
    const size_t maxClientIDLength = 128;  // Example length
    const size_t maxPayloadSize = 1024 * 1024; // 1 MB, for example

    // Check client ID length
    if (clientID.length() > maxClientIDLength) {
        throw std::invalid_argument("Invalid client ID length");
    }

    // Check payload size
    if (payloadSize > maxPayloadSize) {
        throw std::invalid_argument("Payload size exceeds maximum allowed limit");
    }

    std::vector<char> header;
    header.insert(header.end(), clientID.begin(), clientID.end());
    header.push_back(version);
    auto codeBytes = intToBytes(code, 2);
    header.insert(header.end(), codeBytes.begin(), codeBytes.end());
    auto sizeBytes = intToBytes(static_cast<int>(payloadSize), 4);
    header.insert(header.end(), sizeBytes.begin(), sizeBytes.end());

    return header;
}

std::vector<char> Protocol::create_registration_request(const std::string& username, const std::string& publicKey) const {
    // Ensure username is within the specified length
    if (username.length() > 255) {
        throw std::invalid_argument("Username exceeds maximum length of 255 bytes.");
    }

    // Ensure public key is exactly 160 bytes
    if (publicKey.length() < 160) {
        throw std::invalid_argument("Public key must be exactly 160 bytes.");
    }

    // Prepare request payload
    std::vector<char> requestPayload;
    requestPayload.insert(requestPayload.end(), username.begin(), username.end());
    requestPayload.push_back('\0'); // Null-terminated username
    requestPayload.insert(requestPayload.end(), publicKey.begin(), publicKey.end());

    // Create the header
    std::vector<char> requestHeader = createHeader(this->clientID, 1, 1026, requestPayload.size());

    // Combine header and payload
    std::vector<char> request;
    request.insert(request.end(), requestHeader.begin(), requestHeader.end());
    request.insert(request.end(), requestPayload.begin(), requestPayload.end());

    return request;
}

// Creates a public key request with the provided RSA public key.
std::vector<char> Protocol::create_public_key_request(const CryptoPP::RSA::PublicKey& publicKey) {
    // Validate that the public key is not empty
    if (publicKey.GetModulus().BitCount() == 0) {
        std::cerr << "Public key is empty or invalid." << std::endl;
        throw std::invalid_argument("Invalid public key provided.");
    }

    // Convert the public key to a string representation
    CryptoManager cryptoManager;
    std::string publicKeyString = cryptoManager.publicKeyToString(publicKey);

    // Ensure the public key string is of the required length
    if (publicKeyString.size() < 160) {
        throw std::runtime_error("Public key must be exactly 160 bytes.");
    }

    // Create a header for the public key request
    std::vector<char> request;
    request = createHeader(this->clientID, 1, 1026, publicKeyString.length());
    request.insert(request.end(), publicKeyString.begin(), publicKeyString.end());

    return request;
}

// Creates a file transfer request with encrypted file data and CRC checksum.
std::vector<char> Protocol::create_file_transfer_request(const std::string& filename, const std::vector<char>& fileData) {
    // Validate that the file data is not empty
    if (fileData.empty()) {
        std::cerr << "File data is empty." << std::endl;
        throw std::invalid_argument("File data cannot be empty.");
    }

    // Validate that the filename is not empty
    if (filename.empty()) {
        std::cerr << "Filename is empty." << std::endl;
        throw std::invalid_argument("Filename cannot be empty.");
    }

    // Encrypt the file data
    std::vector<char> encryptedData;
    try {
        CryptoManager cryptoManager;
        encryptedData = cryptoManager.encrypt_with_aes(fileData, cryptoManager.getAESKey(), cryptoManager.getAESIV());
    }
    catch (const std::exception& e) {
        std::cerr << "Error encrypting file data: " << e.what() << std::endl;
        throw;
    }

    // Calculate CRC of encrypted data
    uint32_t crc;
    try {
        crc = crc32(std::vector<uint8_t>(encryptedData.begin(), encryptedData.end()));
    }
    catch (const std::exception& e) {
        std::cerr << "Error calculating CRC: " << e.what() << std::endl;
        throw; 
    }

    // Prepare the request payload
    std::vector<char> request;
    try {
        size_t payloadSize = 4 + filename.length() + encryptedData.size() + 4;  // File size + filename + data + CRC
        request = createHeader(clientID, 1, 1028, payloadSize);

        // Add file size
        auto fileSizeBytes = intToBytes(static_cast<int>(encryptedData.size()), 4);
        request.insert(request.end(), fileSizeBytes.begin(), fileSizeBytes.end());

        // Add filename
        request.insert(request.end(), filename.begin(), filename.end());

        // Add encrypted file data
        request.insert(request.end(), encryptedData.begin(), encryptedData.end());

        // Add CRC
        auto crcBytes = intToBytes(crc, 4);
        request.insert(request.end(), crcBytes.begin(), crcBytes.end());
    }
    catch (const std::exception& e) {
        std::cerr << "Error creating file transfer request: " << e.what() << std::endl;
        throw; 
    }

    return request;
}

// Create a checksum verification request.
std::vector<char> Protocol::create_checksum_verification_request(const std::string& file_name, const std::string& checksum) {
    // Validate the input parameters
    if (file_name.empty()) {
        std::cerr << "File name cannot be empty for checksum verification request." << std::endl;
        throw std::invalid_argument("File name cannot be empty.");
    }
    if (checksum.empty()) {
        std::cerr << "Checksum cannot be empty for checksum verification request." << std::endl;
        throw std::invalid_argument("Checksum cannot be empty.");
    }

    // Calculate the total payload size
    size_t payloadSize = file_name.length() + checksum.length();

    // Create the request header
    std::vector<char> request = createHeader(clientID, 1, 1029, payloadSize);

    // Append file name and checksum to the request
    request.insert(request.end(), file_name.begin(), file_name.end());
    request.insert(request.end(), checksum.begin(), checksum.end());

    return request;
}

// Generates a reconnection request with the current client ID.
std::vector<char> Protocol::create_reconnection_request() {
    // Validate the clientID
    if (this->clientID.empty()) {
        std::cerr << "Client ID cannot be empty for reconnection request." << std::endl;
        throw std::invalid_argument("Client ID cannot be empty.");
    }

    std::vector<char> request = createHeader(this->clientID, 1, 1031, 0);

    return request;
}
