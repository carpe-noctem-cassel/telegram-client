#include <Message.h>
#include <tgbot/tgbot.h>
#include <capnp/common.h>
#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <kj/array.h>

Message::Message()
{

}

Message::Message(int chatId, int userId, std::string text)
{
    this->setChatId(chatId);
    this->setUserId(userId);
    this->setText(text);
    this->setType(MsgType::message);
}

Message::Message(TgBot::Message::Ptr msg)
{
    this->setChatId(msg->chat->id);
    this->setUserId(msg->from->id);
    this->setText(msg->text);
    this->setType(MsgType::message);
    this->firstName = msg->from->firstName;
    this->lastName = msg->from->lastName;
    this->setUserName(msg->from->username);
    this->setLanguageCode(msg->from->languageCode);
    this->setMessageId(msg->messageId);
    this->setTimestamp(msg->date);
}

Message::Message(int chatId, int userId, std::string text, MsgType type)
{
    this->setChatId(chatId);
    this->setUserId(userId);
    this->setText(text);
    this->setType(type);
}


// Setters:
void  Message::setChatId(long int chatId)
{
    this->chatId = chatId;
}

void Message::setUserId(long int userId)
{
    this->userId = userId;
}

void Message::setType(MsgType type)
{
    this->type = type;
}

void Message::setText(std::string text)
{
    this->text = text;
}

void Message::setLanguageCode(std::string lang)
{
    this->languageCode = lang;
}

void Message::setMessageId(long int id)
{
    this->messageId = id;
}

void Message::setTimestamp(unsigned int time)
{
    this->timestamp = time;
}

void Message::setUserName(std::string name)
{
    this->userName = name;
}

void Message::setFirstName(std::string name)
{
    this->firstName = name;
}

void Message::setLastName(std::string name)
{
    this->lastName = name;
}


// Getters:
long int Message::getChatId()
{
    return this->chatId;
}

long int Message::getUserId()
{
    return this->userId;
}

long int Message::getMessageId()
{
    return this->messageId;
}

unsigned int Message::getTimestamp()
{
    return this->timestamp;
}

int Message::getType()
{
    return this->type;
}

std::string Message::getFirstName()
{
    return this->firstName;
}

std::string Message::getLastName()
{
    return this->lastName;
}

std::string Message::getLanguageCode()
{
    return this->languageCode;
}

std::string Message::getText()
{
    return this->text;
}

std::string Message::getUserName()
{
    return this->userName;
}


// Misc:
void Message::fromCapnp(void *msg, size_t size)
{
    auto wordArray = kj::ArrayPtr<capnp::word const>(reinterpret_cast<capnp::word const*>(msg), size);
    ::capnp::FlatArrayMessageReader message = ::capnp::FlatArrayMessageReader(wordArray);
    telegram_msgs::Message::Reader msgReader = message.getRoot<telegram_msgs::Message>();
    this->setText(msgReader.getText());
    this->setType((MsgType) msgReader.getType());
    this->setUserId(msgReader.getUserId());
    this->setChatId(msgReader.getChatId());
    this->setLanguageCode(msgReader.getLanguageCode());
    this->setFirstName(msgReader.getFirstName());
    this->setLastName(msgReader.getLastName());
    this->setUserName(msgReader.getUserName());
}

void Message::toCapnp(::capnp::MallocMessageBuilder &msgBuilder)
{
    telegram_msgs::Message::Builder message = msgBuilder.initRoot<telegram_msgs::Message>();

    if(!this->getLanguageCode().empty())
        message.setLanguageCode(this->getLanguageCode());
    else
        message.setLanguageCode("NONE");

    if(!this->getUserName().empty())
        message.setUserName(this->getUserName());
    else
        message.setUserName("NONE");

    if(!this->getLastName().empty())
        message.setLastName(this->getLastName());
    else
        message.setLastName("NONE");

    if(!this->getFirstName().empty())
        message.setLastName(this->getLastName());
    else
        message.setLastName("NONE");

    if(this->getTimestamp() > 0)
        message.setTimestamp(this->getTimestamp());
    else
        message.setTimestamp(0);

    message.setText(this->getText());
    message.setType((unsigned char) this->getType());
    message.setChatId(this->getChatId());
    message.setUserId((int32_t) this->getUserId());
    message.setMessageId((int32_t) this->getMessageId());
//    std::cout << "pub: Message to send: " << message.toString().flatten().cStr() << std::endl;
}