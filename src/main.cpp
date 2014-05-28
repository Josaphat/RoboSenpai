#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>

#include "BotCore.h"

using namespace std;

int main (int argc, char * argv [])
{
    YAML::Node config;
    try {
        config = YAML::LoadFile("../config.yml");
    } catch (YAML::BadFile & e) {
        cerr << "Error loading config.yml : " << e.what() << endl;
    }

    try {
        const std::string jid = config["jid"].as<std::string>();
        const std::string password = config["password"].as<std::string>();

        BotCore bot (jid, password);

        bot.connect (&config);
    } catch (YAML::Exception & e) {
        cerr << "Error getting data from config file : " << e.what() << endl;
    }

	cout << "Returned..." << endl;
	for (;;) {
            // This infinite loop is for debugging purposes to make sure that
            // the host application (console window) doesn't terminate before
            // the output of the application can be displayed.

            // TODO: Add logging
	}
	return 1;
}
