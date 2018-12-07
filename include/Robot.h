#pragma once

#include "User.h"

#include <capnzero/Publisher.h>
#include <tgbot/tgbot.h>

#include <string>
#include <vector>

class Robot
{
public:
    Robot(std::string key, std::string rName);
    ~Robot();

    // Setters:
    void setRobotName(std::string name);

    // Getters:
    std::string getChatBotName();
    std::string getRobotName();
    std::string getBotInfoString();
    bool getReceivingStatus();
    int getOwnUserId();
    unsigned int getUserCount();

    // Manage human info
    bool appendUser(std::string lang, std::string uName, std::string cName, int id);
    void updateCustomName(std::string cName, int id);
    void updateUserName(std::string uName, int id);
    void updateLanguageCode(std::string lang, int id);
    bool isIdKnown(int id);
    bool checkAuthentification(std::string reply, int id);
    bool isUserAuthenticated(int id);

    // Misc
    void addCommand(std::string text);
    void removeCommand(std::string text);
    void receiveMessages();
    void setupTelegram();

    // Event Handlers for Telegram
    void commandEvent(TgBot::Message::Ptr message);
    void messageEvent(TgBot::Message::Ptr message);

private:
    int userId;
    bool running;
    std::string apiKey;
    std::string chatBotName;
    std::string robotName;
    std::vector<std::string> commands;
    std::vector<User> users;
    TgBot::Bot* bot;
    // capnzerostuff
    void* context;
    capnzero::Publisher* czPub;

    // Private methods:
    unsigned int getUserIndexById(int id);
};
