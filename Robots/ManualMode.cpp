#include "Utils.h"
#include "ManualMode.h"

ManualMode::ManualMode() {
    stepsMade = 0;
}

ModeType ManualMode::getModeType() {
    return ModeType::MANUAL;
}

bool ManualMode::invokeCommand(IRobot *robot, CommandType cmd, std::vector<std::string> &args) {
    if (robot == nullptr || robot->getRobotID().first == RobotType::SAPPER) return false;
    if (stepsMade >= 1) {
        stepsMade = 0;
        return false;
    }
    stepsMade++;
    bool res;
    switch(cmd) {
        case CommandType::MOVE:
            res = robot->move(convertStringToDirection(args[0]));
            break;
        case CommandType::GRAB:
            res = robot->invest();
            break;
        case CommandType::SCAN:
            res = robot->scan();
            break;
        default:
            res = false;
    }
    if (!res) stepsMade = 0;
    return res;
}