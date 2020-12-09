#include "Utils.h"
#include "ManualMode.h"
#include "IManualModeCommand.h"

ManualMode::ManualMode() {
    stepsMade = 0;
}

std::string ManualMode::getModeName() {
    return "MANUAL";
}

bool ManualMode::invokeCommand(IRobot *robot, ICommand* cmd, std::vector<std::string> &args) {
    if (robot == nullptr || robot->getRobotID().first == RobotType::SAPPER) return false;

    auto* manualCmd = dynamic_cast<IManualModeCommand*>(cmd);
    if (manualCmd == nullptr) return cmd->execute(args);

    if (stepsMade >= 1) {
        stepsMade = 0;
        return false;
    }
    stepsMade++;

    bool res = manualCmd->execute(args);
    if (!res) stepsMade = 0;

    return res;
}