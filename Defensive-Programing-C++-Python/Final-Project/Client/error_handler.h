#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <string>
#include <iostream>

// The ErrorHandler class is responsible for handling errors in the client application.
// It provides methods to manage error reporting and retry operations, encapsulating
// the error handling logic to ensure a consistent error management strategy.

class ErrorHandler {
public:
    // Handle an error given its message.
    static void handle_error(const std::string& error_message);

    // Retry a previously failed operation.
    bool retry_operation();
};

#endif // ERROR_HANDLER_H
