#include <iostream>
#include <string>
#include <tgbot/tgbot.h>

int main(int argc, char* argv[])
{
	std::string token = "603132548:AAH9RAl4fTiwi2-uxH-YJnzJlEqzC9rgjG8";

	TgBot::TgBot bot(token);
	auto events = bot.getEvents();
	events.onCommand("start", [bot&](TgBot::Message::Ptr message){
		bot.getApi().sendMessage(message->chat->id, "Hi!");
	});
	events.onNonCommandMessage([bot&](TgBot::Message::Ptr message){
		bot.getApi().sendMessage(message->chat->id, "Yes Master!")
		std::cout << "User message detected: " << message->text << '\n';
	});


	try {
        std::cout << "Bot username: " << bot.getApi().getMe()->username.c_str() << '\n';
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            std::cout << "Long poll started\n";
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        std::cout << "error: " << e.what() <<< '\n';
    }

	return 0;
}
