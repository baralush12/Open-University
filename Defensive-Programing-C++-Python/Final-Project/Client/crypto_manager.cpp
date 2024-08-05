// The CryptoManager class handles cryptographic operations for the client application.
// It provides functionalities for AES and RSA encryption/decryption, including key generation
// for RSA. This class abstracts the complexity of cryptographic operations using the Crypto++ library.

#include "crypto_manager.h"
#include <modes.h>
#include <filters.h>
#include <base64.h>
#include <osrng.h>
#include <iomanip>
#include <random>
#include <sstream>
#include <iostream>
#include <algorithm>

// Constructor
CryptoManager::CryptoManager() {
    // Generate initial AES key and IV
    generateAESKey();
    generateAESIV();

    // Generate RSA private key and corresponding public key
    privateKey = generate_rsa_private_key();
    auto publicKey = generate_rsa_public_key(privateKey);

    // Generate UUID and convert private key to string representation
    uuidString = generateUUID();
    privateKeyString = privateKeyToBase64(privateKey);
}

// AES Encryption
std::vector<char> CryptoManager::encrypt_with_aes(const std::vector<char>& data,
    const CryptoPP::SecByteBlock& key,
    const CryptoPP::SecByteBlock& iv) {
    if (data.empty()) {
        throw std::invalid_argument("Data to be encrypted cannot be empty.");
    }

    if (key.size() != AES_SIZE || iv.size() != AES_SIZE) {
        throw std::invalid_argument("Key and IV sizes must match the AES block size.");
    }

    try {
        std::string cipherText;
        CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryption(key, key.size(), iv);
        CryptoPP::StringSource(
            reinterpret_cast<const CryptoPP::byte*>(data.data()), data.size(), true,
            new CryptoPP::StreamTransformationFilter(
                encryption,
                new CryptoPP::StringSink(cipherText)
            )
        );
        return std::vector<char>(cipherText.begin(), cipherText.end());
    }
    catch (const CryptoPP::Exception& e) {
        std::cerr << "AES encryption failed: " << e.what() << '\n';
        throw;
    }
}

// AES Decryption
std::vector<char> CryptoManager::decrypt_with_aes(const std::vector<char>& data,
    const CryptoPP::SecByteBlock& key,
    const CryptoPP::SecByteBlock& iv) {
    if (data.empty()) {
        throw std::invalid_argument("Data to be decrypted cannot be empty.");
    }

    if (key.size() != AES_SIZE || iv.size() != AES_SIZE) {
        throw std::invalid_argument("Key and IV sizes must match the AES block size.");
    }

    try {
        std::string plainText;
        CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decryption(key, key.size(), iv);
        CryptoPP::StringSource(
            reinterpret_cast<const CryptoPP::byte*>(data.data()), data.size(), true,
            new CryptoPP::StreamTransformationFilter(
                decryption,
                new CryptoPP::StringSink(plainText)
            )
        );
        return std::vector<char>(plainText.begin(), plainText.end());
    }
    catch (const CryptoPP::Exception& e) {
        std::cerr << "AES decryption failed: " << e.what() << '\n';
        throw;
    }
}


// RSA Encryption
std::vector<char> CryptoManager::encrypt_with_rsa(const std::vector<char>& data,
    const CryptoPP::RSA::PublicKey& publicKey) {

    if (data.empty()) {
        throw std::invalid_argument("Data to be encrypted cannot be empty.");
    }

    CryptoPP::AutoSeededRandomPool rng;

    if (!publicKey.Validate(rng, 3)) {
        throw std::runtime_error("Invalid RSA public key.");
    }

    try {
        std::string cipherText;
        CryptoPP::RSAES_OAEP_SHA_Encryptor encryptor(publicKey);
        CryptoPP::StringSource(
            reinterpret_cast<const CryptoPP::byte*>(data.data()), data.size(), true,
            new CryptoPP::PK_EncryptorFilter(rng, encryptor,
                new CryptoPP::StringSink(cipherText)
            )
        );
        return std::vector<char>(cipherText.begin(), cipherText.end());
    }
    catch (const CryptoPP::Exception& e) {
        std::cerr << "RSA encryption failed: " << e.what() << '\n';
        throw;
    }
}


// RSA Decryption
std::vector<char> CryptoManager::decrypt_with_rsa(const std::vector<char>& data,
    const CryptoPP::RSA::PrivateKey& privateKey) {

    if (data.empty()) {
        throw std::invalid_argument("Data to be decrypted cannot be empty.");
    }

    // Define the random number generator before using it for validation
    CryptoPP::AutoSeededRandomPool rng;

    if (!privateKey.Validate(rng, 3)) {
        throw std::runtime_error("Invalid RSA private key.");
    }

    try {
        std::string plainText;
        CryptoPP::RSAES_OAEP_SHA_Decryptor decryptor(privateKey);
        CryptoPP::StringSource(
            reinterpret_cast<const CryptoPP::byte*>(data.data()), data.size(), true,
            new CryptoPP::PK_DecryptorFilter(rng, decryptor,
                new CryptoPP::StringSink(plainText)
            )
        );
        return std::vector<char>(plainText.begin(), plainText.end());
    }
    catch (const CryptoPP::Exception& e) {
        std::cerr << "RSA decryption failed: " << e.what() << '\n';
        throw; 
    }
}

// RSA Private Key Generation
CryptoPP::RSA::PrivateKey CryptoManager::generate_rsa_private_key() {
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::RSA::PrivateKey privateKey;

    try {
        int keySize = 2048; // More secure key size
        privateKey.GenerateRandomWithKeySize(rng, keySize);

        if (!privateKey.Validate(rng, 3)) {
            throw std::runtime_error("Failed to validate the generated RSA private key.");
        }
    }
    catch (const CryptoPP::Exception& e) {
        std::cerr << "RSA key generation failed: " << e.what() << '\n';
        throw;
    }

    return privateKey;
}



// RSA Public Key Generation
CryptoPP::RSA::PublicKey CryptoManager::generate_rsa_public_key(const CryptoPP::RSA::PrivateKey& privateKey) {
    try {
        CryptoPP::AutoSeededRandomPool rng;

        if (!privateKey.Validate(rng, 3)) {
            throw std::runtime_error("Invalid RSA private key for generating public key.");
        }

        CryptoPP::RSA::PublicKey publicKey(privateKey);

        if (!publicKey.Validate(rng, 3)) {
            throw std::runtime_error("Generated RSA public key is invalid.");
        }

        return publicKey;
    }
    catch (const CryptoPP::Exception& e) {
        std::cerr << "RSA public key generation failed: " << e.what() << '\n';
        throw;
    }
}

// Public Key to String
std::string CryptoManager::publicKeyToString(const CryptoPP::RSA::PublicKey& publicKey) {
    try {
        // Step 1: Convert the public key to a binary string
        std::string publicKeyBinary;
        publicKey.DEREncode(CryptoPP::StringSink(publicKeyBinary).Ref());

        // Step 2: Base64 encode the binary string
        std::string publicKeyBase64;
        CryptoPP::Base64Encoder base64Encoder(new CryptoPP::StringSink(publicKeyBase64), false);
        base64Encoder.Put((const CryptoPP::byte*)publicKeyBinary.data(), publicKeyBinary.size());
        base64Encoder.MessageEnd();

        return publicKeyBase64;
    }
    catch (const CryptoPP::Exception& e) {
        std::cerr << "Error converting public key to string: " << e.what() << '\n';
        throw;
    }
}

// Generate AES Key
void CryptoManager::generateAESKey() {
    try {
        aesKey.CleanNew(AES_SIZE);
        CryptoPP::AutoSeededRandomPool prng;
        prng.GenerateBlock(aesKey, aesKey.size());

        if (aesKey.size() != AES_SIZE) {
            throw std::runtime_error("AES key generated with incorrect size.");
        }

        std::cout << "AES key generated successfully." << std::endl;
    }
    catch (const CryptoPP::Exception& e) {
        std::cerr << "Crypto++ error during AES key generation: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error generating AES key: " << e.what() << std::endl;
    }
}


void CryptoManager::generateAESIV() {
    try {
        aesIV.CleanNew(AES_SIZE);
        CryptoPP::AutoSeededRandomPool prng;
        
        prng.GenerateBlock(aesIV, aesIV.size());

        std::cout << "AES IV generated successfully" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error generating AES IV: " << e.what() << std::endl;
    }
}

// Get UUID String
std::string CryptoManager::getUUIDString() const {
    if (uuidString.empty()) {
        std::cerr << "UUID string is not initialized." << std::endl;
    }

    std::cout << "Retrieving UUID string: " << uuidString << std::endl;

    return uuidString;
}

// Generate UUID
std::string CryptoManager::generateUUID() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dis(0, 0xFFFFFFFF);

    std::stringstream ss;
    for (int i = 0; i < 4; ++i) { 
        ss << std::hex << std::setw(8) << std::setfill('0') << dis(gen);
    }

    std::string uuid = ss.str();
    if (uuid.length() > 32) {
        uuid = uuid.substr(0, 32);
    }

    return uuid;
}




// Convert Private Key to Base64 String
std::string CryptoManager::privateKeyToBase64(const CryptoPP::RSA::PrivateKey& key) const {
    std::string privateKeyStr;

    try {
        CryptoPP::AutoSeededRandomPool rng;
        if (!key.Validate(rng, 3)) {
            std::cerr << "Invalid RSA Private Key provided." << std::endl;
            return "";
        }

        CryptoPP::Base64Encoder encoder(new CryptoPP::StringSink(privateKeyStr), false);
        key.DEREncode(encoder);
        encoder.MessageEnd();

        std::cout << "Private key successfully converted to Base64." << std::endl;
    }
    catch (const CryptoPP::Exception& e) {
        std::cerr << "Error converting private key to Base64: " << e.what() << std::endl;
        return "";
    }

    return privateKeyStr;
}

//Retrieves the private RSA key as a Base64 encoded string.
std::string CryptoManager::getPrivateKeyString() const {
    if (privateKeyString.empty()) {
        std::cerr << "Private key string is empty." << std::endl;
    }
    return privateKeyString;
}

//Retrieves the generated AES key.
const CryptoPP::SecByteBlock& CryptoManager::getAESKey() const {
    if (aesKey.empty()) {
        std::cerr << "AES key is empty." << std::endl;
    }
    return aesKey;
}

//Retrieves the generated AES initialization vector (IV).
const CryptoPP::SecByteBlock& CryptoManager::getAESIV() const {
    if (aesIV.empty()) {
        std::cerr << "AES IV is empty." << std::endl;
    }
    return aesIV;
}
