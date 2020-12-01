#include "ChangeModeCommand.h"

CommandType ChangeModeCommand::validateArgs(std::vector<std::string> args) {
    if (args.empty()) return CommandType::UNKNOWN;
    if (args[0] == "manual" || args[0] == "auto") {
        if (args.size() != 1) return CommandType::UNKNOWN;
    }
    else if (args[0] == "scan") {
        if (args.size() != 2) return CommandType::UNKNOWN;
        try {
            std::stoi(args[1]);
        }
        catch(std::exception&) {
            return CommandType::UNKNOWN;
        }
    }
    return CommandType::SET_MODE;
}