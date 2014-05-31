#pragma once

#include <string>
#include <vector>

namespace gloox {
    class Message;
}

namespace YAML {
    class Node;
}

class Connection;
class Channel;
class Module;

//
/// BotCore holds references to the modules and the chats as well as well as
/// a reference to the object in charge of maintaining the connection with
/// the HipChat servers.
//
class BotCore {
public:
    BotCore(const std::string& jid, const std::string& nick, const std::string& password);
    virtual ~BotCore();

    //
    /// The connect() method blocks; it loads the configured modules and
    /// establishes the XMPP connection according to the configuration.
    //
    void connect(YAML::Node* config);

    //
    /// Processes an incoming message and forwards it to the appropriate modules.
    //
    void processMessage(Channel* src, const gloox::Message& msg, bool priv);
    void addChannel(Channel* channel);

    //
    /// The full JID the bot uses to connect
    //
    const std::string JID;

    //
    /// The bot's nick.
    //
    const std::string nick;
private:
    Connection* connection;
    std::vector<Channel*> channels;
    std::vector<Module*> modules;

private: // Hide these
    BotCore(const BotCore&) {}
    BotCore& operator=(const BotCore&) { return *this;}
};

