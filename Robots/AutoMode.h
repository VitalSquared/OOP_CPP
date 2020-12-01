#ifndef ROBOTS_AUTOMODE_H
#define ROBOTS_AUTOMODE_H

#include "IMode.h"

class AutoMode : public IMode {
public:
    AutoMode() = default;
    ~AutoMode() override = default;
    bool invokeCommand(IRobot* robot, CommandType cmd, std::vector<std::string>& args) override;
    ModeType getModeType() override;
};

#endif
