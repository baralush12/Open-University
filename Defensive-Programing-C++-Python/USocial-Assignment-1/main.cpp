#include "USocial.h"
#include "User.h"
#include "BusinessUser.h"
#include "Message.h"
#include "Post.h"
#include "Media.h"
#include "Photo.h"
#include "Video.h"
#include "Audio.h"

/*
main1
*/

/*
int main()
{
    USocial us;
    User* u1 = us.registerUser("Liron");
    User* u2 = us.registerUser("Yahav");
    User* u3 = us.registerUser("Shachaf");
    User* u4 = us.registerUser("Tsur", true);
    User* u5 = us.registerUser("Elit");
    u1->post("Hello world!");
    u2->post("I'm having a great time here :)", new Audio());
    u3->post("This is awesome!", new Photo());
    u5->addFriend(u1);
    u5->addFriend(u2);
    u5->viewFriendsPosts(); // should see only u1, u2 s' posts
    u4->sendMessage(u5, new Message("Buy Falafel!"));
    u5->viewReceivedMessages();
    try
    {
        u3->sendMessage(u5, new Message("try catch All your base are belong to us"));
    }
    catch (const std::exception& e)
    {
        std::cout << "error: " << e.what() << std::endl;
    }
    u5->viewReceivedMessages();
    u3->addFriend(u5);
    u3->sendMessage(u5, new Message("All your base are belong to us"));
    u5->viewReceivedMessages();
    return 0;
}
*/

/*
main2
*/

int main()
{
    USocial us;
    User* u1 = us.registerUser("Liron");
    User* u2 = us.registerUser("Yahav");
    User* u3 = us.registerUser("Shachaf");
    User* u4 = us.registerUser("Tsur", true);
    User* u5 = us.registerUser("Elit");

    u1->post("Hello world!");
    u2->post("I'm having a great time here :)", new Audio());
    u3->post("This is awesome!", new Photo());

    u5->addFriend(u1);
    u5->addFriend(u2);

    u5->viewFriendsPosts();

    u4->sendMessage(u5, new Message("Buy Falafel!"));
    u5->viewReceivedMessages();

    // Exception`s test
    us.registerUser("John123!");

    u5->addFriend(u1);
    u5->removeFriend(u3);

    u5->post("");

    User* nonExistingUser = nullptr;
    us.removeUser(nonExistingUser);

    u5->viewReceivedMessages();

    u3->addFriend(u5);
    u3->sendMessage(u5, new Message("All your base are belong to us"));
    u5->viewReceivedMessages();

    return 0;
}