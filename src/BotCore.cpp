#include "BotCore.h"

#include <iostream>
#include <string>

#include <gloox/client.h>
#include <gloox/message.h>
#include <gloox/mucroom.h>

#include "Channel.h"

using namespace std;
using namespace gloox;

BotCore::BotCore (const string & jid, const string & pass) : connection(this, jid, pass)
{
}


BotCore::~BotCore ()
{
}

void BotCore::connect ()
{
	connection.connect ();
}