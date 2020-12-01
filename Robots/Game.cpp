#include "Game.h"

Game::Game(const std::string& map_file) {
    commandsContainer.insert(std::make_pair("MOVE", new MoveCommand()));
    commandsContainer.insert(std::make_pair("GRAB", new GrabCommand()));
    commandsContainer.insert(std::make_pair("SCAN", new ScanCommand()));
    commandsContainer.insert(std::make_pair("SAPPER", new ToggleSapperCommand()));
    commandsContainer.insert(std::make_pair("SET_MODE", new ChangeModeCommand()));

    globalMap = new Map(map_file);

    repeater = new Repeater(globalMap);

    collector = new Collector(findSuitablePos(globalMap->getMap(), { MapElement::EMPTY, MapElement::APPLE }), repeater);
    sapper = new Sapper(repeater);
    mode = new ManualMode();

    curCmd = CommandType::UNKNOWN;
}

Game::~Game() {
    for (auto& elem : commandsContainer) {
        delete elem.second;
    }
    commandsContainer.clear();

    delete collector;
    delete sapper;
    collector = nullptr;
    sapper = nullptr;

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
        split.erase(split.begin());
        curArgs = split;

        if (commandsContainer.find(main_cmd) == commandsContainer.end()) {
            curCmd = CommandType::UNKNOWN;
        } else {
            curCmd = commandsContainer[main_cmd]->validateArgs(curArgs);
        }
    }
    return curCmd != CommandType::UNKNOWN;
}

bool Game::step() {
    switch(curCmd) {
        case CommandType::SET_MODE:
            return modeActivity();
        case CommandType::SAPPER:
            return toggleSapper();
        default:
            return mode->invokeCommand(collector, curCmd, curArgs);
    }
}

const Map* Game::getMap() {
    return globalMap;
}

std::vector<const IRobot *> Game::getRobots() {
    return { collector, sapper };
}

bool Game::modeActivity() {
    if (curArgs[0] == "manual") {
        if (mode->getModeType() == ModeType::MANUAL) return false;
        else {
            delete mode;
            mode = new ManualMode();
        }
    }
    else if (curArgs[0] == "scan"){
        if (mode->getModeType() == ModeType::SCAN) return false;
        else {
            delete mode;
            mode = new ScanMode();
        }
    }
    else if (curArgs[0] == "auto") {
        if (mode->getModeType() == ModeType::AUTO) return false;
        else {
            delete mode;
            mode = new AutoMode();
        }
    }
    else return false;

    return true;
}

bool Game::toggleSapper() {
    if (sapper->isActive() && curArgs[0] == "ON" || !sapper->isActive() && curArgs[0] == "OFF") {
        return false;
    }
    else {
        sapper->setActive(!sapper->isActive());
    }
    return true;
}
