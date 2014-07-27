#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>

#include "BotCore.h"

int main(int, char* [])
{
    YAML::Node config;

    for(;;) {
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

            std::cout << "Initializing BotCore\n\tjid: " << jid << "\n\tnick: " << nick << "\n\tpassword: " << password << std::endl;
            BotCore bot(jid, nick, password);

            std::cout << "Connecting..." << std::endl;
            bot.connect(&config);
        }
        catch (YAML::Exception& e) {
            std::cerr << "Error getting data from config file : " << e.what() << std::endl;
        }

        std::cout << "Returned..." << std::endl;
        std::cout << "Rerunning." << std::endl;
    }

    return 1;
}
