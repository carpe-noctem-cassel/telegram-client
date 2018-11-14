#include <iostream>
#include <string>
#include <tgbot/tgbot.h>
#include <fstream>

void reply(TgBot::Bot &bot, TgBot::Message::Ptr message, std::string reply);

int main(int argc, char* argv[])
{
	std::string token = "603132548:AAH9RAl4fTiwi2-uxH-YJnzJlEqzC9rgjG8";

	TgBot::Bot bot(token);
	bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message){
		bot.getApi().sendMessage(message->chat->id, "Hi!");
	});
	bot.getEvents().onNonCommandMessage([&bot](TgBot::Message::Ptr message){reply(bot, message, "Yes Master!");
		bot.getApi().sendMessage(message->chat->id, "Your msg was: " + message->text);
	});


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
	bot.getApi().sendMessage(message->chat->id, "Yes Master!");
	std::string text = message->text;
	std::cout << "Replying: " << text << '\n';
	std::ifstream in("logs.txt");
	in >> message->chat->id >> text;
	in.close();
}
