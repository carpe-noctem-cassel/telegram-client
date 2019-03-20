#pragma once

#include "User.h"
#include "Message.h"

#include <capnzero/Common.h>
#include <capnzero/Publisher.h>
#include <capnzero/Subscriber.h>
#include <tgbot/tgbot.h>

#include <string>
#include <vector>

class Robot
{
public:
    Robot(std::string key, std::string rName, void* ctx);
    ~Robot();

    // Setters:
    void setRobotName(std::string name);

    // Getters:
    std::string getBotInfoString();
    std::string getBotName();
    unsigned int getUserCount();

    // Manage human info
    bool isIdKnown(int id);

    // Misc
    void receiveMessages();
    void setupTelegram();
    void setupUpstream();

    // Event Handlers for Telegram
    void commandEvent(TgBot::Message::Ptr message);
    void messageEvent(TgBot::Message::Ptr message);
    void dispatchMessage(::capnp::FlatArrayMessageReader& reader);

private:
    int userId;
    bool running;
    std::string apiKey;
    std::string chatBotName;
    std::string robotName;
    std::string topicDown;
    std::string topicUp;
    std::vector<std::string> commands;
    std::vector<User> users;
    TgBot::Bot* bot;
    // capnzerostuff
    void* context;
    capnzero::Publisher* czPub;
    capnzero::Subscriber* czSub;

    // Private methods:
    unsigned int getUserIndexById(int id);
};
