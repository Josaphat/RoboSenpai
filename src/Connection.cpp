#include "Connection.h"

#include <iostream>
#include <thread>
#include <gloox/message.h>
#include <yaml-cpp/yaml.h>

#include "BotCore.h"
#include "Channel.h"

using namespace std;
using namespace gloox;

// forward declare
ostream& operator<< (ostream& os, const Message& msg);

Connection::Connection(BotCore* bot, const std::string& jid, const std::string& password) : bot(bot)
{
    JID jID(jid);
    client = new Client(jid, password);
    client->registerMessageSessionHandler(this, 0);
    client->registerConnectionListener(this);

    client->setResource("bot");
}

Connection::~Connection()
{
}

void Connection::handleMessageSession(MessageSession* session)
{
    session->registerMessageHandler(this);
}

void Connection::handleMessage(const Message& msg, MessageSession* /*session*/)
{
    // TODO: Log this.
    cerr << "[::BotCore::handleMessage]" << "Unexpected message: " << msg << endl;
}

void Connection::onConnect()
{
    // TODO: Log this.
    cout << "== Connection successfully established ==" << endl;

    // Keep the connection alive
    // TODO: Clean this up. I don't fully understand Lambdas in C++11 yet.
    unsigned int intervalSeconds = 60;
    std::function<void (void) > func = std::bind(&Connection::keepAlive, this);
    std::thread([func, intervalSeconds]() {
        for (;;) {
            std::this_thread::sleep_for(std::chrono::seconds(intervalSeconds));
            func();
        }
    }).detach();

    // Join the rooms listed in the configuration file
    const std::string service = (*config) ["service"].as<std::string> ();
    const std::string nick = (*config) ["nick"].as<std::string> ();

    YAML::Node rooms = (*config) ["rooms"];

    for (YAML::const_iterator it = rooms.begin(); it != rooms.end(); ++it) {
        const std::string roomName = it->as<std::string> ();
        joinRoom(roomName, service, nick);
    }
}

void Connection::onDisconnect(enum gloox::ConnectionError e)
{
    if (e == gloox::ConnNoError) {
        // All Good.
    } else {
        // TODO: Log this.
        cerr << "== Connection error ==" << endl;
    }
}

bool Connection::onTLSConnect(const gloox::CertInfo& info)
{
    // TODO: Perhaps it would be a good idea to check the cert. Definitely do appropriate logging.
    cout << "[TLS Cert info] cipher: " << info.cipher << " compression: " << info.compression << " issuer: " << info.issuer << endl;
    return true;
}

void Connection::setConfig(YAML::Node* config)
{
    this->config = config;
}

/// Invokes the client's blocking infinite loop
void Connection::connect()
{
    client->connect(true);
}

void Connection::joinRoom(const std::string& room, const std::string& service, const std::string& nick)
{
    std::cout << "roomJID: " << room << "@" << service << "/" << nick << endl;
    JID roomJID(room + "@" + service + "/" + nick);
    Channel* myChannel = new Channel(bot, this, client, roomJID);
    bot->addChannel(myChannel);
    myChannel->join();
}

void Connection::keepAlive()
{
    // TODO: Log this with highest verbose.
    //std::cout << "White space ping." << std::endl;
    client->whitespacePing();
}

ostream& operator<< (ostream& os, const Message& msg)
{
    Message::MessageType mType = msg.subtype();
    os << "type: ";

    switch (mType) {
        case gloox::Message::Chat:
            os << "Chat";
            break;

        case gloox::Message::Error:
            os << "Error";
            break;

        case gloox::Message::Groupchat:
            os << "Groupchat";
            break;

        case gloox::Message::Headline:
            os << "Headline";
            break;

        case gloox::Message::Normal:
            os << "Normal";
            break;

        case gloox::Message::Invalid:
            os << "Invalid";
            break;

        default:
            break;
    }

    os << " from:'" << msg.from().resource() << "' subject: '" << msg.subject() << " body:'" << msg.body() << "'";
    return os;
}
