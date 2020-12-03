#ifndef ROBOTS_MOVE_COMMAND_H
#define ROBOTS_MOVE_COMMAND_H

#include "ICommand.h"

class MoveCommand : public ICommand {
public:
    MoveCommand() = default;
    ~MoveCommand() override = default;

    CommandType validateArgs(std::vector<std::string> args) override;
};

#endif
