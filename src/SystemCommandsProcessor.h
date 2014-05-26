#pragma once

#include <string>
#include <vector>

#include "SystemCommandModule.h"

class SystemCommandsProcessor
{
public:
	SystemCommandsProcessor ();
	virtual ~SystemCommandsProcessor ();

	/**
	 * Processes a system command. If a command is executed, it returns
	 * true to indicate that the message should not be sent to other modules.
	 *
	 * \returns true if a system command is executed.
	 */
	bool process (const std::string & msg);

private:
	std::vector<SystemCommandModule *> commandModules;
};
