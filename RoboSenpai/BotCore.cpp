#include "BotCore.h"

#include <iostream>
#include <string>

#include <gloox/message.h>
#include <gloox/mucroom.h>

#include "Channel.h"

using namespace std;
using namespace gloox;

BotCore::BotCore (const string & jid, const string & pass)
{
	JID jID (jid);
	client = new Client (jid, pass);
	client->registerMessageSessionHandler (this, 0);
	client->registerConnectionListener (this);

	client->setResource ("bot");
	client->connect (true);
}


BotCore::~BotCore ()
{
}

ostream& operator<<(ostream& os, const Message& msg)
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
	os << " from:'" << msg.from ().resource() << "' subject: '" << msg.subject() << " body:'" << msg.body () << "'";
	return os;
}

void BotCore::handleMessageSession (MessageSession * session)
{
	session->registerMessageHandler (this);
}

void BotCore::handleMessage (const Message& msg, MessageSession* session)
{
	cerr << "[::BotCore::handleMessage]" << "Unexpected message: " << msg << endl;
}

void BotCore::onConnect ()
{
	cout << "== Connection successfully established ==" << endl;
	// The connection has been successfully established
	// TODO: Join the MUCs listed in a configuration file.
	joinRoom ("97498_bottest", "conf.hipchat.com", "Josaphat Valdivia");
	//joinRoom ("97498_the_chuckledome", "conf.hipchat.com", "Josaphat Valdivia");
}

void BotCore::onDisconnect (enum gloox::ConnectionError e)
{
	if (e == gloox::ConnNoError) {
		// All Good.
	}
	else {
		cerr << "== Connection error ==" << endl;
	}
}

bool BotCore::onTLSConnect (const gloox::CertInfo &info)
{
	// TODO: Perhaps it would be a good idea to check the cert
	return true;
}

void BotCore::processMessage (MUCRoom* room, const Message& msg, bool priv)
{
    // TODO: What is this?
}

void BotCore::joinRoom (const std::string& room, const std::string& service, const std::string& nick)
{
	Channel * myHandler = new Channel (*this);
	JID roomJID (room + "@" + service + "/" + nick);
	rooms.push_back(new MUCRoom (client, roomJID, myHandler, 0));
	rooms.back ()->join (Presence::Available, "ROBOSENPAI IN THE HAUUUUUS");
}
