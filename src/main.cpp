#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>

#include "BotCore.h"

int main(int, char* [])
{
    YAML::Node config;

    try {
        config = YAML::LoadFile("../config.yml");
    }
    catch (YAML::BadFile& e) {
        std::cerr << "Error loading config.yml : " << e.what() << std::endl;
    }

    try {
        const std::string jid = config["jid"].as<std::string>();
        const std::string nick = config["nick"].as<std::string>();
        const std::string password = config["password"].as<std::string>();

        BotCore bot(jid, nick, password);

        bot.connect(&config);
    }
    catch (YAML::Exception& e) {
        std::cerr << "Error getting data from config file : " << e.what() << std::endl;
    }

    std::cout << "Returned..." << std::endl;

    for (;;) {
        // This infinite loop is for debugging purposes to make sure that
        // the host application (console window) doesn't terminate before
        // the output of the application can be displayed.

        // TODO: Add logging
    }

    return 1;
}
