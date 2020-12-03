#include "Utils.h"
#include "SwitchCollectorCommand.h"

CommandType SwitchCollectorCommand::validateArgs(std::vector<std::string> args) {
    int n;
    if (args.empty()) return CommandType::COLLECTOR;
    if (args.size() > 1 || !convertStringToInt(args[0], n)) return CommandType::UNKNOWN;
    return CommandType::COLLECTOR;
}