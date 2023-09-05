/*
* Message.h
*/

#ifndef MEDIA_H_
#define MEDIA_H_

#include <iostream>

// Pure abstract class representing a general media type
class Media {
public:
    virtual void display() const = 0; // Pure virtual function
    virtual ~Media() {} // Virtual destructor
};

#endif // MEDIA_H_
