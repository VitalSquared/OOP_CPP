#ifndef ROBOTS_SCANMODE_H
#define ROBOTS_SCANMODE_H

#include <set>
#include <map>
#include "IMode.h"
#include "Utils.h"

class ScanMode : public IMode {
public:
    ScanMode() = default;
    ~ScanMode() override = default;
    bool invokeCommand(IRobot* robot, CommandType cmd, std::vector<std::string>& args) override;
    ModeType getModeType() override;

private:
    std::map<IRobot*, int> stepsMade;
    std::map<IRobot*, std::pair<int, int>> dest;
    std::map<IRobot*, std::set<std::pair<int, int>>> unreachable;

};

#endif
