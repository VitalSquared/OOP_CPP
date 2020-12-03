#ifndef ROBOTS_CHANGE_MODE_COMMAND_H
#define ROBOTS_CHANGE_MODE_COMMAND_H

#include "ICommand.h"

class ChangeModeCommand : public ICommand {
public:
    ChangeModeCommand() = default;
    ~ChangeModeCommand() override = default;

    CommandType validateArgs(std::vector<std::string> args) override;
};

#endif
