#ifndef ROBOTS_SWITCH_COLLECTOR_COMMAND_H
#define ROBOTS_SWITCH_COLLECTOR_COMMAND_H

#include "ICommand.h"
#include "IManualModeCommand.h"

class SwitchCollectorCommand : public IManualModeCommand {
public:
    SwitchCollectorCommand(std::map<IRobot*, std::pair<int, int>>* _robots, int* _id, Repeater* _repeater) : IManualModeCommand(_robots, _id, _repeater) {};
    ~SwitchCollectorCommand() override = default;

    bool validateArgs(std::vector<std::string> args) override;
    bool execute(IRobot* sender, std::vector<std::string> args) override;
};

#endif
