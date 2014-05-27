#include "Connection.h"

#include <iostream>
#include <gloox/message.h>

#include "BotCore.h"
#include "Channel.h"

using namespace std;
using namespace gloox;

ostream& operator<<(ostream& os, const Message & msg)
{
	Message::MessageType mType = msg.subtype ();
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
	os << " from:'" << msg.from ().resource () << "' subject: '" << msg.subject () << " body:'" << msg.body () << "'";
	return os;
}

Connection::Connection (BotCore * bot, const std::string & jid, const std::string & password) : bot (bot)
{
	JID jID (jid);
	client = new Client (jid, password);
	client->registerMessageSessionHandler (this, 0);
	client->registerConnectionListener (this);

	client->setResource ("bot");
}

Connection::~Connection ()
{
}

void Connection::handleMessageSession (MessageSession * session)
{
	session->registerMessageHandler (this);
}

void Connection::handleMessage (const Message& msg, MessageSession* session)
{
	// TODO: Log this.
	cerr << "[::BotCore::handleMessage]" << "Unexpected message: " << msg << endl;
}

void Connection::onConnect ()
{
	// TODO: Log this.
	cout << "== Connection successfully established ==" << endl;

	// TODO: Join the MUCs listed in a configuration file.
	joinRoom ("97498_botdev", "conf.hipchat.com", "Josaphat Valdivia");
	//joinRoom ("97498_the_chuckledome", "conf.hipchat.com", "Josaphat Valdivia");
}

void Connection::onDisconnect (enum gloox::ConnectionError e)
{
	if (e == gloox::ConnNoError) {
		// All Good.
	}
	else {
		// TODO: Log this.
		cerr << "== Connection error ==" << endl;
	}
}

bool Connection::onTLSConnect (const gloox::CertInfo &info)
{
	// TODO: Perhaps it would be a good idea to check the cert. Definitely do appropriate logging.
	cout << "[TLS Cert info] cipher: " << info.cipher << " compression: " << info.compression << " issuer: " << info.issuer << endl;
	return true;
}

/// Invokes the client's blocking infinite loop
void Connection::connect ()
{
	client->connect (true);
}

void Connection::joinRoom (const std::string& room, const std::string& service, const std::string& nick)
{
    JID roomJID (room + "@" + service + "/" + nick);
	Channel * myChannel = new Channel (bot, this, client, roomJID);
	bot->addChannel(myChannel);
	myChannel->join ();
}
