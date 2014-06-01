#include "Module.h"

#include "BotCore.h"

std::map<std::string, Module*> Module::myMap;
Scraper Module::scraper;

Module::Module(const std::string& name)
{
    myMap[name] = this;
}


Module::~Module()
{
}

void Module::setBot(BotCore* bot)
{
    this->bot = bot;
}
