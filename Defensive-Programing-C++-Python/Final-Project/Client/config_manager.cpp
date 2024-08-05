// The ConfigManager class is responsible for managing the client's configuration settings.
// It handles the loading of configuration from a specified file and provides access to various
// configuration parameters such as server IP, server port, client name, and file path for sending data.

#include "config_manager.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Constructor: Initializes the ConfigManager with the path to the configuration file.
ConfigManager::ConfigManager(const std::string& config_file_path)
    : config_file_path(config_file_path) {}

void ConfigManager::load_configuration() {
    std::ifstream configFile(config_file_path);
    std::string line;
    if (!configFile.is_open()) {
        std::cerr << "Unable to open config file: " << config_file_path << std::endl;
        return;
    }

    try {
        // Read server IP and port
        if (std::getline(configFile, line)) {
            size_t colonPos = line.find(':');
            if (colonPos != std::string::npos) {
                server_ip = line.substr(0, colonPos);
                server_port = std::stoi(line.substr(colonPos + 1));
            }
            else {
                throw std::runtime_error("Invalid format for IP and port in config file.");
            }
        }

        // Read client name
        if (std::getline(configFile, client_name)) {
            std::cout << "Read client name: " << client_name << std::endl;  // Debug print
        }
        else {
            throw std::runtime_error("Failed to read client name from config file.");
        }

        // Read file path
        if (!std::getline(configFile, file_path_to_send)) {
            throw std::runtime_error("Failed to read file path from config file.");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error reading config file: " << e.what() << std::endl;
    }

    configFile.close();
}


std::string ConfigManager::get_server_ip() const { return server_ip; }
int ConfigManager::get_server_port() const { return server_port; }
std::string ConfigManager::get_client_name() const { return client_name; }
std::string ConfigManager::get_file_path_to_send() const { return file_path_to_send; }