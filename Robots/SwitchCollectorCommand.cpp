#include <iostream>
#include "Utils.h"
#include "SwitchCollectorCommand.h"

CommandType SwitchCollectorCommand::validateArgs(std::vector<std::string> args) {
    int n;
    if (args.empty()) return CommandType::COLLECTOR;
    if (args.size() > 1 || !convertStringToInt(args[0], n)) return CommandType::UNKNOWN;
    return CommandType::COLLECTOR;
}

bool SwitchCollectorCommand::execute(std::vector<std::string> args) {
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