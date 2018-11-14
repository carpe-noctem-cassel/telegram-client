#include <tgbot/tgbot.h>
#include <string>
#include <vector>
#include "User.h"

class Robot
{
	public:
		Robot(std::string key);
		Robot(std::string key, std::string rName);

		// Setters:
		void setRobotName(std::string name);

		// Getters:
		std::string getChatBotName();
		std::string getRobotName();
		int getOwnUserId();

		// Manage human info
		void appendUser(std::string lang, std::string uName, std::sring cName, int id);
		void updateCustomName(std::string cName, int id);
		void updateUserName(std::string uName, int id);
		void updateLanguageCode(std::string lang, int id);

		// Misc
		void addCommand(std::string text);
		void removeCommand(std::string text);

	private:
		std::string apiKey;
		std::string chatBotName;
		std::string robotName;
		int userId;
		std::vector <std::string> commands;
		std::vector <User> users;

}
