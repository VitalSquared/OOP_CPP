#include "AutoMode.h"

ModeType AutoMode::getModeType() {
    return ModeType::AUTO;
}

bool AutoMode::invokeCommand(IRobot *robot, CommandType cmd, std::vector<std::string> &args) {
    if (robot->invest()) {
        return true;
    }

    if (containerContains(dest, robot) && robot->getPosition() == dest[robot]) {
        dest.erase(robot);
        unreachable.erase(robot);
    }

    std::set<MapElement> investible = robot->getInvestible();
    while (true) {
        if (!containerContains(dest, robot)) {
            double min_dist = -1;
            std::vector<std::pair<int, int>> all_min_psbl;
            for (auto cell: robot->getLocalMap().getMap()) {
                int cell_r = cell.first.first, cell_c = cell.first.second;

                if (!containerContains(investible, robot->getLocalMap().getElement(cell_r, cell_c)) ||
                        containerContains(unreachable[robot], cell.first) || cell.first == robot->getPosition()) continue;

                double dist = calcDistance(cell.first, robot->getPosition());
                if (min_dist < 0 || dist < min_dist) {
                    min_dist = dist;
                    all_min_psbl.clear();
                }
                if (dist <= min_dist) all_min_psbl.emplace_back(std::make_pair(cell_r, cell_c));
                break;
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
        break;
    }
    return true;
}