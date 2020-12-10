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
    globalMap = new Map(map_file);
    repeater = new Repeater(globalMap, &robots);
    mode = new ManualMode();

    std::vector<std::pair<int, int>> positions = findSuitablePos(cnt_collectors, globalMap->_getMap(), { MapElement::EMPTY, MapElement::APPLE });
    for (int i = 0; i < cnt_collectors; i++) {
        IRobot* collector = new Collector(repeater, i);
        robots.insert(std::make_pair(collector, positions[i]));
        collector->initMap();
    }
    activeCollectorID = 0;

    commandsContainer.insert(std::make_pair("MOVE", new MoveCommand(&robots, &activeCollectorID, repeater)));
    commandsContainer.insert(std::make_pair("GRAB", new GrabCommand(&robots, &activeCollectorID, repeater)));
    commandsContainer.insert(std::make_pair("SCAN", new ScanCommand(&robots, &activeCollectorID, repeater)));
    commandsContainer.insert(std::make_pair("SAPPER", new ToggleSapperCommand(&robots, &activeCollectorID, repeater)));
    commandsContainer.insert(std::make_pair("COLLECTOR", new SwitchCollectorCommand(&robots, &activeCollectorID, repeater)));
    commandsContainer.insert(std::make_pair("SET_MODE", new ChangeModeCommand(&mode)));
    curCmd = "";
}

Game::~Game() {
    for (auto& elem : commandsContainer) delete elem.second;
    commandsContainer.clear();

    for (auto robot : robots) delete robot.first;
    robots.clear();

    delete globalMap;
    globalMap = nullptr;

    delete mode;
    mode = nullptr;

    delete repeater;
    repeater = nullptr;
}

bool Game::parseCommand(const std::string &cmd) {
     bool validArgs;

    std::vector<std::string> split = splitString(cmd, ' ');
    if (split.empty()) {
        curArgs = {};
        curCmd = "";
        validArgs = false;
    }
    else {
        curCmd = std::string(split[0]);
        containerRemove(split, 0);
        curArgs = split;

        if (!containerContains(commandsContainer, curCmd)) validArgs = false;
        else validArgs = commandsContainer[curCmd]->validateArgs(curArgs);
    }
    return validArgs;
}

bool Game::step() {
    bool res = false;
    std::set<IRobot*> finishedWork;
    for (auto robot : robots) {
        bool invokeRes = mode->invokeCommand(robot.first, commandsContainer[curCmd], curArgs);
        if (robot.first->getRobotID().first == RobotType::COLLECTOR) {
            res = res || invokeRes;
            if (!invokeRes) finishedWork.insert(robot.first);
        }
    }

    if (dynamic_cast<ManualMode*>(mode) == nullptr) {
        if (containerContains(finishedWork, getActiveCollector()) && res) {
            for (auto robot : robots) {
                if (robot.first->getRobotID().first != RobotType::COLLECTOR ||
                    containerContains(finishedWork, robot.first))
                    continue;
                activeCollectorID = robot.first->getRobotID().second;
                break;
            }
        }
    }

    std::set<int> collectorIDs;
    for (auto robot = robots.cbegin(); robot != robots.cend();) {
        if (!robot->first->isActive()) {
            IRobot* to_remove = robot->first;
            robots.erase(robot++);
            delete to_remove;
        }
        else {
            collectorIDs.insert(robot->first->getRobotID().second);
            ++robot;
        }
    }

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

const std::map<IRobot*, std::pair<int, int>>& Game::getRobots() {
    return robots;
}

IRobot* Game::getActiveCollector() {
    for (auto robot : robots) {
        std::pair<RobotType, int> id = robot.first->getRobotID();
        if (id.first == RobotType::COLLECTOR && id.second == activeCollectorID) {
            return robot.first;
        }
    }
    return nullptr;
}

std::string Game::getActiveModeName() {
    if (mode == nullptr) return "NONE";
    return mode->getModeName();
}