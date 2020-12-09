#include "Utils.h"
#include "AutoMode.h"
#include "IManualModeCommand.h"

std::string AutoMode::getModeName() {
    return "AUTO";
}

bool AutoMode::invokeCommand(IRobot* robot, ICommand* cmd, std::vector<std::string>& args) {
    if (robot == nullptr || dynamic_cast<IManualModeCommand*>(cmd) != nullptr) return false;

    if (cmd->execute(args)) return true;

    if (robot->invest()) return true;

    if (!containerContains(unreachable, robot)) {
        unreachable.insert(std::make_pair(robot, std::set<std::pair<int, int>>()));
    }

    if (containerContains(destination, robot) && robot->getPosition() == destination[robot]) {
        destination.erase(robot);
        unreachable[robot].clear();
    }

    while (true) {
        if (!containerContains(destination, robot)) {
            double min_dist = -1;
            std::vector<std::pair<int, int>> possible_destinations;
            const auto& _map = robot->getLocalMap()._getMap();
            for (int k = 0; k < _map.size(); k++) {
                auto cell = std::make_pair(Cantor_NumberToPair(k), _map[k]);
                if (!containerContains(robot->getInvestible(), robot->getLocalMap().getElement(cell.first)) ||
                    containerContains(unreachable[robot], cell.first) ||
                    cell.first == robot->getPosition() ||
                    anyRobotsMoveToPosition(robot, cell.first)) continue;

                double dist = calcDistance(cell.first, robot->getPosition());
                if (min_dist < 0 || dist < min_dist) {
                    min_dist = dist;
                    possible_destinations.clear();
                }
                if (dist <= min_dist) possible_destinations.emplace_back(cell.first);
            }

            if (possible_destinations.empty()) return false;
            destination.insert(std::make_pair(robot, possible_destinations[random(possible_destinations.size())]));
        }

        std::vector<std::pair<int, int>> path = buildPath(robot->getPosition(), destination[robot],
                                                      robot->getLocalMap(), robot->getWalkable(),unreachable[robot]);
        if (path.empty() || !robot->move(convertDeltaToDirection(path[0] - robot->getPosition()))) {
            unreachable[robot].insert(path.empty() ? destination[robot] : path[0]);
            destination.erase(robot);
            continue;
        }
        break;
    }
    return true;
}

bool AutoMode::anyRobotsMoveToPosition(IRobot *sender, std::pair<int, int> pos) {
    for(auto & iter : destination) {
        if (iter.first == sender) continue;
        if (iter.second == pos) return true;
    }
    return false;
}