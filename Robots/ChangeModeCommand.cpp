#include "Utils.h"
#include "ChangeModeCommand.h"
#include "ManualMode.h"
#include "AutoMode.h"
#include "ScanMode.h"

ChangeModeCommand::ChangeModeCommand(IMode **mode) {
    this->mode = mode;
}

bool ChangeModeCommand::validateArgs(std::vector<std::string> args) {
    int n;
    if (args.empty()) return false;
    if (args[0] == "manual" || args[0] == "auto") {
        if (args.size() != 1) return false;
    }
    else if (args[0] == "scan") {
        if (args.size() != 2) return false;
        if (!convertStringToInt(args[1], n)) return false;
    }
    return true;
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
        if ((*mode)->getModeName() != new_mode->getModeName()) {
            delete *mode;
            *mode = new_mode;
            return true;
        }
        else delete new_mode;
    }
    return false;
}