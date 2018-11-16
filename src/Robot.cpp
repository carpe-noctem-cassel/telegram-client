#include "Robot.h"
#include <iostream>

// =========================================================
// Constructors:

Robot::Robot(std::string key)
{
	//this->Robot(key, "");
}

Robot::Robot(std::string key, std::string rName)
{
	std::cout << "Creating a new Robot.\n";
	this->apiKey = key;
	this->reciving = false;
	this->setRobotName(rName);
}

// ==========================================================
// Setters:

void Robot::setRobotName(std::string name)
{
	this->robotName = name;
}

void Robot::setRecivingStatus(bool value)
{
	this->reciving = value;
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

bool Robot::getRecivingStatus()
{
	return this->reciving;
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

void Robot::reciveMessages()
{
	std::cout << "reciveMessage was called.\n";
	if(this->reciving)
	{
		try
		{
			TgBot::TgLongPoll longPoll(*(this->bot));
			while(this->reciving)
			{
				longPoll.start();
				this->killable = true;
			}
		}
		catch(TgBot::TgException &e)
		{
			std::cout << e.what();
		}
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
		if(this->killable)
		{
			//this->setRecivingStatus(false);
			this->bot->getApi().sendMessage(message->chat->id, "Bye!");
		}
		this->killable = false;

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
		this->bot->getApi().sendMessage(message->from->id, "How is your name?");
	}
	else
	{
		std::cout << "Known User detected!\n";
		int id = this->getUserIndexById(message->from->id);
		if(id >= 0)
		{
			if(!this->users[id].isDataComplete())
			{
				std::cout << "User data is incomplete.\n";
				if(message->text.find("my name is ") == 0)
				{
					std::string name = message->text.substr(11);
					std::cout << "Set custom name to " << name << '\n';
					this->updateCustomName(name, message->from->id);
					this->bot->getApi().sendMessage(message->from->id, "Thanks!");
				}
			}
			else
			{
				std::cout << "User data is complete.\n";
			}
		}
	}
	std::cout.flush();
}
