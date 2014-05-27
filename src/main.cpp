#include <iostream>
#include <string>

#include "BotCore.h"

using namespace std;


int main (int argc, char * argv [])
{
    // TODO: Read in the chat info from a configuration file
	BotCore bot ("97498_713477@chat.hipchat.com", "ThunderBurdsAreG0");
	bot.connect ();
	cout << "Returned..." << endl;
	for (;;) {
        // This infinite loop is for debugging purposes to make sure that
        // the host application (console window) doesn't terminate before
        // the output of the application can be displayed.
		
		// TODO: Add logging
	}
	return 1;
}
