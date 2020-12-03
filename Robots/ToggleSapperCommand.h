#ifndef ROBOTS_TOGGLESAPPERCOMMAND_H
#define ROBOTS_TOGGLESAPPERCOMMAND_H

#include "ICommand.h"
#include "Utils.h"

class ToggleSapperCommand : public ICommand {
public:
    ToggleSapperCommand() = default;
    ~ToggleSapperCommand() override = default;
    CommandType validateArgs(std::vector<std::string> args) override;
};

#endif
