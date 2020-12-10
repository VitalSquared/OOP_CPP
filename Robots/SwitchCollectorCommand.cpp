#include <iostream>
#include "Utils.h"
#include "SwitchCollectorCommand.h"

bool SwitchCollectorCommand::validateArgs(std::vector<std::string> args) {
    int n;
    return args.empty() || args.size() == 1 && convertStringToInt(args[0], n);
}

bool SwitchCollectorCommand::execute(IRobot* sender, std::vector<std::string> args) {
    if (getActiveCollector() != sender) return false;
    if (args.empty()) {
        std::cout << "Collectors ID list: ";
        for (auto robot : *getRobots()) {
            std::pair<RobotType, int> id = robot.first->getRobotID();
            if (id.first == RobotType::COLLECTOR) {
                std::cout << id.second;
                if (id.second == *getActiveCollectorID()) std::cout << "(active)";
                std::cout << ",  ";
            }
        }
        std::cout << std::endl;
    }
    else {
        int newID;
        convertStringToInt(args[0], newID);

        if (newID == *getActiveCollectorID()) return false;

        for (auto robot : *getRobots()) {
            std::pair<RobotType, int> id = robot.first->getRobotID();
            if (id.first == RobotType::COLLECTOR && id.second == newID) {
                *getActiveCollectorID() = newID;
                return true;
            }
        }
    }
    return false;
}