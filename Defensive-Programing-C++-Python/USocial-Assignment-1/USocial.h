/*
*USocial.h
*/

#ifndef USOCIAL_H_
#define  USOCIAL_H_

#include <map>
#include <queue>
#include <string>

class User;

// USocial class handles user registration, management, and unique ID generation
class USocial {
private:
    std::map<unsigned long, User*> users;// Map to store active users
    std::queue<unsigned long> freeIds; // Queue to store available IDs
    unsigned long generateUniqueId();// Function to generate a unique ID

public:
    ~USocial(); // Destructor
    User* registerUser(const std::string& name, bool isBusiness = false); // Register a user, optionally as a business user
    void removeUser(User* user); // Remove a user from the system
    User* getUserById(unsigned long id); // Retrieve a user by their unique ID

    friend class User; // Define User as a friend to allow access to private members
};

#endif // USOCIAL_H_