#ifndef ROBOTS_SCANMODE_H
#define ROBOTS_SCANMODE_H

#include <set>
#include <map>
#include "IMode.h"

class ScanMode : public IMode {
public:
    ScanMode() = default;
    ~ScanMode() override = default;

    ModeType getModeType() override;
    bool invokeCommand(IRobot* robot, CommandType cmd, std::vector<std::string>& args) override;

private:
    std::map<IRobot*, int> stepsMade;
    std::map<IRobot*, std::pair<int, int>> destination;
    std::map<IRobot*, std::set<std::pair<int, int>>> unreachable;

    bool anyRobotsMoveToPosition(IRobot* sender, std::pair<int, int> pos);
};

#endif
