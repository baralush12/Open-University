#include "Post.h"

// Initialize the text member with the given text and media as nullptr
Post::Post(const std::string& text) {
    if (text.empty()) {
        throw std::invalid_argument("Post text cannot be empty");
    }
    this->text = text;
    this->media = nullptr;
}

// Initialize the text and media members with the given values
Post::Post(const std::string& text, Media* media) {
    if (text.empty()) {
        throw std::invalid_argument("Post text cannot be empty");
    }
    this->text = text;
    this->media = media;
}

// Return the text of the post
std::string Post::getText() const { 
    return text; 
}

// Return the media of the post
Media* Post::getMedia() const {
    return media; 
}