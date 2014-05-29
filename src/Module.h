#pragma once

#include <map>
#include <string>

// Forward declare
namespace gloox
{
	class Message;
}

class BotCore;
class Channel;

class Module
{
public:
	Module (const std::string & name);
	virtual ~Module ();

	void setBot (BotCore * bot);
	virtual void accept (Channel * src, const gloox::Message & msg) = 0;

	static std::map<const std::string, Module *> myMap;

protected:
	BotCore * bot;
};
