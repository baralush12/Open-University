#include "BusinessUser.h"

// Sends a message to the specified recipient, without checking if they are friends, since business users can send messages to anyone.
void BusinessUser::sendMessage(User* recipient, Message* msg) {
    recipient->receiveMessage(msg);
}