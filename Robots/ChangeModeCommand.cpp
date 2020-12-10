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
    if (args[0] == "manual" && dynamic_cast<ManualMode*>(*mode) == nullptr) {
        delete *mode;
        *mode = new ManualMode();
        return true;
    }
    else if (args[0] == "scan" && dynamic_cast<ScanMode*>(*mode) == nullptr) {
        delete *mode;
        *mode = new ScanMode();
        return true;
    }
    else if (args[0] == "auto" && dynamic_cast<AutoMode*>(*mode) == nullptr) {
        delete *mode;
        *mode = new AutoMode();
        return true;
    }
    return false;
}