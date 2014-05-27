#ifndef BOTCORE_H
#define BOTCORE_H

#include "Connection.h"

/**
 * BotCore handles the primary connectivity of the application.
 * This class handles connecting to the chat server and maintaining the connection.
 * It also acts as a router for messages to the various modules.
 */

class BotCore
{
public:
	BotCore (const std::string & jid, const std::string & password);
	virtual ~BotCore ();
	void connect ();
private:
	Connection connection;
};

#endif /* BOTCORE_H */
