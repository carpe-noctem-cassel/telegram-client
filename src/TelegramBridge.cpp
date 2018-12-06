#include <iostream>
#include "Robot.h"
#include <zmq.hpp>
#include "Message.h"

int main(int argc, char *argv[])
{
	Message m;
	m.setType(MsgType::message);
	m.setText("test");
	m.setChatId(1234);
	m.setUserId(2345);
	m.toCapnp();
	Robot r("603132548:AAH9RAl4fTiwi2-uxH-YJnzJlEqzC9rgjG8", "Pinky");
	r.setupTelegram();
    r.receiveMessages();
	return 0;
}
