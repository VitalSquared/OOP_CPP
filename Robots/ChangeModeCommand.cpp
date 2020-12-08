#include "Utils.h"
#include "ChangeModeCommand.h"
#include "ManualMode.h"
#include "AutoMode.h"
#include "ScanMode.h"

ChangeModeCommand::ChangeModeCommand(IMode **mode) {
    this->mode = mode;
}

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

bool ChangeModeCommand::execute(std::vector<std::string> args) {
    IMode* new_mode;
    if (args[0] == "manual") {
        new_mode = new ManualMode();
    }
    else if (args[0] == "scan") {
        new_mode = new ScanMode();
    }
    else if (args[0] == "auto") {
        new_mode = new AutoMode();
    }
    if (*mode == nullptr) {
        *mode = new_mode;
        return true;
    }
    else {
        if ((*mode)->getModeType() != new_mode->getModeType()) {
            delete *mode;
            *mode = new_mode;
            return true;
        }
        else delete new_mode;
    }
    return false;
}