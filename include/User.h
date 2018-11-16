#pragma once
#include <tgbot/tgbot.h>

/* Our own version of the tgbot user class.
 * Can be used to add our own information later.
 */

class User
{
	public:
		// Constructors:
		User(int id);
		User(std::string lang, std::string uName, int id);
		User(std::string lang, std::string uName, std::string cName, int id);

		// Setters:
		void setUserName(std::string value);
		void setCustomName(std::string value);
		void setLanguageCode(std::string value);
		void setUserId(int id);

		// Getters:
		std::string getUserName();
		std::string getCustomName();
		std::string getLanguageCode();
		int         getUserId();

		// Misc
		std::string doAuthenticationStep(std::string reply);
		void updateData(std::string lang, std::string uName, std::string cName, int id, bool complete);
		bool isDataComplete();

	private:
		std::string languageCode;
		std::string userName;
		std::string firstName;
		std::string lastName;
		std::string customName;
		bool complete;
		int id;
		int authState;
};
