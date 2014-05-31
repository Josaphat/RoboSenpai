#include "CommandModule.h"

#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <gloox/message.h>

CommandModule::CommandModule(const std::string& name, const std::vector<std::string>& commands, const char& commandChar)
    : Module(name), commands(commands), commandChar(commandChar)
{
}

CommandModule::~CommandModule()
{
}

// When the command module gets a message it needs to break it up, check the
// command and then pass it along by calling the commandAction() method.
void CommandModule::accept(Channel* src, const gloox::Message& msg)
{
    std::string msgText = msg.body();

    // If it doesn't start with the command character then it's not a command
    if (msgText[0] == commandChar) {
        // Remove the command character
        msgText = msgText.substr(1);

        // Split the message up on the whitespace and store the tokens
        std::vector<std::string> tokens;
        std::string buf;
        std::stringstream ss(msgText);
        while (ss >> buf) {
            tokens.push_back(buf);
        }

        if (!tokens.empty()) {
            // Make sure this is the command we're looking for
            if (std::find(commands.begin(), commands.end(), tokens[0]) != commands.end()) {
                // Don't send the command as arg
                tokens.erase(tokens.cbegin());
                commandAction(src, tokens);
            }
        }
    }
}
