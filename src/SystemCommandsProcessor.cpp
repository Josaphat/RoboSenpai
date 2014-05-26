#include "SystemCommandsProcessor.h"

#include <string>


SystemCommandsProcessor::SystemCommandsProcessor ()
{
}


SystemCommandsProcessor::~SystemCommandsProcessor ()
{
}

bool SystemCommandsProcessor::process (const std::string & msg)
{
	if (msg.front () != '#') {
		return false;
	}
	else {
	}

	// TODO
	return false;
}
