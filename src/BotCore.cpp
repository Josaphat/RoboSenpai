#include "BotCore.h"

#include <string>

#include <gloox/message.h>
#include <yaml-cpp/yaml.h>

#include "Channel.h"
#include "Connection.h"
#include "Module.h"

BotCore::BotCore(const std::string& jid, const std::string& nick, const std::string& pass)
    : JID(jid), nick(nick), connection(new Connection(this, jid, pass)), channels(), modules()
{
}


typedef std::vector<Channel*>::iterator ChanIter;
BotCore::~BotCore()
{
    for (ChanIter it = channels.begin(); it != channels.end(); it++) {
        delete *it;
    }
}

void BotCore::connect(YAML::Node* config)
{
    connection->setConfig(config);
    // Add all the modules in the config file
    YAML::Node modules = (*config)["modules"];

    for (YAML::const_iterator it = modules.begin(); it != modules.end(); ++it) {
        const std::string moduleName = it->as<std::string>();
        this->modules.push_back(Module::moduleMap[moduleName]);
    }

    connection->connect();
}

void BotCore::processMessage(Channel* src, const gloox::Message& msg, bool /*priv*/)
{
    // TODO: Process system-level messages

    // Pass the message to all of the modules
    for (Module* m : modules) {
        try {
            m->accept(src, msg);
        }
        catch (...) {
            std::cout << "Plugin exception error." << std::endl;
        }
    }
}

void BotCore::addChannel(Channel* channel)
{
    channels.push_back(channel);
}
