#pragma once
#include "../../Module.h"

class Channel;

//
/// The PennyArcade module implementation. Scrapes the comic off of
/// http://penny-arcade.com/comic/
//
class PennyArcade : public Module {
public:
    PennyArcade(const std::string& name);
    virtual ~PennyArcade();

public: // Override
    virtual void accept(Channel* src, const gloox::Message& msg);
};
