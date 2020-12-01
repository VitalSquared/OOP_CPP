#include "MoveCommand.h"

CommandType MoveCommand::validateArgs(std::vector<std::string> args) {
    if (args.size() != 1 || args[0].size() != 1) return CommandType::UNKNOWN;
    switch(args[0][0]) {
        case 'U': return CommandType::MOVE;
        case 'D': return CommandType::MOVE;
        case 'L': return CommandType::MOVE;
        case 'R': return CommandType::MOVE;
        default:
            return CommandType::UNKNOWN;
    }
}