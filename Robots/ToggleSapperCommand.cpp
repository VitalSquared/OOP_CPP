#include "Utils.h"
#include "ToggleSapperCommand.h"

CommandType ToggleSapperCommand::validateArgs(std::vector<std::string> args) {
    int id;
    if (args.empty()) return CommandType::SAPPER;
    if (args.size() > 2) return CommandType::UNKNOWN;
    if (args[0] == "ON") return args.size() == 1 ? CommandType::SAPPER : CommandType::UNKNOWN;
    else if (args[0] == "OFF") {
        if (args.size() == 2 && !convertStringToInt(args[1], id)) return CommandType::UNKNOWN;
        return CommandType::SAPPER;
    }
    return CommandType::UNKNOWN;
}