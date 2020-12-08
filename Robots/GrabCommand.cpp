#include "GrabCommand.h"

CommandType GrabCommand::validateArgs(std::vector<std::string> args) {
    return args.empty() ? CommandType::GRAB : CommandType::UNKNOWN;
}

bool GrabCommand::execute(std::vector<std::string> args) {
    return getActiveCollector()->invest();
}