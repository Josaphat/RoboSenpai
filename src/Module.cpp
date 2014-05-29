#include "Module.h"

#include "BotCore.h"

std::map<const std::string, Module *> Module::myMap;

Module::Module (const std::string & name)
{
	myMap[name] = this;
}


Module::~Module ()
{
}

void Module::setBot (BotCore * bot)
{
	this->bot = bot;
}
