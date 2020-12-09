#ifndef ROBOTS_AUTO_MODE_H
#define ROBOTS_AUTO_MODE_H

#include <set>
#include <map>
#include "IMode.h"

class AutoMode : public IMode {
public:
    AutoMode() = default;
    ~AutoMode() override = default;

    std::string getModeName() override;
    bool invokeCommand(IRobot* robot, ICommand* cmd, std::vector<std::string>& args) override;

private:
    std::map<IRobot*, std::pair<int, int>> destination;
    std::map<IRobot*, std::set<std::pair<int, int>>> unreachable;

    bool anyRobotsMoveToPosition(IRobot* sender, std::pair<int, int> pos);
};

#endif
