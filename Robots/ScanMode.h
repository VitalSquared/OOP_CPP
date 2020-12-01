#ifndef ROBOTS_SCANMODE_H
#define ROBOTS_SCANMODE_H

#include "IMode.h"

class ScanMode : public IMode {
public:
    ScanMode() = default;
    ~ScanMode() override = default;
    bool invokeCommand(IRobot* robot, CommandType cmd, std::vector<std::string>& args) override;
    ModeType getModeType() override;
};

#endif
