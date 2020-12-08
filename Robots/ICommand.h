#ifndef ROBOTS_ICOMMAND_H
#define ROBOTS_ICOMMAND_H

#include <vector>
#include <string>
#include <map>
#include "IRobot.h"
#include "Repeater.h"

enum class CommandType { UNKNOWN, MOVE, SCAN, GRAB, SAPPER, SET_MODE, COLLECTOR };

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual CommandType validateArgs(std::vector<std::string> args) = 0;
    virtual bool execute(std::vector<std::string> args) = 0;
};

#endif
