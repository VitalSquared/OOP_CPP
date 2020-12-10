#include <vector>
#include "Utils.h"
#include "MoveCommand.h"

bool MoveCommand::validateArgs(std::vector<std::string> args) {
    return args.size() == 1 && containerContains(std::set<std::string>({"U", "D", "L", "R"}), args[0]);
}

bool MoveCommand::execute(IRobot* sender, std::vector<std::string> args) {
    if (getActiveCollector() != sender) return false;
    return getActiveCollector()->move(convertStringToDirection(args[0]));
}