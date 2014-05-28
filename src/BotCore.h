#ifndef BOTCORE_H
#define BOTCORE_H

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

/**
 * BotCore holds references to the modules and the chats as well as well as
 * a reference to the object in charge of maintaining the connection with
 * the HipChat servers.
 */
class BotCore
{
public:
	BotCore (const std::string & jid, const std::string & password);
	virtual ~BotCore ();
	void connect (YAML::Node * config);
	void processMessage(Channel * src, const gloox::Message & msg, bool priv);
	void addChannel(Channel * channel);
private:
	Connection * connection;
	std::vector<Channel *> channels;
};

#endif /* BOTCORE_H */
