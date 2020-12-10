#ifndef ROBOTS_TOGGLE_SAPPER_COMMAND_H
#define ROBOTS_TOGGLE_SAPPER_COMMAND_H

#include "ICommand.h"
#include "IManualModeCommand.h"

class ToggleSapperCommand : public IManualModeCommand {
public:
    ToggleSapperCommand(std::map<IRobot*, std::pair<int, int>>* _robots, int* _id, Repeater* _repeater) : IManualModeCommand(_robots, _id, _repeater) {};
    ~ToggleSapperCommand() override = default;

    bool validateArgs(std::vector<std::string> args) override;
    bool execute(IRobot* sender, std::vector<std::string> args) override;
};

#endif
