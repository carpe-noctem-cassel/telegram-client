#include <string>
#include <tgbot/tgbot.h>

class Message
{
	public:
		Message();
		Message(int chatId, int userId, std::string text);
		Message(TgBot::Message::Ptr);

	private:
		int chatId;										// The ID of the chat this message was sent or will bet sent.
		int userId;										// The User ID of the User who sent the Message or who this messsages adresses.
		int messageId;								// A unique message id. Don't know what to do with it, but can come in handy.
		int timestamp;								// The unix timestamp the message was sent at.
		std::string userName;					// The optional username of the User the message was sent from.
		std::string firstName;				// The users first name. Can be used to address the user.
		std::string lastName;					// The users last name.
		std::string text;							// The text of the message
		std::string languageCode			// Optional language code of the user.
};
