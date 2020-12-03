#ifndef ROBOTS_SWITCH_COLLECTOR_COMMAND_H
#define ROBOTS_SWITCH_COLLECTOR_COMMAND_H

#include "ICommand.h"

class SwitchCollectorCommand : public ICommand {
public:
    SwitchCollectorCommand() = default;
    ~SwitchCollectorCommand() override = default;

    CommandType validateArgs(std::vector<std::string> args) override;
};

#endif
