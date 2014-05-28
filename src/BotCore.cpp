#include "BotCore.h"

#include <string>

#include <gloox/message.h>

#include "Channel.h"
#include "Connection.h"

BotCore::BotCore (const std::string & jid, const std::string & pass) : connection(new Connection(this, jid, pass))
{
}


typedef std::vector<Channel *>::iterator ChanIter;
BotCore::~BotCore ()
{
    for(ChanIter it = channels.begin(); it != channels.end(); it++) {
        delete *it;
    }
}

void BotCore::connect (YAML::Node * config)
{
    connection->setConfig(config);
	connection->connect ();
}

void BotCore::processMessage(Channel * src, const gloox::Message & msg, bool priv)
{
    // TODO: Process the message
    src->speak("(robosenpai) " + msg.body () + ", from " + msg.from ().resource ());
}

void BotCore::addChannel(Channel * channel)
{
    channels.push_back(channel);
}
