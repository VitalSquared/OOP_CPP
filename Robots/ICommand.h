#ifndef ROBOTS_ICOMMAND_H
#define ROBOTS_ICOMMAND_H

#include <vector>
#include <string>
#include <exception>

enum class CommandType { UNKNOWN, MOVE, SCAN, GRAB, SAPPER, SET_MODE };

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual CommandType validateArgs(std::vector<std::string> args) = 0;
};

#endif
