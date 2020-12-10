#include "ScanCommand.h"

bool ScanCommand::validateArgs(std::vector<std::string> args) {
    return args.empty();
}

bool ScanCommand::execute(IRobot* sender, std::vector<std::string> args) {
    if (sender != getActiveCollector()) return false;
    return getActiveCollector()->scan();
}