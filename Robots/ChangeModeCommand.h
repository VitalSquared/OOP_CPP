#ifndef ROBOTS_CHANGEMODECOMMAND_H
#define ROBOTS_CHANGEMODECOMMAND_H

#include "ICommand.h"

class ChangeModeCommand : public ICommand {
public:
    ChangeModeCommand() = default;
    ~ChangeModeCommand() override = default;
    CommandType validateArgs(std::vector<std::string> args) override;
};

#endif
