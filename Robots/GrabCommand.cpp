#include "GrabCommand.h"

bool GrabCommand::validateArgs(std::vector<std::string> args) {
    return args.empty();
}

bool GrabCommand::execute(IRobot* sender, std::vector<std::string> args) {
    if (getActiveCollector() != sender) return false;
    return getActiveCollector()->invest();
}