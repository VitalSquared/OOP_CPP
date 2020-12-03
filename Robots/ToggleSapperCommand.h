#ifndef ROBOTS_TOGGLE_SAPPER_COMMAND_H
#define ROBOTS_TOGGLE_SAPPER_COMMAND_H

#include "ICommand.h"

class ToggleSapperCommand : public ICommand {
public:
    ToggleSapperCommand() = default;
    ~ToggleSapperCommand() override = default;
    CommandType validateArgs(std::vector<std::string> args) override;
};

#endif
