#include <iostream>
#include <algorithm>
#include "MoveCommand.h"
#include "ScanCommand.h"
#include "GrabCommand.h"
#include "ToggleSapperCommand.h"
#include "ChangeModeCommand.h"
#include "SwitchCollectorCommand.h"
#include "Collector.h"
#include "Sapper.h"
#include "ManualMode.h"
#include "ScanMode.h"
#include "AutoMode.h"
#include "Utils.h"
#include "Game.h"

Game::Game(const std::string& map_file, int cnt_collectors) {
    commandsContainer.insert(std::make_pair("MOVE", new MoveCommand()));
    commandsContainer.insert(std::make_pair("GRAB", new GrabCommand()));
    commandsContainer.insert(std::make_pair("SCAN", new ScanCommand()));
    commandsContainer.insert(std::make_pair("SAPPER", new ToggleSapperCommand()));
    commandsContainer.insert(std::make_pair("SET_MODE", new ChangeModeCommand()));
    commandsContainer.insert(std::make_pair("COLLECTOR", new SwitchCollectorCommand()));
    curCmd = CommandType::UNKNOWN;

    globalMap = new Map(map_file);
    repeater = new Repeater(globalMap, &robots);
    mode = new ManualMode();

    std::vector<std::pair<int, int>> positions = findSuitablePos(cnt_collectors, globalMap->_getMap(), { MapElement::EMPTY, MapElement::APPLE });
    for (int i = 0; i < cnt_collectors; i++) robots.emplace_back(new Collector(i, positions[i], repeater));
    activeCollectorID = 0;
}

Game::~Game() {
    for (auto& elem : commandsContainer) delete elem.second;
    commandsContainer.clear();

    for (auto* robot : robots) delete robot;
    robots.clear();

    delete globalMap;
    globalMap = nullptr;

    delete mode;
    mode = nullptr;

    delete repeater;
    repeater = nullptr;
}

bool Game::parseCommand(const std::string &cmd) {
    std::vector<std::string> split = splitString(cmd, ' ');
    if (split.empty()) {
        curArgs = {};
        curCmd = CommandType::UNKNOWN;
    }
    else {
        std::string main_cmd(split[0]);
        containerRemove(split, 0);
        curArgs = split;

        if (!containerContains(commandsContainer, main_cmd)) curCmd = CommandType::UNKNOWN;
        else curCmd = commandsContainer[main_cmd]->validateArgs(curArgs);
    }
    return curCmd != CommandType::UNKNOWN;
}

bool Game::step() {
    bool res;
    switch(curCmd) {
        case CommandType::SET_MODE:
            res = modeActivity();
            break;
        case CommandType::SAPPER:
            res = toggleSapper();
            break;
        case CommandType::COLLECTOR:
            res = switchCollector();
            break;
        default:
            res = mode->invokeCommand(getActiveCollector(), curCmd, curArgs);
            break;
    }

    std::set<int> collectorIDs;
    bool bFoundInactive;
    do {
        bFoundInactive = false;
        for (int i = 0; i < robots.size(); i++) {
            if (!robots[i]->isActive()) {
                delete robots[i];
                containerRemove(robots, i);
                bFoundInactive = true;
                break;
            }
            if (robots[i]->getRobotID().first == RobotType::COLLECTOR) {
                collectorIDs.insert(robots[i]->getRobotID().second);
            }
        }
    } while (bFoundInactive);

    if (!containerContains(collectorIDs, activeCollectorID) && !collectorIDs.empty()) {
        int idx = random(collectorIDs.size()), i = 0;
        for (auto elem : collectorIDs) {
            if (i == idx) {
                activeCollectorID = elem;
                break;
            }
            i++;
        }
    }
    return res;
}

const std::vector<IRobot*>& Game::getRobots() {
    return robots;
}

IRobot* Game::getActiveCollector() {
    for (auto* robot : robots) {
        std::pair<RobotType, int> id = robot->getRobotID();
        if (id.first == RobotType::COLLECTOR && id.second == activeCollectorID) {
            return robot;
        }
    }
    return nullptr;
}

bool Game::modeActivity() {
    if (curArgs[0] == "manual") {
        if (mode->getModeType() != ModeType::MANUAL) {
            delete mode;
            mode = new ManualMode();
        }
        return false;
    }
    else if (curArgs[0] == "scan" || curArgs[0] == "auto") {
        if (mode->getModeType() != ModeType::SCAN && curArgs[0] == "scan") {
            delete mode;
            mode = new ScanMode();
        }
        if (mode->getModeType() != ModeType::AUTO && curArgs[0] == "auto") {
            delete mode;
            mode = new AutoMode();
        }
        std::set<IRobot*> finishedWork;
        bool res = false;
        for (auto* robot : robots) {
            if (curArgs[0] == "scan" && robot->getRobotID().first == RobotType::SAPPER) continue;

            bool invokeRes = mode->invokeCommand(robot, curCmd, curArgs);
            if (robot->getRobotID().first == RobotType::COLLECTOR) {
                res = res || invokeRes;
                if (!invokeRes) finishedWork.insert(robot);
            }
        }
        if (containerContains(finishedWork, getActiveCollector()) && res) {
            for (auto* robot : robots) {
                if (robot->getRobotID().first != RobotType::COLLECTOR || containerContains(finishedWork, robot)) continue;
                activeCollectorID = robot->getRobotID().second;
                break;
            }
        }
        if (!res) {
            delete mode;
            mode = new ManualMode();
        }
        return res;
    }
    else return false;
}

bool Game::toggleSapper() {
    if (curArgs.empty()) {
        std::cout << "Sappers ID list: ";
        for (auto* robot : robots) {
            std::pair<RobotType, int> id = robot->getRobotID();
            if (id.first == RobotType::SAPPER) {
                std::cout << id.second << ", ";
            }
        }
        std::cout << std::endl;
    }
    else {
        int idReq = 0;
        if (curArgs.size() == 2) convertStringToInt(curArgs[1], idReq);

        int idxLastSapper = 0;
        std::vector<int> ids;
        for (int i = 0; i < robots.size(); i++) {
            std::pair<RobotType, int> id = robots[i]->getRobotID();
            if (id.first == RobotType::SAPPER) {
                if (curArgs.size() == 2 && id.second == idReq) {
                    if (curArgs[0] == "OFF") {
                        containerRemove(robots, i);
                        return true;
                    }
                    else return false;
                }
                ids.emplace_back(id.second);
                idxLastSapper = i;
            }
        }
        if (ids.size() == 1 && curArgs.size() == 1 && curArgs[0] == "OFF") {
            containerRemove(robots, idxLastSapper);
            return true;
        }

        if (curArgs[0] == "ON") {
            std::sort(ids.begin(), ids.end());
            int min_unused_id = 0;
            for (auto id : ids) {
                if (id == min_unused_id) min_unused_id++;
            }
            robots.emplace_back(new Sapper(repeater, min_unused_id));
            curArgs.emplace_back(std::to_string(min_unused_id));
            return true;
        }
    }
    return false;
}

bool Game::switchCollector() {
    if (curArgs.empty()) {
        std::cout << "Collectors ID list: ";
        for (auto* robot : robots) {
            std::pair<RobotType, int> id = robot->getRobotID();
            if (id.first == RobotType::COLLECTOR) {
                std::cout << id.second;
                if (id.second == activeCollectorID) std::cout << "(active)";
                std::cout << ",  ";
            }
        }
        std::cout << std::endl;
    }
    else {
        int newID;
        convertStringToInt(curArgs[0], newID);

        if (newID == activeCollectorID) return false;

        for (auto* robot : robots) {
            std::pair<RobotType, int> id = robot->getRobotID();
            if (id.first == RobotType::COLLECTOR && id.second == newID) {
                activeCollectorID = newID;
                return true;
            }
        }
    }
    return false;
}