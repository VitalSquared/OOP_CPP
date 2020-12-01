#include "ToggleSapperCommand.h"

CommandType ToggleSapperCommand::validateArgs(std::vector<std::string> args) {
    if (args.size() != 1) return CommandType::UNKNOWN;
    if (args[0] != "ON" && args[0] != "OFF") return CommandType::UNKNOWN;
    return CommandType::SAPPER;
}