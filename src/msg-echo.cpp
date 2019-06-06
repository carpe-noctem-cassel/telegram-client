#include "telegram_msgs/message.capnp.h"
#include "Message.h"
#include <capnzero/Common.h>
#include <capnzero/Subscriber.h>

#include <capnp/common.h>
#include <capnp/message.h>
#include <capnp/serialize-packed.h>

#include <SystemConfig.h>

#include <signal.h>
#include <thread>
#include <ctime>


// This file mirrors the design of capnzeros echo!
// This will be removed if capnzero echo gets the capability to echo any message type!


void callback(::capnp::FlatArrayMessageReader& reader)
{
    std::cout << "Called callback..." << std::endl;
    Message m;
    m.fromCapnp(reader);
    std::cout << "\033[31;1m" << m.getUserName() << '(' << m.getUserId() << ")(" << m.getChatId() << ")\033[0m at ";
    std::cout << m.getTimestamp() << ": " << m.getText() << std::endl;
//    std::cout << reader.getRoot<telegram_msgs::Message>().toString().flatten().cStr() << std::endl;
}

static bool interrupted = false;
static void s_signal_handler(int signal_value)
{
    interrupted = true;
}

static void s_catch_signals(void)
{
    struct sigaction action;
    action.sa_handler = s_signal_handler;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGTERM, &action, NULL);
}

int main(int argc, char** argv)
{
    s_catch_signals();

    if (argc <= 1) {
        std::cerr << "Synopsis: rosrun telegram-client msgecho \"Topic that should be listened to!\"" << std::endl;
        return -1;
    }

//    for (size_t i = 0; i < argc; i++) {
//        std::cout << "Param " << i << ": '" << argv[i] << "'" << std::endl;
//    }

    void* ctx = zmq_ctx_new();
    essentials::SystemConfig *sc = essentials::SystemConfig::getInstance();
    capnzero::Subscriber* sub = new capnzero::Subscriber(ctx, argv[1]);
//    sub->connect(capnzero::CommType::IPC, "@capnzero.ipc");
//    sub->connect(capnzero::CommType::UDP, "224.0.0.2:5555");
    sub->connect(capnzero::CommType::INT, "udp://224.0.0.2:5555");
    sub->subscribe(&callback);

    while (!interrupted) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    delete sub;

    zmq_ctx_term(ctx);

    return 0;
}