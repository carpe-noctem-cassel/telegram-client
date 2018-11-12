#include <iostream>
#include <string>
#include <tgbot/tgbot.h>

void reply(TgBot::Bot &bot, TgBot::Message::Ptr message, std::string reply);

int main(int argc, char* argv[])
{
	std::string token = "603132548:AAH9RAl4fTiwi2-uxH-YJnzJlEqzC9rgjG8";

	TgBot::Bot bot(token);
	bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message){
		bot.getApi().sendMessage(message->chat->id, "Hi!");
	});
	bot.getEvents().onNonCommandMessage([&bot](TgBot::Message::Ptr message){reply(bot, message, "Yes Master!")});


	try {
        std::cout << "Bot username: " << bot.getApi().getMe()->username.c_str() << '\n';
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            std::cout << "Long poll started\n";
            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        std::cout << "error: " << e.what() << '\n';
    }

	return 0;
}

void reply(TgBot::Bot &bot, TgBot::Message::Ptr message, std::string reply)
{
	bot.getApi().sendMessage(message->chat->id, "Yes Master!")
	std::cout << "Replying: " << message->text << '\n';
}
