#include "AutoMode.h"

ModeType AutoMode::getModeType() {
    return ModeType::AUTO;
}

bool AutoMode::invokeCommand(IRobot *robot, CommandType cmd, std::vector<std::string> &args) {
    if (robot->invest()) {
        return true;
    }

    if (dest.find(robot) != dest.end() && robot->getPosition() == dest[robot]) {
        dest.erase(robot);
        unreachable.erase(robot);
    }

    std::set<MapElement> investible = robot->getInvestible();
    while (true) {
        if (dest.find(robot) == dest.end()) {
            double min_dist = -1;
            std::vector<std::pair<int, int>> all_min_psbl;
            for (auto cell: robot->getLocalMap().getMap()) {
                int cell_r = cell.first.first, cell_c = cell.first.second;

                if (investible.find(robot->getLocalMap().getElement(cell_r, cell_c)) == investible.end() ||
                    unreachable[robot].find(cell.first) != unreachable[robot].end() ||
                    cell.first == robot->getPosition()) continue;

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
        std::vector<std::pair<int, int>> path = buildPath(rbt_r, rbt_c, dst_r, dst_c, robot->getLocalMap(), robot->getWalkable());
        if (path.empty()) {
            if (unreachable.find(robot) == unreachable.end()) {
                unreachable.insert(std::make_pair(robot, std::set<std::pair<int, int>>({dest[robot]})));
            }
            else {
                unreachable[robot].insert(dest[robot]);
            }
            dest.erase(robot);
            continue;
        }
        robot->move(calcDirection(robot->getPosition(), path[0]));
        break;
    }
    return true;
}