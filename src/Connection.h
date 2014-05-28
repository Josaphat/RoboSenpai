#pragma once

#include <gloox/client.h>
#include <gloox/connectionlistener.h>
#include <gloox/messagehandler.h>
#include <gloox/messagesessionhandler.h>
#include <gloox/mucroom.h>

#include <yaml-cpp/yaml.h>

#include "SystemCommandsProcessor.h"

namespace YAML {
    class Node;
}

class BotCore;
class Channel;

class Connection : public gloox::MessageSessionHandler, gloox::MessageHandler, gloox::ConnectionListener
{
public:
	Connection (BotCore * bot, const std::string & jid, const std::string & password);
	virtual ~Connection ();

	void setConfig(YAML::Node * config);
	void connect ();

protected:
	void joinRoom (const std::string & room, const std::string & service, const std::string & nick);
	void keepAlive ();

public: // Inherited
	virtual void handleMessageSession (gloox::MessageSession * session);
	virtual void handleMessage (const gloox::Message & msg, gloox::MessageSession * session = 0);
	virtual void onConnect ();
	virtual void onDisconnect (gloox::ConnectionError e);
	virtual bool onTLSConnect (const gloox::CertInfo & info);

private:
	gloox::Client * client;
	BotCore * bot;
	SystemCommandsProcessor sysCmd;
	YAML::Node * config;
};
