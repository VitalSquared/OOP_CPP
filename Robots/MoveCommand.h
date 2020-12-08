#ifndef ROBOTS_MOVE_COMMAND_H
#define ROBOTS_MOVE_COMMAND_H

#include "ICommand.h"
#include "IManualModeCommand.h"

class MoveCommand : public IManualModeCommand {
public:
    MoveCommand(std::map<IRobot*, std::pair<int, int>>* _robots, int* _id, Repeater* _repeater) : IManualModeCommand(_robots, _id, _repeater) {};
    ~MoveCommand() override = default;

    CommandType validateArgs(std::vector<std::string> args) override;
    bool execute(std::vector<std::string> args) override;
};

#endif
