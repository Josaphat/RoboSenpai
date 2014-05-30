#pragma once

#include <map>
#include <string>
#include "Scraper.h"

// Forward declarations
namespace gloox {
    class Message;
}
class BotCore;
class Channel;


class Module {
public:
    Module(const std::string& name);
    virtual ~Module();

    void setBot(BotCore* bot);
    virtual void accept(Channel* src, const gloox::Message& msg) = 0;

    static std::map<std::string, Module*> myMap;

protected:
    Scraper scraper;
    BotCore* bot;
};
