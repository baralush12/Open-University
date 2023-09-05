/*
* Message.h
*/

#ifndef POST_H_
#define POST_H_

#include <string>
#include "Media.h"

// Represents a post that may contain text and media
class Post {
private:
    std::string text;
    Media* media; // The media associated with the post, can be nullptr

public:
    Post(const std::string& text); // Constructor to initialize text without media
    Post(const std::string& text, Media* media); // Constructor to initialize text and media
    std::string getText() const; // Method to get the text of the post
    Media* getMedia() const; // Method to get the media of the post
};

#endif // POST_H_
