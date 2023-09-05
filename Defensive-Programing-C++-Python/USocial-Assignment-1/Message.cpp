#include "Message.h"

// Constructor that initializes the Message object with the given text
Message::Message(const std::string& text) {
    try {
        if (text.empty()) {
            throw std::invalid_argument("Message text cannot be empty");
        }
        this->text = text;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// Getter function that returns the text content of the message
std::string Message::getText() const {
    return text; // Return the text of the message
}