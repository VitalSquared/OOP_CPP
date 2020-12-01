#include "ScanMode.h"

ModeType ScanMode::getModeType() {
    return ModeType::SCAN;
}

bool ScanMode::invokeCommand(IRobot *robot, CommandType cmd, std::vector<std::string> &args) {
    return false;
}