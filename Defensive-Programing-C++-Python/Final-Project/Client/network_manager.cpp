// The NetworkManager class is responsible for managing network communications for the client.
// This includes establishing a connection to the server, sending data, and receiving data.
// It encapsulates the details of network operations, providing a clean interface for network interactions.

#include "network_manager.h"
#include "error_handler.h"
#include "protocol.h"
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS

// Constructor: Initializes NetworkManager with specified server IP and port.
NetworkManager::NetworkManager(const std::string& server_ip, int port)
    : server_ip(server_ip), port(port) {
}

// Destructor: Ensures the proper closure of the socket and cleanup of Winsock resources.
NetworkManager::~NetworkManager() {
    // Close the socket if it's valid.
    if (client_socket != INVALID_SOCKET) {
        closesocket(client_socket);
        client_socket = INVALID_SOCKET; 
    }

    close_connection();

    WSACleanup();
}

// connect_to_server: Attempts to establish a connection to the server.
bool NetworkManager::connect_to_server() {
    // Initialize Winsock
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        ErrorHandler::handle_error("WSAStartup failed: " + std::to_string(result));
        return false;
    }

    // Create a socket
    client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client_socket == INVALID_SOCKET) {
        ErrorHandler::handle_error("Error at socket(): " + std::to_string(WSAGetLastError()));
        WSACleanup();
        return false;
    }

    // Setup the server address structure
    sockaddr_in client_service{};
    client_service.sin_family = AF_INET;
    client_service.sin_port = htons(port);

    // Convert IP address from text to binary form
    result = inet_pton(AF_INET, server_ip.c_str(), &client_service.sin_addr);
    if (result <= 0) {
        ErrorHandler::handle_error(result == 0 ? "Not in presentation format" : "inet_pton error: " + std::to_string(WSAGetLastError()));
        closesocket(client_socket);
        WSACleanup();
        return false;
    }

    // Attempt to connect to the server
    if (connect(client_socket, reinterpret_cast<SOCKADDR*>(&client_service), sizeof(client_service)) == SOCKET_ERROR) {
        ErrorHandler::handle_error("Failed to connect: " + std::to_string(WSAGetLastError()));
        closesocket(client_socket);
        WSACleanup();
        return false;
    }

    std::cout << "Successfully connected to server." << std::endl;
    return true;
}

// Close the network connection and release the socket.
void NetworkManager::close_connection() {
    if (client_socket != INVALID_SOCKET) {
        // Attempt to close the socket
        if (closesocket(client_socket) == SOCKET_ERROR) {
            ErrorHandler::handle_error("Error closing socket: " + std::to_string(WSAGetLastError()));
        }
        client_socket = INVALID_SOCKET;
        std::cout << "Connection closed." << std::endl;
    }
    else {
        std::cout << "Connection was not open." << std::endl;
    }
}

// receive_data: Receives data from the server.
std::vector<char> NetworkManager::receive_data() {
    // Define a buffer for the incoming data
    char buffer[512];
    std::vector<char> receivedData;

    while (true) {
        int bytesReceived = recv(client_socket, buffer, sizeof(buffer), 0);

        // Check for SOCKET_ERROR
        if (bytesReceived == SOCKET_ERROR) {
            ErrorHandler::handle_error("Error receiving data: " + std::to_string(WSAGetLastError()));
            break; 
        }
        // Check if the server has closed the connection
        else if (bytesReceived == 0) {
            ErrorHandler::handle_error("Server closed the connection.");
            break; 
        }
        else {
            receivedData.insert(receivedData.end(), buffer, buffer + bytesReceived);
            if (bytesReceived < sizeof(buffer)) {
                break;
            }
        }
    }

    return receivedData;
}

// send_data: Sends data to the server.
bool NetworkManager::send_data(const std::vector<char>& data) {
    size_t totalBytesSent = 0;
    size_t dataLength = data.size();

    while (totalBytesSent < dataLength) {
        int bytesSent = send(client_socket, data.data() + totalBytesSent, dataLength - totalBytesSent, 0);

        // Check for SOCKET_ERROR
        if (bytesSent == SOCKET_ERROR) {
            ErrorHandler::handle_error("Error sending data: " + std::to_string(WSAGetLastError()));
            return false; // Return false on error
        }

        totalBytesSent += bytesSent;
    }
    return true;
}

// Establishes connection and handles registration
bool NetworkManager::connectAndRegister(const Protocol& protocol, const std::string& clientID, const std::string& username, const std::string& publicKey) {
    if (!connect_to_server()) {
        ErrorHandler::handle_error("Failed to connect to server.");
        return false;
    }

    try {
        auto registrationRequest = protocol.create_registration_request(username, publicKey);
        if (!send_data(registrationRequest)) {
            ErrorHandler::handle_error("Failed to send registration request.");
            return false;
        }

        auto response = receive_data();
        if (response.empty()) {
            ErrorHandler::handle_error("No response received from server.");
            return false;
        }

        return true;
    }
    catch (const std::exception& e) {
        ErrorHandler::handle_error("Error in registration: " + std::string(e.what()));
        return false;
    }
}
