#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>
#include <vector>
#include "crypto_manager.h"

// The Protocol class defines the structure of various requests in the client-server communication.
// It provides methods to create different types of protocol-compliant requests, such as
// registration, public key exchange, file transfer, checksum verification, and reconnection.

class Protocol {
public:
    explicit Protocol(const std::string& clientID);
    std::vector<char> create_registration_request(const std::string& username, const std::string& publicKey) const;
    std::vector<char> create_public_key_request(const CryptoPP::RSA::PublicKey& publicKey);
    std::vector<char> create_file_transfer_request(const std::string& filename, const std::vector<char>& fileData);
    std::vector<char> create_checksum_verification_request(const std::string& file_name, const std::string& checksum);
    std::vector<char> create_reconnection_request();

private:
    std::string clientID;
};

#endif // PROTOCOL_H
