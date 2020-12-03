#include "SwitchCollectorCommand.h"

CommandType SwitchCollectorCommand::validateArgs(std::vector<std::string> args) {
    if (args.empty()) return CommandType::COLLECTOR;
    if (args.size() > 1) return CommandType::UNKNOWN;
    int n;
    if (!convertStringToInt(args[0], n)) return CommandType::UNKNOWN;
    return CommandType::COLLECTOR;
}