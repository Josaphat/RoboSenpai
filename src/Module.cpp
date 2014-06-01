#include "Module.h"

#include "BotCore.h"

std::map<std::string, Module*> Module::moduleMap;
Scraper Module::scraper;

Module::Module(const std::string& name)
{
    moduleMap[name] = this;
}


Module::~Module()
{
}
