#pragma once

#include "Module.h"
#include <vector>

//
/// Provides an easy way for implementing classes to provide commands to a chat.
/// This class implements the common aspects of being a command module.
//
class CommandModule : public Module {
public:
    //
    /// Constructor for a command module which takes the name of the module (for
    /// the configuration file), a list of commands this module will respond to,
    /// and the command character (usually '!').
    //
    CommandModule(const std::string& name,
                  const std::vector<std::string>& commands,
                  const char& commandChar);
    virtual ~CommandModule();
public: // Overrides
    virtual void accept(Channel* src, const gloox::Message& msg);
public:
    //
    /// Defines the actual functionality of the module.
    /// This method provides the implementor with the source of the command and
    /// the arguments that were passed to it. If this method is invoked it's
    /// because a valid command was issued in the src Channel.
    //
    virtual void commandAction(Channel* src, const std::vector<std::string>& args) = 0;

private:
    // The commands that the module will respond to (the same action can be
    // invoked with various command names; e.g., `!PennyArcade` and the
    // abbreviated form, `!pa`). This list is just the "PennyArcade" and "pa"
    // parts.
    std::vector<std::string> commands;

    // The command flag character. In the `!pa` example above, '!' is the command
    // char.
    char commandChar;
};
