#include "Utils.h"
#include "ManualMode.h"
#include "IManualModeCommand.h"

std::string ManualMode::getModeName() {
    return "MANUAL";
}

bool ManualMode::invokeCommand(IRobot *robot, ICommand* cmd, std::vector<std::string> &args) {
    if (robot == nullptr || robot->getRobotID().first != RobotType::COLLECTOR) return false;

    auto *manualCmd = dynamic_cast<IManualModeCommand *>(cmd);
    if (manualCmd == nullptr) return cmd->execute(args);

    if (!containerContains(stepsMade, robot)) {
        stepsMade.insert(std::make_pair(robot, 0));
    }

    if (stepsMade[robot] >= 1) {
        stepsMade[robot] = 0;
        return false;
    }
    stepsMade[robot]++;

    bool res = manualCmd->execute(robot, args);
    if (!res) stepsMade[robot] = 0;

    return res;
}