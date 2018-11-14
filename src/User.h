#pragma once
#include <tgbot/tgbot.h>

/* Our own version of the tgbot user class.
 * Can be used to add our own information later.
 */

class User
{
	public:
		User(int id);
		User(std::string lang, std::string uName, int id);
		User(std::string lang, std::string uName, std::string cName, int id);

		// Setters:
		void setUserName(std::string value);
		void setCustomName(std::string value);
		void setLanguageCode(std::string value);
		void setUserId(int);

		// Getters:
		std::string getUserName();
		std::string getCustomName();
		std::string getLanguageCode();
		int         getUserId();

		// Misc
		void updateData(std::string lang, std::string uName, std::string cName, int id);

	private:
		std::string languageCode;
		int32 id;
		std::string userName;
		std::string customName;
}
