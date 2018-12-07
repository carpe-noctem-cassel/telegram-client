#pragma once

#include "telegram_msgs/message.capnp.h"

#include <tgbot/tgbot.h>
#include <kj/array.h>
#include <capnp/message.h>

#include <string>

// Different message types, so we can pull different data from this structure depending on what message should be sent.
// The telegram api has no means to send a prefilled message structure, so we have to construct the messages in our bot thread.
enum MsgType{
    message,
    privateMessage,
    reply
};

class Message {
public:
    Message();

    Message(int chatId, int userId, std::string text);

    Message(TgBot::Message::Ptr msg);

    Message(int chatId, int userId, std::string text, MsgType type);

    // Getters:
    long int getChatId();
    long int getUserId();
    long int getMessageId();
    int getType();
    unsigned int getTimestamp();
    std::string getUserName();
    std::string getFirstName();
    std::string getLastName();
    std::string getText();
    std::string getLanguageCode();

    // Setters:
    void setType(MsgType type);
    void setChatId(long int chatId);
    void setUserId(long int userId);
    void setText(std::string text);
    // setting messageId, timestamp, username, firstName, lastName, or languageCode makes no sense, so it should be not possible.
    // reading these things from a recived message on the other hand is fine.

    // Misc:
    void fromCapnp(void* msg, size_t size);
    void toCapnp(::capnp::MallocMessageBuilder &msgBuilder);

private:
    MsgType type;             // The type of the message needed to get the right data while sending.
    long int chatId;          // The ID of the chat this message was sent or will bet sent.
    long int userId;          // The User ID of the User who sent the Message or who this messsages adresses.
    long int messageId;       // A unique message id. Don't know what to do with it, but can come in handy.
    unsigned int timestamp;            // The unix timestamp the message was sent at.
    std::string userName;     // The optional username of the User the message was sent from.
    std::string firstName;    // The users first name. Can be used to address the user.
    std::string lastName;     // The users last name.
    std::string text;         // The text of the message
    std::string languageCode; // Optional language code of the user.

    // Private setters for values that should not be settable from the outside:
    void setLanguageCode(std::string lang);
    void setMessageId(long int id);
    void setTimestamp(unsigned int time);
    void setUserName(std::string name);
    void setFirstName(std::string name);
    void setLastName(std::string name);
};
