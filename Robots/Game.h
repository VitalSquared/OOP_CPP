#ifndef ROBOTS_GAME_H
#define ROBOTS_GAME_H

#include <map>
#include <set>
#include <string>
#include <vector>
#include "ICommand.h"
#include "MoveCommand.h"
#include "ScanCommand.h"
#include "GrabCommand.h"
#include "ToggleSapperCommand.h"
#include "ChangeModeCommand.h"
#include "IRobot.h"
#include "Collector.h"
#include "Sapper.h"
#include "IMode.h"
#include "ManualMode.h"
#include "ScanMode.h"
#include "AutoMode.h"
#include "Map.h"
#include "Repeater.h"
#include "Utils.h"

class Game {
public:
    Game(const std::string& map_file);
    ~Game();
    bool parseCommand(const std::string& cmd);
    bool step();

    const Map* getMap();
    std::vector<const IRobot*> getRobots();

private:
    std::map<std::string, ICommand*> commandsContainer;

    IRobot* collector{};
    IRobot* sapper{};

    IMode* mode;

    CommandType curCmd;
    std::vector<std::string> curArgs;

    Map* globalMap;

    Repeater* repeater;

    bool modeActivity();
    bool toggleSapper();
};

#endif
