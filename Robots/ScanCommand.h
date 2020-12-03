#ifndef ROBOTS_SCAN_COMMAND_H
#define ROBOTS_SCAN_COMMAND_H

#include "ICommand.h"

class ScanCommand : public ICommand {
public:
    ScanCommand() = default;
    ~ScanCommand() override = default;

    CommandType validateArgs(std::vector<std::string> args) override;
};

#endif
