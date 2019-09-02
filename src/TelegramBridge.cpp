#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <zmq.hpp>
#include "Robot.h"
//#include "Message.h"


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
    std::cout << "Trying to read AAPI-Key . . .\n";
    if(std::getenv("KEY_PATH") != NULL)
    {
        std::string path = std::getenv("KEY_PATH");
        std::cout << "ROSWS: " << path << '\n';
        std::ifstream input(path, std::ifstream::in);
        if(input.good())
        {
            std::cout << "getting API-Key . . .\n";
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
            std::cerr << "ERROR: could not open key File at: " << path << "!\n";
        }
    } else
    {
        std::cerr << "ERROR: Could not find the environment Variable \"KEY_PATH\"!\n"
                  << "Please include it into your .bashrc file and restart your terminal.\n"
                  << "export KEY_PATH=<path/to/your/keyfile>\n";
    }
	return 0;
}
