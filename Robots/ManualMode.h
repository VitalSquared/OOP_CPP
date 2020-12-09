#ifndef ROBOTS_MANUAL_MODE_H
#define ROBOTS_MANUAL_MODE_H

#include "IMode.h"

class ManualMode : public IMode {
public:
    ManualMode();
    ~ManualMode() override = default;

    std::string getModeName() override;
    bool invokeCommand(IRobot* robot, ICommand* cmd, std::vector<std::string>& args) override;

private:
    int stepsMade;
};

#endif