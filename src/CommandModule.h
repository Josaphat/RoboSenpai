#pragma once

#include "Module.h"
#include <vector>

//
/// Provides an easy way for implementing classes to provide commands to a chat.
/// This class implements the common aspects of being a command module.
//
class CommandModule : public Module {
public:
    CommandModule(const std::string& name,
                  const std::vector<std::string>& commands,
                  const char& commandChar);
    virtual ~CommandModule();
public: // Overrides
    virtual void accept(Channel* src, const gloox::Message& msg);
public:
    virtual void commandAction(Channel* src, const std::vector<std::string>& args) = 0;
private:
    std::vector<std::string> commands;
    char commandChar;
};
