#include "SystemCommandsProcessor.h"

#include <iostream>
#include <string>


SystemCommandsProcessor::SystemCommandsProcessor()
{
}


SystemCommandsProcessor::~SystemCommandsProcessor()
{
}

bool SystemCommandsProcessor::process(const std::string& msg)
{
    if (msg.front() != '#') {
        return false;
    }
    else {
        bool processed = false;

        // TODO: Iterate over the system command modules
        if (msg.compare("#shutdown") == 0) {
            std::cout << "#shutdown command" << std::endl;
            processed = true;
        }
        else if (msg.compare("#restart") == 0) {
            std::cout << "#restart command" << std::endl;
            processed = true;
        }

        return processed;
    }
}
