#ifndef ROBOTS_GRABCOMMAND_H
#define ROBOTS_GRABCOMMAND_H

#include "ICommand.h"
#include "IManualModeCommand.h"

class GrabCommand : public IManualModeCommand {
public:
    GrabCommand(std::map<IRobot*, std::pair<int, int>>* _robots, int* _id, Repeater* _repeater) : IManualModeCommand(_robots, _id, _repeater) {};
    ~GrabCommand() override = default;

    CommandType validateArgs(std::vector<std::string> args) override;
    bool execute(std::vector<std::string> args) override;
};

#endif
