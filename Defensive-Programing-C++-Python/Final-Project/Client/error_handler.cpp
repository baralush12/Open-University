// The ErrorHandler class is responsible for managing error handling in the client application.
// It provides functionalities to handle various errors that might occur during the application's
// runtime and implements strategies like retrying operations that failed due to recoverable errors.

#include "error_handler.h"

void ErrorHandler::handle_error(const std::string& error_message) {
    std::cerr << "Error: " << error_message << std::endl;
}

bool ErrorHandler::retry_operation() {
    static int retryCount = 0;
    const int maxRetries = 3;
    if (retryCount < maxRetries) {
        retryCount++;
        std::cout << "Retrying operation (" << retryCount << "/" << maxRetries << ")" << std::endl;
        return true;
    }
    return false;
}
