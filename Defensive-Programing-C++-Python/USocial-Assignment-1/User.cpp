#include "User.h"

// Constructor to initialize user's.
User::User() : us(nullptr), id(0), isBusinessUser(false) {}

// Destructor to clean up user's.
User::~User() {
    // Delete dynamically allocated Post objects
    for (auto* post : posts) {
        delete post;
    }

    // Delete dynamically allocated Message objects
    for (auto* message : receivedMsgs) {
        delete message;
    }
}

// Initializes user's information with name, ID, and reference to USocial.
void User::initialize(std::string n, unsigned long i, USocial* u, bool isBusiness) {
    name = n;
    id = i;
    us = u;
    isBusinessUser = isBusiness;
}

// Returns the user's unique ID.
unsigned long User::getId() {
    return id;
}

// Returns the user's name.
std::string User::getName() {
    return name;
}

// Adds a friend to the user's friend list.
void User::addFriend(User* user) {
    try {
        if (std::find(friends.begin(), friends.end(), user->getId()) != friends.end()) {
            throw std::invalid_argument(user->getName() + " Is already in the friend list");
        }
        friends.push_back(user->getId());
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error:" << e.what() << std::endl;
    }
}

// Removes a friend from the user's friend list.
void User::removeFriend(User* user) {
    try {
        if (std::find(friends.begin(), friends.end(), user->getId()) == friends.end()) {
            throw std::invalid_argument(user->getName() + " Is not in the friend list");
        }
        friends.remove(user->getId());
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void User::post(const std::string& text) {
    try {
        if (text.empty()) {
            throw std::invalid_argument("Text cannot be empty");
        }
        // Create a Post and add it to the user's posts
        Post* p = new Post(text);
        posts.push_back(p);
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void User::post(const std::string& text, Media* media) {
    try {
        if (text.empty()) {
            throw std::invalid_argument("Text cannot be empty");
        }
        // Create a Post with media and add it to the user's posts
        Post* p = new Post(text, media);
        posts.push_back(p);
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// Returns the user's posts.
std::list<Post*> User::getPosts() {
    if (posts.empty()) {
        std::cout << "Your post list is empty.\n";
    }
    else {
        return posts;
    }
}

// Views and prints posts of all friends.
void User::viewFriendsPosts() {
    for (unsigned long friendId : friends) {
        User* friendUser = us->getUserById(friendId);
        if (friendUser) {
            std::list<Post*> friendPosts = friendUser->getPosts();
            for (Post* post : friendPosts) {
                std::cout << post->getText();
                if (post->getMedia()) {
                    post->getMedia()->display(); // Call the display method of the media
                }
                std::cout << "\n";
            }
        }
    }
}

// Handles receiving a message.
void User::receiveMessage(Message* message) {
    receivedMsgs.push_back(message); // Add the received message to the list
}

// Sends a message to another user.
void User::sendMessage(User* recipient, Message* msg) {
    if (std::find(friends.begin(), friends.end(), recipient->getId()) != friends.end()) {
        recipient->receiveMessage(msg);
    }
    else {
        std::cerr << "Cannot send message to a non-friend user.\n";
        delete msg;
    }
}

// Views and prints all received messages.
void User::viewReceivedMessages() {
    if (receivedMsgs.empty()) {
        std::cout << "No messages received.\n";
        return;
    }

    for (Message* msg : receivedMsgs) {
        std::cout << msg->getText() << "\n";
    }
}