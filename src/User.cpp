#include "User.h"

User::User(std::string lang, std::string uName, std::string cName, int id)
{
	this->updateData(lang, uName, cName, id, true);
	this->authState = 0;
}

User::User(std::string lang, std::string uName, int id)
{
	this->updateData(lang, uName, "", id, false);
	this->authState = 0;
}

User::User(int id)
{
	this->updateData("", "", "", id, false);
	this->authState = 0;
}

// ==============================================================
// Setters:

void User::setUserName(std::string value)
{
	this->userName = value;
}

void User::setCustomName(std::string value)
{
	this->customName = value;
}

void User::setLanguageCode(std::string value)
{
	this->languageCode = value;
}

void User::setUserId(int id)
{
	this->id = id;
}

// ==============================================================
// Getters:

std::string User::getUserName()
{
	return this->userName;
}

std::string User::getCustomName()
{
	return this->customName;
}

std::string User::getLanguageCode()
{
	return this->languageCode;
}

int User::getUserId()
{
	return this->id;
}

bool User::isUserAuthenticated()
{
	return this->authenticated;
}

// ===============================================================
// Misc:

std::string User::doAuthenticationStep(std::string reply)
{
	switch(this->authState)
	{
		case 0:
			// Unauthorised User
			// -> Ask for the first name
			this->authState++;
			return "Tell me your first name.";
		case 1:
			// Partially authorised User
			// -> ask for last name
			this->authState++;
			// test for viable response
			return "Tell me your last name.";
		case 2:
			// Partially authorised User
			// -> ask for the name we should call him
			this->authState++;
			// test for viable response
			return "Tell me how I should call you.";
		case 3:
			// got all importent data
			// -> ask for the prefered language code
			this->authState++;
		default:
			this->authenticated = true;
			return "";
	}
}

void User::updateData(std::string uName, std::string cName, std::string lang, int id, bool complete)
{
	// Setting internal values using setters.
	// This will allow for sanity checking if needed.
	this->setUserName(uName);
	this->setCustomName(cName);
	this->setLanguageCode(lang);
	this->setUserId(id);
	std::cout << "setting completeness to " << (complete ? "TRUE" : "FALSE") << '\n';
	this->authenticated = false;
}

/*bool User::isDataComplete()
{
	// Is probably not needed anymore
	if(this->complete == false)
	{
		std::cout << "User complete is not set.\nTesting . . .\n";
		bool result = true;
		if(this->getUserName() == "")
		{
			std::cout << "Username not found.\n";
			result = false;
		}
		if(this->getCustomName() == "")
		{
			std::cout << "Custom name is not set.\n";
			result = false;
		}
		if(this->getLanguageCode() == "")
		{
			std::cout << "language code not found.\n";
			result = false;
		}
		this->complete = result;
		std::cout << "The test returns " << (result ? "TRUE" : "FALSE") << '\n';
		std::cout.flush();
		return result;
	}
	else
	{
		std::cout << "Test returns TRUE\n";
		std::cout.flush();
		return true;
	}
}*/
