#pragma once

#include <string>
#include <vector>

#include "SystemCommandModule.h"

class SystemCommandsProcessor
{
public:
	SystemCommandsProcessor ();
	virtual ~SystemCommandsProcessor ();

	bool process (const std::string & msg);

private:
	std::vector<SystemCommandModule *> commandModules;
};

