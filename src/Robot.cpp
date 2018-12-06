#include "Robot.h"

#include <capnp/common.h>
#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include <kj/array.h>

#include <capnzero-base-msgs/string.capnp.h>
#include <iostream>

// =========================================================
// Constructors/Destructor:
Robot::Robot(std::string key, std::string rName)
{
	std::cout << "Creating a new Robot.\n";
	this->apiKey = key;
	this->setRobotName(rName);
	this->context = zmq_ctx_new();
	this->czPub = new capnzero::Publisher(context, "voice");
	this->czPub->bind(capnzero::CommType::IPC, "@capnzero.ipc");
}

Robot::~Robot(){
	// clean up capnzero stuff
	delete this->czPub;
	zmq_ctx_term(this->context);
}

// ==========================================================
// Setters:

void Robot::setRobotName(std::string name)
{
	this->robotName = name;
}

// =========================================================
// Getters:

std::string Robot::getChatBotName()
{
	return this->chatBotName;
}

std::string Robot::getRobotName()
{
	return this->robotName;
}

std::string Robot::getBotInfoString()
{
	std::string result = "Telegram name: " + this->getChatBotName() + '\n';
	result += "Running on the robot \"" + this->getRobotName() + "\"\n";
	result += "Amount of known users: " + this->getUserCount() + '\n';
	return result;
}

bool Robot::getReceivingStatus()
{
	return this->running;
}

int Robot::getOwnUserId()
{
	return this->userId;
}

unsigned int Robot::getUserCount()
{
	return this->users.size();
}

// ==========================================================
// Manage human info:

bool Robot::appendUser(std::string lang, std::string uName, std::string cName, int id)
{
	if(!isIdKnown(id))
	{
		this->users.push_back(User(lang, uName, id));
		return true;
	}
	return false;
}

unsigned int Robot::getUserIndexById(int id)
{
	for(unsigned int i = 0; i < this->users.size(); ++i)
	{
		if(this->users[i].getUserId() == id)
		{
			return i;
		}
	}
	return -1;
}

void Robot::updateCustomName(std::string cName, int id)
{
	int index = this->getUserIndexById(id);
	this->users[index].setCustomName(cName);
}

void Robot::updateUserName(std::string uName, int id)
{
	int index = this->getUserIndexById(id);
	this->users[index].setUserName(uName);
}

void Robot::updateLanguageCode(std::string lang, int id)
{
	int index = this->getUserIndexById(id);
	this->users[index].setLanguageCode(lang);
}

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

bool Robot::checkAuthentification(std::string reply, int id)
{
	if(!this->isUserAuthenticated(id))
	{
		std::cout << "User not authenticated.\n";
		std::string request = this->users[this->getUserIndexById(id)].doAuthenticationStep(reply);
		if(request != "")
		{
			std::cout << "Sending request: " << request << '\n';
			this->bot->getApi().sendMessage(id, request);
		}
	}
	else
	{
		std::cout << "User is authenticated.\n";
	}
	std::cout.flush();
}

bool Robot::isUserAuthenticated(int id)
{
	return this->users[this->getUserIndexById(id)].isUserAuthenticated();
}

// ==================================================================
// Misc:

void Robot::addCommand(std::string text)
{
	this->commands.push_back(text);
}

void Robot::removeCommand(std::string text)
{
	for(unsigned int i = 0; i < this->commands.size(); ++i)
	{
		if(this->commands[i] == text)
		{
			this->commands.erase(this->commands.begin() + i);
			break;
		}
	}
}

void Robot::setupTelegram()
{
	std::cout << "setupTelegram was called.\n";
	this->bot = new TgBot::Bot(this->apiKey);
	this->bot->getEvents().onCommand("start", [this](TgBot::Message::Ptr message){
		this->commandEvent(message);
	});
	this->bot->getEvents().onCommand("quit", [this](TgBot::Message::Ptr message){
		this->commandEvent(message);
	});
	this->bot->getEvents().onNonCommandMessage([this](TgBot::Message::Ptr message){this->messageEvent(message);});
	try
	{
		this->chatBotName = this->bot->getApi().getMe()->username;
	}
	catch(TgBot::TgException &e)
	{
		std::cerr << "Error: " << e.what();
	}
}

void Robot::receiveMessages()
{
	std::cout << "reciveMessage was called.\n";

		try
		{
			TgBot::TgLongPoll longPoll(*(this->bot));
			while(this->running)
			{
				longPoll.start();
			}
		}
		catch(TgBot::TgException &e)
		{
			std::cout << e.what();
		}

}

// ========================================================================
// Event handlers for Telegram

void Robot::commandEvent(TgBot::Message::Ptr message)
{
	if(message->text == "/start")
	{
		std::cout << "recived Start\n";
		//this->killable = true;
		this->bot->getApi().sendMessage(message->chat->id, "Hi!");
	}
	else if(message->text == "/quit")
	{
		std::cout << "recived quit\n";
		if(this->running)
		{
			//this->setRecivingStatus(false);
			this->bot->getApi().sendMessage(message->chat->id, "Bye!");
		}
		this->running = false;

	}
}

void Robot::messageEvent(TgBot::Message::Ptr message)
{
	//std::cout << "MessageEvent Called!\n";
	std::cout << "User " << message->from->username << " with id " << message->from->id << " sent: " << message->text << '\n';
	this->bot->getApi().sendMessage(message->chat->id, "Your Message was: " + message->text);
	if(this->appendUser(message->from->languageCode, message->from->username, "", message->from->id))
	{
		std::cout << "Unknown user detected!\n";
		//this->bot->getApi().sendMessage(message->from->id, "How is your name?");
	}
	else
	{
		std::cout << "Known User detected!\n";
		bool process = this->checkAuthentification(message->text, message->from->id);
	}
	std::cout.flush();

	// build message
	::capnp::MallocMessageBuilder msgBuilder;
	capnzero::String::Builder beaconMsgBuilder = msgBuilder.initRoot<capnzero::String>();
	beaconMsgBuilder.setString(message->text);
	// send
	this->czPub->send(msgBuilder);
}
