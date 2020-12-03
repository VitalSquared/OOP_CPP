#ifndef ROBOTS_MANUAL_MODE_H
#define ROBOTS_MANUAL_MODE_H

#include "IMode.h"

class ManualMode : public IMode {
public:
    ManualMode();
    ~ManualMode() override = default;

    ModeType getModeType() override;
    bool invokeCommand(IRobot* robot, CommandType cmd, std::vector<std::string>& args) override;

private:
    int stepsMade;
};

#endif