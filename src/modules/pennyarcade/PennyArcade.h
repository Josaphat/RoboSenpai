#pragma once

#include "../../CommandModule.h"

class Channel;

//
/// The PennyArcade module implementation. Scrapes the comic off of
/// http://penny-arcade.com/comic/
//
class PennyArcade : public CommandModule {
public:
    PennyArcade(const std::string& name);
    virtual ~PennyArcade();

public: // Override
    virtual void commandAction (Channel* src, const std::vector<std::string>& args);
};
