#ifndef ROBOTS_SWITCHCOLLECTORCOMMAND_H
#define ROBOTS_SWITCHCOLLECTORCOMMAND_H

#include "ICommand.h"
#include "Utils.h"

class SwitchCollectorCommand : public ICommand {
public:
    SwitchCollectorCommand() = default;
    ~SwitchCollectorCommand() override = default;
    CommandType validateArgs(std::vector<std::string> args) override;
};

#endif
