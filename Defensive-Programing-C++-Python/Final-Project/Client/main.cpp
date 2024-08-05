// This is the main entry point for the C++ client application. 
// It includes the necessary headers for network management, cryptographic operations, 
// file handling, configuration management, protocol handling, and error handling.
// The file also sets up the Winsock2 library, which is essential for network communications on Windows.

#include "network_manager.h"
#include "crypto_manager.h"
#include "file_manager.h"
#include "config_manager.h"
#include "protocol.h"
#include "error_handler.h"
#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "crc.h"

// Function to run the main client operations
void run_client_operations() {
    ConfigManager configManager("transfer.info");
    configManager.load_configuration();

    NetworkManager networkManager(configManager.get_server_ip(), configManager.get_server_port());
    Protocol protocol("ClientID");
    ErrorHandler errorHandler;

    CryptoManager cryptoManager;

    // Generate RSA keys
    auto privateKey = cryptoManager.generate_rsa_private_key();
    auto publicKey = cryptoManager.generate_rsa_public_key(privateKey);

    // Convert public key to string
    std::string public_key = cryptoManager.publicKeyToString(publicKey);

    // Generate client ID (UUID)
    std::string client_id = cryptoManager.getUUIDString();

    // Check and possibly initialize 'me.info' file
    std::ifstream meFile("me.info");
    if (!meFile.is_open()) {
        std::ofstream outFile("me.info");
        outFile << configManager.get_client_name() << "\n";
        outFile << client_id << "\n";
        outFile << public_key << "\n";
        outFile.close();
    }
    else {
        // Read client_id and public_key from file if it already exists
        std::string line;
        getline(meFile, line);
        getline(meFile, client_id);
        getline(meFile, public_key);
        meFile.close();
    }

    try {
        // Connect to the server
        networkManager.connect_to_server();
        std::cout << "Connected to server successfully." << std::endl;

        // Format and send the registration request
        std::string username = configManager.get_client_name();

        std::string registrationData = client_id + "," + username + "," + public_key;

        auto registrationRequest = protocol.create_registration_request(configManager.get_client_name(), public_key);
        networkManager.send_data(registrationRequest);

        std::cout << "Sent registration request with username: " << username << std::endl;

        // Receive and process response from the server
        auto response = networkManager.receive_data();
        if (!response.empty()) {
            std::cout << "Response received from server." << std::endl;
        }
    }
    catch (const std::exception& e) {
        errorHandler.handle_error(e.what());
    }

    networkManager.close_connection();
}


int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return 1;
    }

    try {
        run_client_operations();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    WSACleanup();
    return 0;
}