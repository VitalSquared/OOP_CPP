#include "ScanMode.h"

ModeType ScanMode::getModeType() {
    return ModeType::SCAN;
}

bool ScanMode::invokeCommand(IRobot *robot, CommandType cmd, std::vector<std::string> &args) {
    if (cmd != CommandType::SET_MODE || robot->getRobotType() != RobotType::COLLECTOR) return false;

    int stepsReq;
    convertStringToInt(args[1], stepsReq);

    if (!containerContains(stepsMade, robot)) {
        stepsMade.insert(std::make_pair(robot, 0));
        dest.insert(std::make_pair(robot, robot->getPosition()));
    }

    if (containerContains(dest, robot) && robot->getPosition() == dest[robot]) {
        robot->scan();
        dest.erase(robot);
        unreachable.erase(robot);
        return true;
    }

    if (stepsMade[robot] >= stepsReq) {
        if (containerContains(dest, robot)) dest.erase(robot);
        return false;
    }

    std::set<MapElement> walkable = robot->getWalkable();
    while (true) {
        if (dest.find(robot) == dest.end()) {
            double min_dist = -1;
            std::vector<std::pair<int, int>> all_min_psbl;
            for (auto cell: robot->getLocalMap().getMap()) {
                int cell_r = cell.first.first, cell_c = cell.first.second;

                if (!containerContains(walkable, robot->getLocalMap().getElement(cell_r, cell_c)) ||
                        containerContains(unreachable[robot], cell.first) || cell.first == robot->getPosition()) continue;

                std::vector<std::pair<int, int>> adjs = getAdjacentCoords(cell_r, cell_c);
                for (auto adj : adjs) {
                    if (!robot->getLocalMap().containsLocation(adj.first, adj.second)) {
                        double dist = calcDistance(cell.first, robot->getPosition());
                        if (min_dist < 0 || dist < min_dist) {
                            min_dist = dist;
                            all_min_psbl.clear();
                        }
                        if (dist <= min_dist) all_min_psbl.emplace_back(std::make_pair(cell_r, cell_c));
                        break;
                    }
                }
            }

            if (all_min_psbl.empty()) return false;
            dest.insert(std::make_pair(robot, all_min_psbl[random(all_min_psbl.size())]));
        }

        int rbt_r = robot->getPosition().first, rbt_c = robot->getPosition().second;
        int dst_r = dest[robot].first, dst_c = dest[robot].second;
        std::vector<std::pair<int, int>> path = buildPath(rbt_r, rbt_c, dst_r, dst_c, robot->getLocalMap(), robot->getWalkable(),
                                      containerContains(unreachable, robot) ? unreachable[robot] : std::set<std::pair<int, int>>());
        if (path.empty()) {
            if (!containerContains(unreachable, robot)) {
                unreachable.insert(std::make_pair(robot, std::set<std::pair<int, int>>({dest[robot]})));
            }
            else {
                unreachable[robot].insert(dest[robot]);
            }
            dest.erase(robot);
            continue;
        }
        if (!robot->move(calcDirection(robot->getPosition(), path[0]))) {
            if (!containerContains(unreachable, robot)) {
                unreachable.insert(std::make_pair(robot, std::set<std::pair<int, int>>({path[0]})));
            }
            else {
                unreachable[robot].insert(path[0]);
            }
            if (path[0] == dest[robot]) dest.erase(robot);
            continue;
        }
        stepsMade[robot]++;
        break;
    }
    return true;
}