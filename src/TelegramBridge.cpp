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
//	Message m;
//	m.setType(MsgType::message);
//	m.setText("test");
//	m.setChatId(1234);
//	m.setUserId(2345);
//    ::capnp::MallocMessageBuilder msgBuilder;
//    m.toCapnp(msgBuilder);

    // Get workspace path and loadd key from file
    std::string path = std::getenv("ROS_WORKSPACE");
    std::string keyPath = path + "/../src/telegram-client/telegram.key";
    std::ifstream input(keyPath, std::ifstream::in);
    if(input.good())
    {
        std::string key;
        input >> key;

        void* ctx = zmq_ctx_new();
        std::cout << "\033[30;48;5;51mBot Status: \033[31mOFFLINE\033[0m\n";
        std::cout << "API-key: " << key << '\n';
        Robot r(key, "Pinky", ctx);
        r.setupTelegram();
        r.receiveMessages();
        zmq_ctx_term(ctx);
    } else
    {
        std::cerr << "ERROR: could not open key File at: " << keyPath << "!\n";
    }
	return 0;
}
