/*
* Message.h
*/

#ifndef AUDIO_H_
#define AUDIO_H_

#include "Media.h"

// Audio class inherits from Media and represents an audio media type
class Audio : public Media {
public:
    void display() const override {
        std::cout << " ,Audio\n";
    }
};

#endif // AUDIO_H_
