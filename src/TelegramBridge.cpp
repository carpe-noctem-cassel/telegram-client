#include <iostream>
#include "Robot.h"
#include <zmq.hpp>
#include "Message.h"
#include <fstream>

#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    // Only for testing purposes
	Message m;
	m.setType(MsgType::message);
	m.setText("test");
	m.setChatId(1234);
	m.setUserId(2345);
    ::capnp::MallocMessageBuilder msgBuilder;
    m.toCapnp(msgBuilder);

    std::string path = std::getenv("HOME");

    std::ifstream input(path + "/teamwork-ws/src/telegram-client/telegram.key", std::ifstream::in);
    std::string key;
    input >> key;

	Robot r(key, "Pinky");
	r.setupTelegram();
    r.receiveMessages();
	return 0;
}
