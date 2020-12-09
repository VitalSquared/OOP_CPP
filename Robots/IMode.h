#ifndef ROBOTS_IMODE_H
#define ROBOTS_IMODE_H

#include <vector>
#include <string>
#include "ICommand.h"
#include "IRobot.h"

class IMode {
public:
    virtual ~IMode() = default;

    virtual std::string getModeName() = 0;
    virtual bool invokeCommand(IRobot* robot, ICommand* cmd, std::vector<std::string>& args) = 0;
};

#endif
