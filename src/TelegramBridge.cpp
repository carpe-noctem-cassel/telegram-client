#include <iostream>
#include "Robot.h"
#include <zmq.hpp>
#include "Message.h"
#include <fstream>

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

    std::ifstream input("telegram.key", std::ifstream::in);
    std::string key;
    input >> key

	Robot r(key, "Pinky");
	r.setupTelegram();
    r.receiveMessages();
	return 0;
}
