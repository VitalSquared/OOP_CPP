#ifndef ROBOTS_GRABCOMMAND_H
#define ROBOTS_GRABCOMMAND_H

#include "ICommand.h"

class GrabCommand : public ICommand {
public:
    GrabCommand() = default;
    ~GrabCommand() override = default;

    CommandType validateArgs(std::vector<std::string> args) override;
};

#endif
