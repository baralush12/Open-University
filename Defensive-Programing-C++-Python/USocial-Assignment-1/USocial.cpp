#include "USocial.h"
#include "BusinessUser.h"
#include "User.h"
#include <cstdlib>

// Registers a new user, either as a regular or business user, and returns a pointer to the new user.
User* USocial::registerUser(const std::string& name, bool isBusiness /*= false by default */) {
    try {
        // Check if the name is empty
        if (name.empty()) {
            throw std::invalid_argument("Name Cannot Be Empty");
        }

        // Check if the name contains only alphabetic characters
        for (char c : name) {
            if (!std::isalpha(c)) {
                throw std::invalid_argument("Name must contain only alphabetic characters");
            }
        }

        unsigned long userId = generateUniqueId();
        User* newUser = isBusiness ? new BusinessUser() : new User();
        newUser->initialize(name, userId, this);
        users[userId] = newUser;
        return newUser;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return nullptr; // An error
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Error: Memory allocation failed - " << e.what() << std::endl;
        return nullptr; // Memory allocation failure
    }
}

// Removes a user from the social network and cleans up resources.
void USocial::removeUser(User* user) {
    try {
        if (!user) {
            throw std::invalid_argument("User does not exist");
        }

        unsigned long userId = user->getId();
        if (!getUserById(userId)) {
            throw std::invalid_argument("User ID does not exist");
        }

        users.erase(userId);
        freeIds.push(userId); // Add the ID to the queue of available IDs
        delete user;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// Retrieves a user by their unique ID.
User* USocial::getUserById(unsigned long id) {
    return users.find(id) != users.end() ? users[id] : nullptr;
}

// Generates a unique ID to be assigned to a new user.
unsigned long USocial::generateUniqueId() {
    if (!freeIds.empty()) {
        unsigned long userId = freeIds.front();
        freeIds.pop();
        return userId;
    }

    static unsigned long userId = 1;
    while (users.find(userId) != users.end()) {
        userId++;
    }
    return userId;
}

// Destructor to clean up resources related to the social network, such as users.
USocial::~USocial() {
    for (auto& userPair : users) {
        delete userPair.second; // Release the memory for each User object
    }
}
