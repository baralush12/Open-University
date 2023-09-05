/*
* Message.h
*/

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <iostream>
#include <stdexcept>
#include <string>

// Represents a text message
class Message {
private:
    std::string text;

public:
    Message(const std::string& text); // Constructor to initialize the text
    std::string getText() const; // Method to get the text of the message
};

#endif // MESSAGE_H_
