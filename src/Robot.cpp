#include "Robot.h"
#include "Message.h"
#include "User.h"
#include <capnp/common.h>
#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <kj/array.h>

#include <iostream>

// =========================================================
// Constructors/Destructor:
Robot::Robot(std::string key, std::string rName, void* ctx)
{
	std::cout << "Creating a new Robot.\n";
	this->apiKey = key;
	this->setRobotName(rName);
	this->context = ctx;
	this->topicDown = "downstream";
	this->topicUp = "upstream";
	std::cout << "Set up some stuff! Creating sockets . . .\n";
	this->czPub = new capnzero::Publisher(this->context, this->topicDown);
//	this->czPub->bind(capnzero::CommType::IPC, "@capnzero.ipc");
    this->czPub->bind(capnzero::CommType::UDP, "224.0.0.2:5555");
    this->czSub = new capnzero::Subscriber(this->context, this->topicUp);
    this->czSub->connect(capnzero::CommType::UDP, "224.0.0.2:5555");
    std::cout << "End of constructor\n";
}

Robot::~Robot(){
	// clean up capnzero stuff
	delete this->czPub;
	delete this->czSub;
//	zmq_ctx_term(this->context);
}

// ==========================================================
// Setters:

void Robot::setRobotName(std::string name)
{
	this->robotName = name;
}

// =========================================================
// Getters:

std::string Robot::getBotInfoString()
{
	std::string result = "Telegram name: " + this->getBotName() + '\n';
	result += "Running on the robot \"" + this->robotName + "\"\n";
//	result += "Amount of known users: " + this->getUserCount() + '\n';
	return result;
}

std::string Robot::getBotName()
{
	return this->bot->getApi().getMe()->username;
}

unsigned int Robot::getUserCount()
{
	return this->users.size();
}

// ==========================================================
// Manage human info:

bool Robot::isIdKnown(int id)
{
	for(unsigned int i = 0; i < this->users.size(); ++i)
	{
		if(this->users[i].getUserId() == id)
		{
			return true;
		}
	}
	return false;
}

// ==================================================================
// Misc:

//void Robot::addCommand(std::string text)
//{
//	this->commands.push_back(text);
//}
//
//void Robot::removeCommand(std::string text)
//{
//	for(unsigned int i = 0; i < this->commands.size(); ++i)
//	{
//		if(this->commands[i] == text)
//		{
//			this->commands.erase(this->commands.begin() + i);
//			break;
//		}
//	}
//}

void Robot::setupTelegram()
{
	std::cout << "setupTelegram was called.\n";
	this->bot = new TgBot::Bot(this->apiKey);
	std::cout << "Set start event.\n";
	this->bot->getEvents().onCommand("start", [this](TgBot::Message::Ptr message){
		this->commandEvent(message);
	});
	std::cout << "Set quit command.\n";
	this->bot->getEvents().onCommand("quit", [this](TgBot::Message::Ptr message){
		this->commandEvent(message);
	});
    try {
        this->bot->getEvents().onNonCommandMessage([this](TgBot::Message::Ptr message){std::cout << "Recived Message\n"; this->messageEvent(message);});
        std::cout << "Set messageEvent.\n";
    }
    catch (TgBot::TgException &e)
    {
        std::cerr << "Error: " << e.what();
    }
	try
	{
		this->chatBotName = this->bot->getApi().getMe()->username;
	}
	catch(TgBot::TgException &e) {
        std::cerr << "Error: " << e.what();
    }
    std::cout << this->getBotInfoString();
	this->running = true;
}

void Robot::receiveMessages()
{
	std::cout << "reciveMessage was called.\n";
	int state = 0;
	char animatedChar = ' ';
		try
		{
			TgBot::TgLongPoll longPoll(*(this->bot));
			std::cout << "Starting long poll loop\n";
			while(this->running)
			{
//			    std::cout << "TEST" << std::endl;
			    switch(state)
			    {
                    case 0:
                        animatedChar = '-';
                        ++state;
                        break;
                    case 1:
                        animatedChar = '\\';
                        ++state;
                        break;
                    case 2:
                        animatedChar = '|';
                        ++state;
                        break;
                    case 3:
                        animatedChar = '/';
                        state = 0;
                        break;
                    default:
                        std::cerr << "Somthing wierd is going on!\n";
			    }
			    std::cout << "\033[30;48;5;51mBot Status: " << animatedChar <<
			                 " Downstream Topic: " << this->topicDown << "\033[0m\r";
			    std::cout.flush();
				longPoll.start();
			}
		}
		catch(TgBot::TgException &e)
		{
			std::cout << e.what();
		}

}

void Robot::setupUpstream()
{
    this->czSub->subscribe(&Robot::dispatchMessage, &(*this));
}

// ========================================================================
// Event handlers for Telegram

void Robot::commandEvent(TgBot::Message::Ptr message)
{
	if(message->text == "/start")
	{
		std::cout << "recived Start\n";
		this->bot->getApi().sendMessage(message->chat->id, "Hi!");
	}
	else if(message->text == "/quit")
	{
		std::cout << "recived quit\n";
		if(this->running)
        {
			this->bot->getApi().sendMessage(message->chat->id, "Bye!");
		}
		this->running = false;

	}
}

void Robot::messageEvent(TgBot::Message::Ptr message)
{
	std::cout << "\033[KMessageEvent Called!\n";
	std::cout << "User " << message->from->username << " with id " << message->from->id << " sent: " << message->text << std::endl;
//
//	// This block was only for testing purposes and will be removed soon.
//	this->bot->getApi().sendMessage(message->chat->id, "Your Message was: " + message->text);
//	if(this->appendUser(message->from->languageCode, message->from->username, "", message->from->id))
//	{
//		std::cout << "Unknown user detected!\n";
//		//this->bot->getApi().sendMessage(message->from->id, "How is your name?");
//	}
//	else
//	{
//		std::cout << "Known User detected!\n";
//		bool process = this->checkAuthentification(message->text, message->from->id);
//	}
//	std::cout.flush();

	// build message
	Message m(message);

	// send
    ::capnp::MallocMessageBuilder msgBuilder;
    m.toCapnp(msgBuilder);
	this->czPub->send(msgBuilder);
}

void Robot::dispatchMessage(::capnp::FlatArrayMessageReader& reader)
{
    Message m;
    m.fromCapnp(reader);
    this->bot->getApi().sendMessage(m.getChatId(), m.getText());
}