// The CryptoManager class handles cryptographic operations within the client application.
// It offers AES and RSA encryption/decryption methods, along with key generation functionalities,
// leveraging the Crypto++ library.
#ifndef CRYPTO_MANAGER_H
#define CRYPTO_MANAGER_H

#include <string>
#include <vector>
#include <rsa.h>
#include <aes.h>
#include <osrng.h>
#include <secblock.h>
#include <stdexcept>

class CryptoManager {
public:
    CryptoManager();

    // AES encryption and decryption methods
    std::vector<char> encrypt_with_aes(const std::vector<char>& data,
        const CryptoPP::SecByteBlock& key,
        const CryptoPP::SecByteBlock& iv);
    std::vector<char> decrypt_with_aes(const std::vector<char>& data,
        const CryptoPP::SecByteBlock& key,
        const CryptoPP::SecByteBlock& iv);

    // RSA encryption and decryption methods
    std::vector<char> encrypt_with_rsa(const std::vector<char>& data,
        const CryptoPP::RSA::PublicKey& publicKey);
    std::vector<char> decrypt_with_rsa(const std::vector<char>& data,
        const CryptoPP::RSA::PrivateKey& privateKey);

    // Key generation methods
    CryptoPP::RSA::PrivateKey generate_rsa_private_key();
    CryptoPP::RSA::PublicKey generate_rsa_public_key(const CryptoPP::RSA::PrivateKey& privateKey);

    // Convert RSA public key to a string representation
    std::string publicKeyToString(const CryptoPP::RSA::PublicKey& publicKey);

    // AES key and IV generation methods
    void generateAESKey();
    void generateAESIV();

    // Getters for UUID and private key string
    std::string getUUIDString() const;
    std::string getPrivateKeyString() const;

    // Getter methods for AES key and IV
    const CryptoPP::SecByteBlock& getAESKey() const;
    const CryptoPP::SecByteBlock& getAESIV() const;

private:
    CryptoPP::SecByteBlock aesKey;
    CryptoPP::SecByteBlock aesIV;
    CryptoPP::RSA::PrivateKey privateKey;
    std::string uuidString;
    std::string privateKeyString;

    static const size_t AES_SIZE = 16;
    static const int MIN_RSA_KEY_SIZE = 2048;
    static const int RSA_SIZE = 1024;

    std::string generateUUID();
    std::string privateKeyToBase64(const CryptoPP::RSA::PrivateKey& privateKey) const;
};

#endif // CRYPTO_MANAGER_H