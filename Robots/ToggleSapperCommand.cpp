#include <iostream>
#include <algorithm>
#include "Utils.h"
#include "Sapper.h"
#include "ToggleSapperCommand.h"

CommandType ToggleSapperCommand::validateArgs(std::vector<std::string> args) {
    int id;
    if (args.empty()) return CommandType::SAPPER;
    if (args.size() > 2) return CommandType::UNKNOWN;
    if (args[0] == "ON") return args.size() == 1 ? CommandType::SAPPER : CommandType::UNKNOWN;
    else if (args[0] == "OFF") {
        if (args.size() == 2 && !convertStringToInt(args[1], id)) return CommandType::UNKNOWN;
        return CommandType::SAPPER;
    }
    return CommandType::UNKNOWN;
}

bool ToggleSapperCommand::execute(std::vector<std::string> args) {
    if (args.empty()) {
        std::cout << "Sappers ID list: ";
        for (auto robot : *getRobots()) {
            std::pair<RobotType, int> id = robot.first->getRobotID();
            if (id.first == RobotType::SAPPER) {
                std::cout << id.second << ", ";
            }
        }
        std::cout << std::endl;
    }
    else {
        int idReq = 0;
        if (args.size() == 2) convertStringToInt(args[1], idReq);

        IRobot* lastSapper = nullptr;
        std::vector<int> ids;
        for (auto robot: *getRobots()) {
            std::pair<RobotType, int> id = robot.first->getRobotID();
            if (id.first == RobotType::SAPPER) {
                if (args.size() == 2 && id.second == idReq) {
                    if (args[0] == "OFF") {
                        getRobots()->erase(robot.first);
                        delete robot.first;
                        return true;
                    }
                    else return false;
                }
                ids.emplace_back(id.second);
                lastSapper = robot.first;
            }
        }
        if (ids.size() == 1 && args.size() == 1 && args[0] == "OFF") {
            getRobots()->erase(lastSapper);
            delete lastSapper;
            return true;
        }

        if (args[0] == "ON") {
            std::sort(ids.begin(), ids.end());
            int min_unused_id = 0;
            for (auto id : ids) {
                if (id == min_unused_id) min_unused_id++;
            }
            Map scannedMap;

            std::vector<std::pair<int, int>> positions = findSuitablePos(1, getActiveCollector()->getLocalMap()._getMap(), { MapElement::EMPTY, MapElement::APPLE, MapElement::BOMB });
            IRobot* sapper = new Sapper(getRepeater(), min_unused_id);
            getRobots()->insert(std::make_pair(sapper, getRobots()->at(getActiveCollector()) + positions[0]));
            sapper->initMap();
            args.emplace_back(std::to_string(min_unused_id));
            return true;
        }
    }
    return false;
}