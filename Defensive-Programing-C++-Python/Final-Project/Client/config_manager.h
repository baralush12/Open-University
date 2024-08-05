#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <string>

// The ConfigManager class is responsible for managing configuration settings of the client application.
// It allows loading of configuration from a file and provides methods to access various configuration
// parameters such as server IP, server port, client name, and file path for data transmission.

class ConfigManager {
public:
    // Constructor to initialize the ConfigManager with a configuration file path.
    ConfigManager(const std::string& config_file_path);

    void load_configuration();
    std::string get_server_ip() const;
    int get_server_port() const;
    std::string get_client_name() const;
    std::string get_file_path_to_send() const;

private:
    std::string config_file_path;
    std::string server_ip;
    int server_port;
    std::string client_name;
    std::string file_path_to_send;

};

#endif // CONFIG_MANAGER_H
