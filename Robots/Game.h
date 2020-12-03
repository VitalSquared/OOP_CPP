#ifndef ROBOTS_GAME_H
#define ROBOTS_GAME_H

#include <map>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include "ICommand.h"
#include "MoveCommand.h"
#include "ScanCommand.h"
#include "GrabCommand.h"
#include "ToggleSapperCommand.h"
#include "ChangeModeCommand.h"
#include "SwitchCollectorCommand.h"
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
    Game(const std::string& map_file, int cnt_collectors);
    ~Game();
    bool parseCommand(const std::string& cmd);
    bool step();

    const Map* getMap();
    const std::vector<IRobot*>& getRobots();
    IRobot* getActiveCollector();

private:
    std::map<std::string, ICommand*> commandsContainer;

    int activeCollectorID;
    std::vector<IRobot*> robots;

    IMode* mode;

    CommandType curCmd;
    std::vector<std::string> curArgs;

    Map* globalMap;

    Repeater* repeater;

    bool modeActivity();
    bool toggleSapper();
    bool switchCollector();
};

#endif
