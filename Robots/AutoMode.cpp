#include "AutoMode.h"

ModeType AutoMode::getModeType() {
    return ModeType::AUTO;
}

bool AutoMode::invokeCommand(IRobot *robot, CommandType cmd, std::vector<std::string> &args) {
    return false;
}