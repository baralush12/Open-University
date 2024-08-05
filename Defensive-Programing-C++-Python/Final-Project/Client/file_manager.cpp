// The FileManager class is responsible for file-related operations in the client application.
// This includes reading from and writing to files, calculating file checksums for data integrity,
// and saving client information. It abstracts the file handling operations, providing a clean
// interface for file manipulation and data processing.

#include "file_manager.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include "crc.h"
#include <iomanip>

FileManager::FileManager(const std::string& id) : clientID(id), cryptoManager() {
}

// Read the content of a file and return it as a vector of characters.
std::vector<char> FileManager::read_file(const std::string& file_path) {
    if (!is_file_size_within_limit(file_path)) {
        std::cerr << "Error: File size exceeds the limit for: " << file_path << std::endl;
        return std::vector<char>(); 
    }

    std::ifstream file(file_path, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << file_path << std::endl;
        return std::vector<char>();
    }

    return std::vector<char>((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());
}

// Write the provided data (vector of characters) to a file.
void FileManager::write_file(const std::string& file_path, const std::vector<char>& data) {
    std::ofstream file(file_path, std::ios::binary);

    if (!file) {
        std::cerr << "Error opening file for writing: " << file_path << std::endl;
        return;

        file.write(data.data(), data.size());

        if (!file.good()) {
            std::cerr << "Error writing to file: " << file_path << std::endl;
        }
    }
}
// Calculate and return the checksum of the provided data.
std::string FileManager::calculate_checksum(const std::vector<char>&data) {
        if (data.empty()) {
            std::cerr << "Checksum calculation failed: Data is empty." << std::endl;
            return "";
        }

        try {
            std::vector<uint8_t> byteData(data.begin(), data.end());

            uint32_t checksum = crc32(byteData);

            std::stringstream ss;
            ss << std::hex << std::setw(8) << std::setfill('0') << checksum;
            return ss.str();
        }
        catch (const std::exception& e) {
            std::cerr << "Checksum calculation failed: " << e.what() << std::endl;
            return "";
        }
}

// Save client-specific information (such as name and ID) to a file.
void FileManager::save_client_info(const std::string& client_name, const std::string& client_id, const std::string& file_path) {
    if (client_name.empty() || client_id.empty()) {
        throw std::invalid_argument("Client information is incomplete: Missing name or ID.");
    }

    std::ofstream file(file_path);
    if (!file) {
        throw std::runtime_error("Error opening file for saving client info: " + file_path);
    }

    file << client_name << "\n" << client_id << "\n";
    if (!file.good()) {
        throw std::runtime_error("Failed to write client information to file.");
    }
}

// Read transfer information from a specified file.
void FileManager::read_transfer_info(const std::string& file_path, std::string& ip, int& port, std::string& client_name) {
    std::ifstream file(file_path);
    if (!file) {
        throw std::runtime_error("Error opening file for reading transfer info: " + file_path);
    }

    // Check if the file contents are readable and in expected format
    std::string port_str;
    if (!std::getline(file, ip) || ip.empty()) {
        throw std::runtime_error("Failed to read IP address from file: " + file_path);
    }

    if (!std::getline(file, port_str) || port_str.empty()) {
        throw std::runtime_error("Failed to read port information from file: " + file_path);
    }

    try {
        port = std::stoi(port_str);
    }
    catch (const std::invalid_argument& e) {
        throw std::runtime_error("Invalid port value in file: " + file_path + ". Error: " + e.what());
    }
    catch (const std::out_of_range& e) {
        throw std::runtime_error("Port value out of range in file: " + file_path + ". Error: " + e.what());
    }

    if (!std::getline(file, client_name) || client_name.empty()) {
        throw std::runtime_error("Failed to read client name from file: " + file_path);
    }
}

//Encrypts and sends a file to the server.
bool FileManager::send_file(const std::string& file_path, const std::string& server_ip, int server_port) {
    try {
        auto fileData = read_file(file_path);
        if (fileData.empty()) {
            std::cerr << "File is empty or could not be read: " << file_path << '\n';
            return false;
        }

        const auto& aesKey = cryptoManager.getAESKey();
        const auto& aesIV = cryptoManager.getAESIV();
        auto encryptedData = cryptoManager.encrypt_with_aes(fileData, aesKey, aesIV);
        if (encryptedData.empty()) {
            std::cerr << "Failed to encrypt the file data." << '\n';
            return false;
        }

        NetworkManager networkManager(server_ip, server_port);
        if (!networkManager.connect_to_server()) {
            std::cerr << "Failed to connect to server at " << server_ip << ":" << std::to_string(server_port) << '\n';
            return false;
        }

        Protocol protocol(clientID);
        auto request = protocol.create_file_transfer_request(file_path, encryptedData);
        if (!networkManager.send_data(request)) {
            std::cerr << "Failed to send data to server." << '\n';
            return false;
        }

        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error sending file: " << e.what() << '\n';
        return false;
    }
}

//Checks if the file size is within the specified limit.
bool FileManager::is_file_size_within_limit(const std::string& file_path) {
    struct stat stat_buf;
    int rc = stat(file_path.c_str(), &stat_buf);
    if (rc != 0) {
        std::cerr << "Failed to get file statistics for: " << file_path << std::endl;
        return false;
    }

    if (stat_buf.st_size > MAX_FILE_SIZE) {
        std::cerr << "File size exceeds the maximum limit." << std::endl;
        return false;
    }

    return true;
}

// Initialize 'me.info' file with client details
void FileManager::initializeMeFile(const ConfigManager& configManager, CryptoManager& cryptoManager) {
    std::ifstream meFile("me.info");
    if (!meFile.is_open()) {
        std::ofstream outFile("me.info");
        outFile << configManager.get_client_name() << "\n";
        outFile << cryptoManager.getUUIDString() << "\n";
        outFile << cryptoManager.getPrivateKeyString() << "\n";
        outFile.close();
    }
    else {
        meFile.close();
    }
}