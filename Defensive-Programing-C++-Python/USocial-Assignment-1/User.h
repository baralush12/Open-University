/*
*User.h
*/

#ifndef USER_H_
#define  USER_H_

#include "USocial.h"
#include "Post.h"
#include "Message.h"

#include <list>
#include <string>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

class USocial;
class Media;
class Message;
class Post;

// User class represents individual users in the system and their associated data and behavior
class User {
private:
    bool isBusinessUser; // Flag to indicate if the user is a business user
protected:
    USocial* us;
    unsigned long id; // Unique identifier for the user
    std::string name; // Name of the user
    std::list<unsigned long> friends; // List of friend's IDs
    std::list<Post*> posts; // List of posts releated to the user
    std::list<Message*> receivedMsgs; // List of received messages

    // Initializes the user with specific details
    void initialize(std::string name, unsigned long id, USocial* us, bool isBusiness = false);

    User(); // Constructor
    ~User(); // Destructor
public:
    unsigned long getId(); // Get user's ID
    std::string getName(); // Get user's name
    void addFriend(User* user); // Add a friend
    void removeFriend(User* user); // Remove a friend
    void post(const std::string& text); // Create a text post
    void post(const std::string& text, Media* media); // Create a media post
    std::list<Post*> getPosts(); // Retrieve user's posts
    void viewFriendsPosts(); // View posts from friends
    void receiveMessage(Message* message); // Receive a message
    virtual void sendMessage(User* recipient, Message* msg); // Send a message
    void viewReceivedMessages(); // View received messages

    friend class USocial; // Define USocial as a friend to allow access to private members
};
#endif // USER_H_