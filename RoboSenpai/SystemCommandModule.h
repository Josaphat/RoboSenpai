#pragma once

#include <string>
#include <vector>

class SystemCommandModule
{
public:
	SystemCommandModule ();
	virtual ~SystemCommandModule ();

	virtual void accept (const std::string & command, const std::vector<const std::string> & args) = 0;
};

