#include "Utils.h"
#include "ScanMode.h"
#include "IManualModeCommand.h"

std::string ScanMode::getModeName() {
    return "SCAN";
}

bool ScanMode::invokeCommand(IRobot *robot, ICommand* cmd, std::vector<std::string> &args) {
    if (robot == nullptr || robot->getRobotID().first != RobotType::COLLECTOR || dynamic_cast<IManualModeCommand*>(cmd) != nullptr) return false;

    if (cmd->execute(args)) return true;

    int stepsReq;
    convertStringToInt(args[1], stepsReq);

    if (!containerContains(stepsMade, robot)) {
        stepsMade.insert(std::make_pair(robot, 0));
        destination.insert(std::make_pair(robot, robot->getPosition()));
    }

    if (!containerContains(unreachable, robot)) {
        unreachable.insert(std::make_pair(robot, std::set<std::pair<int, int>>()));
    }

    if (containerContains(destination, robot) && robot->getPosition() == destination[robot]) {
        robot->scan();
        destination.erase(robot);
        unreachable[robot].clear();
        return true;
    }

    if (stepsMade[robot] >= stepsReq) {
        if (containerContains(destination, robot)) destination.erase(robot);
        return false;
    }

    std::set<MapElement> walkable = robot->getWalkable();
    while (true) {
        if (destination.find(robot) == destination.end()) {
            double min_dist = -1;
            std::vector<std::pair<int, int>> possible_destinations;
            const auto& _map = robot->getLocalMap()._getMap();
            for (int k = 0; k < _map.size(); k++) {
                auto cell = std::make_pair(Cantor_NumberToPair(k), _map[k]);
                if (!containerContains(walkable, robot->getLocalMap().getElement(cell.first)) ||
                    containerContains(unreachable[robot], cell.first) ||
                    cell.first == robot->getPosition() ||
                    anyRobotsMoveToPosition(robot, cell.first)) continue;

                for (auto adj : getAdjacentCoords(cell.first)) {
                    if (!robot->getLocalMap().containsLocation(adj.first, adj.second)) {
                        double dist = calcDistance(cell.first, robot->getPosition());
                        if (min_dist < 0 || dist < min_dist) {
                            min_dist = dist;
                            possible_destinations.clear();
                        }
                        if (dist <= min_dist) possible_destinations.emplace_back(cell.first);
                        break;
                    }
                }
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
        stepsMade[robot]++;
        break;
    }
    return true;
}

bool ScanMode::anyRobotsMoveToPosition(IRobot *sender, std::pair<int, int> pos) {
    for(auto & iter : destination) {
        if (iter.first == sender) continue;
        if (iter.second == pos) return true;
    }
    return false;
}