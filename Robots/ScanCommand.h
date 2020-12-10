#ifndef ROBOTS_SCAN_COMMAND_H
#define ROBOTS_SCAN_COMMAND_H

#include "ICommand.h"
#include "IManualModeCommand.h"

class ScanCommand : public IManualModeCommand {
public:
    ScanCommand(std::map<IRobot*, std::pair<int, int>>* _robots, int* _id, Repeater* _repeater) : IManualModeCommand(_robots, _id, _repeater) {};
    ~ScanCommand() override = default;

    bool validateArgs(std::vector<std::string> args) override;
    bool execute(IRobot* sender, std::vector<std::string> args) override;
};

#endif
