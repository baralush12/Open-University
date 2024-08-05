#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "protocol.h"
#include "crypto_manager.h"
#include "network_manager.h"
#include "config_manager.h"
#include <fstream>
#include <string>
#include <vector>

class FileManager {
public:
    FileManager(const std::string& clientID);

    std::vector<char> read_file(const std::string& file_path);
    void write_file(const std::string& file_path, const std::vector<char>& data);
    std::string calculate_checksum(const std::vector<char>& data);
    void save_client_info(const std::string& client_name, const std::string& client_id, const std::string& file_path);
    void read_transfer_info(const std::string& file_path, std::string& ip, int& port, std::string& client_name);
    bool send_file(const std::string& file_path, const std::string& server_ip, int server_port);
    void initializeMeFile(const ConfigManager& configManager, CryptoManager& cryptoManager);

private:
    CryptoManager cryptoManager;
    std::string clientID;
    static const size_t MAX_FILE_SIZE = 10485760;

    bool is_file_size_within_limit(const std::string& file_path);
};

#endif // FILE_MANAGER_H
