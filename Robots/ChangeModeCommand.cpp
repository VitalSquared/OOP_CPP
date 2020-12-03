#include "Utils.h"
#include "ChangeModeCommand.h"

CommandType ChangeModeCommand::validateArgs(std::vector<std::string> args) {
    int n;
    if (args.empty()) return CommandType::UNKNOWN;
    if (args[0] == "manual" || args[0] == "auto") {
        if (args.size() != 1) return CommandType::UNKNOWN;
    }
    else if (args[0] == "scan") {
        if (args.size() != 2) return CommandType::UNKNOWN;
        if (!convertStringToInt(args[1], n)) return CommandType::UNKNOWN;
    }
    return CommandType::SET_MODE;
}