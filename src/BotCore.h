#ifndef BOTCORE_H
#define BOTCORE_H

#include <vector>

#include <gloox/client.h>
#include <gloox/connectionlistener.h>
#include <gloox/messagehandler.h>
#include <gloox/messagesessionhandler.h>
#include <gloox/mucroom.h>

#include "SystemCommandsProcessor.h"

/**
 * BotCore handles the primary connectivity of the application.
 * This class handles connecting to the chat server and maintaining the connection.
 * It also acts as a router for messages to the various modules.
 */

class BotCore : public gloox::MessageSessionHandler, gloox::MessageHandler, gloox::ConnectionListener
{
public:
	BotCore (const std::string & jid, const std::string & password);
	virtual ~BotCore ();
	virtual void handleMessageSession (gloox::MessageSession * session);
	virtual void handleMessage (const gloox::Message & msg, gloox::MessageSession * session = 0);
	virtual void onConnect ();
	virtual void onDisconnect (gloox::ConnectionError e);
	virtual bool onTLSConnect (const gloox::CertInfo & info);

	void processMessage (gloox::MUCRoom * room, const gloox::Message & msg, bool priv);
private:
	void joinRoom (const std::string & room, const std::string & service, const std::string & nick);

	gloox::Client * client;
	std::vector<gloox::MUCRoom *> rooms;
	SystemCommandsProcessor sysCmd;
};

#endif /* BOTCORE_H */
