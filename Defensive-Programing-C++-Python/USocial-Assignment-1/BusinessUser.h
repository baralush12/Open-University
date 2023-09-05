/*
*BusinessUser.h
*/

#ifndef BUSINESSUSER_H_
#define  BUSINESSUSER_H_

#include "User.h"

// BusinessUser class that inherits from the User class.
class BusinessUser : public User {
public:
    /* Override the sendMessage method to implement business-specific logic.
       Business users can send messages to any user, regardless of friendship status.*/
    virtual void sendMessage(User* recipient, Message* msg) override;
};

#endif // BUSINESSUSER_H_