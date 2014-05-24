#include <iostream>
#include <string>

#include <gloox/client.h>
#include <gloox/message.h>
#include <gloox/messagehandler.h>
#include <gloox/connectionlistener.h>

#include "BotCore.h"

using namespace std;
using namespace gloox;


typedef struct
{
	int butts;
	int buuts2;
	int buuts3;
} mybutts;

mybutts buttfunc ()
{
	mybutts butts;
	butts.butts = 0;
	butts.buuts2 = 1;
	butts.buuts3 = 2;
	return butts;
}

int main (int argc, char * argv [])
{
	buttfunc ();


	BotCore bot ("97498_713477@chat.hipchat.com", "ThunderBurdsAreG0");
	cout << "Returned..." << endl;
	for (;;) {

	}
	return 1;
}
