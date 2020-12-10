#ifndef ROBOTS_ICOMMAND_H
#define ROBOTS_ICOMMAND_H

#include <vector>
#include <string>
#include <map>
#include "IRobot.h"
#include "Repeater.h"

class ICommand {
public:
    virtual ~ICommand() = default;

    virtual bool validateArgs(std::vector<std::string> args) = 0;
    virtual bool execute(std::vector<std::string> args) = 0;
};

#endif
