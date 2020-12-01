#ifndef ROBOTS_MANUALMODE_H
#define ROBOTS_MANUALMODE_H

#include "IMode.h"

class ManualMode : public IMode {
public:
    ManualMode();
    ~ManualMode() override = default;
    bool invokeCommand(IRobot* robot, CommandType cmd, std::vector<std::string>& args) override;
    ModeType getModeType() override;

private:
    int stepsMade;

    Direction stringToDirection(const std::string& str);
};

#endif