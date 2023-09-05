/*
* Photo.h
*/

#ifndef PHOTO_H_
#define PHOTO_H_

#include "Media.h"

// Photo class inherits from Media and represents a photo media type
class Photo : public Media {
public:
    void display() const override {
        std::cout << " ,Photo\n";
    }
};

#endif // PHOTO_H_
