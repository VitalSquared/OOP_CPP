#include "ScanCommand.h"

CommandType ScanCommand::validateArgs(std::vector<std::string> args) {
    return args.empty() ? CommandType::SCAN : CommandType::UNKNOWN;
}