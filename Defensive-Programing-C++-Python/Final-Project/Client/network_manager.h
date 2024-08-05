#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <vector>
#include "file_manager.h"
#include "config_manager.h"
#include "crypto_manager.h"

#pragma comment(lib, "Ws2_32.lib") 

// The NetworkManager class manages the network communications for the client.
// It handles tasks such as connecting to the server, sending data, and receiving data.
// This class encapsulates the details of network operations using the Winsock library.

class NetworkManager {
public:
    // Constructor to initialize the NetworkManager with server IP and port.
    NetworkManager(const std::string& server_ip, int port);
    ~NetworkManager();

    // Establish a connection to the server.
    bool connect_to_server();

    // Close the network connection.
    void close_connection();

    // Send data to the server.
    bool send_data(const std::vector<char>& data);

    // Receive data from the server.
    std::vector<char> receive_data();
    bool connectAndRegister(const Protocol& protocol, const std::string& clientID, const std::string& username, const std::string& publicKey);

    std::vector<char> create_registration_request(const std::string& clientID, const std::string& username, const std::string& publicKey) const;

private:
    std::string server_ip;
    int port;
    SOCKET client_socket;
};

#endif // NETWORK_MANAGER_H
