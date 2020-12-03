#ifndef ROBOTS_IMODE_H
#define ROBOTS_IMODE_H

#include <vector>
#include <string>
#include "ICommand.h"
#include "IRobot.h"

enum class ModeType { MANUAL, SCAN, AUTO };

class IMode {
public:
    virtual ~IMode() = default;

    virtual ModeType getModeType() = 0;
    virtual bool invokeCommand(IRobot* robot, CommandType cmd, std::vector<std::string>& args) = 0;
};

#endif
