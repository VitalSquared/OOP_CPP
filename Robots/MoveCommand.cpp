#include <vector>
#include "Utils.h"
#include "MoveCommand.h"

CommandType MoveCommand::validateArgs(std::vector<std::string> args) {
    if (args.size() != 1) return CommandType::UNKNOWN;
    return containerContains(std::set<std::string>({"U", "D", "L", "R"}), args[0]) ? CommandType::MOVE : CommandType::UNKNOWN;
}