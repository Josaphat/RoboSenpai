#include <iostream>
#include <string>

#include <gloox/client.h>
#include <gloox/message.h>
#include <gloox/messagehandler.h>
#include <gloox/connectionlistener.h>

#include "BotCore.h"

using namespace std;
using namespace gloox;


int main (int argc, char * argv [])
{
    // TODO: Read in the chat info from a configuration file
	BotCore bot ("97498_713477@chat.hipchat.com", "ThunderBurdsAreG0");
	cout << "Returned..." << endl;
	for (;;) {
        // This infinite loop is for debugging purposes on Windows: if you run
        // the application and it terminates, you can't see any last-minute
        // print statements before the window closes
	}
	return 1;
}
