#include "Game.h"

Game::Game(const std::string& map_file, int cnt_collectors) {
    commandsContainer.insert(std::make_pair("MOVE", new MoveCommand()));
    commandsContainer.insert(std::make_pair("GRAB", new GrabCommand()));
    commandsContainer.insert(std::make_pair("SCAN", new ScanCommand()));
    commandsContainer.insert(std::make_pair("SAPPER", new ToggleSapperCommand()));
    commandsContainer.insert(std::make_pair("SET_MODE", new ChangeModeCommand()));
    commandsContainer.insert(std::make_pair("COLLECTOR", new SwitchCollectorCommand()));

    globalMap = new Map(map_file);

    repeater = new Repeater(globalMap);

    std::vector<std::pair<int, int>> positions = findSuitablePos(cnt_collectors, globalMap->getMap(), { MapElement::EMPTY, MapElement::APPLE });
    for (int i = 0; i < cnt_collectors; i++)
        robots.emplace_back(new Collector(i, positions[i], repeater));
    activeCollectorID = 0;

    mode = new ManualMode();

    curCmd = CommandType::UNKNOWN;
}

Game::~Game() {
    for (auto& elem : commandsContainer) delete elem.second;
    commandsContainer.clear();

    for (auto* robot : robots) delete robot;
    robots.clear();

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
            if (res && !getActiveCollector()->isActive()) {
                for (int i = 0; i < robots.size(); i++) {
                    if (robots[i]->getRobotID().second == activeCollectorID) {
                        robots.erase(robots.begin() + i);
                        break;
                    }
                }
            }
            break;
    }

    std::set<int> collectorIDs;
    bool bFoundInactive;
    do {
        bFoundInactive = false;
        for (int i = 0; i < robots.size(); i++) {
            if (!robots[i]->isActive()) {
                robots.erase(robots.begin() + i);
                bFoundInactive = true;
                break;
            }
            if (robots[i]->getRobotID().first == RobotType::COLLECTOR) {
                collectorIDs.insert(robots[i]->getRobotID().second);
            }
        }
    } while (bFoundInactive);

    if (!containerContains(collectorIDs, activeCollectorID)) {
        if (!collectorIDs.empty()) {
            int idx = random(collectorIDs.size()), i = 0;
            for (auto elem : collectorIDs) {
                if (i == idx) {
                    activeCollectorID = elem;
                    break;
                }
                i++;
            }
        }
    }
    return res;
}

const Map* Game::getMap() {
    return globalMap;
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
    else if (curArgs[0] == "scan") {
        if (mode->getModeType() != ModeType::SCAN) {
            delete mode;
            mode = new ScanMode();
        }
        bool res = false;
        for (auto* robot : robots) {
            if (robot->getRobotID().first == RobotType::COLLECTOR) {
                res = mode->invokeCommand(robot, curCmd, curArgs) || res;
            }
        }
        if (!res) {
            delete mode;
            mode = new ManualMode();
        }
        return res;
    }
    else if (curArgs[0] == "auto") {
        if (mode->getModeType() != ModeType::AUTO) {
            delete mode;
            mode = new AutoMode();
        }
        bool res = false;
        for (auto* robot : robots) {
            bool invokeRes = mode->invokeCommand(robot, curCmd, curArgs);
            if (robot->getRobotID().first == RobotType::COLLECTOR) {
                res = res || invokeRes;
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
                        robots.erase(robots.begin() + i);
                        return true;
                    }
                    else return false;
                }
                ids.emplace_back(id.second);
                idxLastSapper = i;
            }
        }
        if (ids.size() == 1 && curArgs.size() == 1 && curArgs[0] == "OFF") {
            robots.erase(robots.begin() + idxLastSapper);
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