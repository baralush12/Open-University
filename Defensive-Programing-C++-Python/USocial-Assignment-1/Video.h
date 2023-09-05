/*
* Message.h
*/

#ifndef VIDEO_H_
#define VIDEO_H_

#include "Media.h"

// Video class inherits from Media and represents a video media type
class Video : public Media {
public:
    void display() const override {
        std::cout << " ,Video\n";
    }
};

#endif // VIDEO_H_
