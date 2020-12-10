#ifndef ROBOTS_GAME_H
#define ROBOTS_GAME_H

#include <map>
#include <set>
#include <string>
#include <vector>
#include "ICommand.h"
#include "IRobot.h"
#include "IMode.h"
#include "Map.h"
#include "Repeater.h"

class Game {
public:
    Game(const std::string& map_file, int cnt_collectors);
    ~Game();

    bool parseCommand(const std::string& cmd);
    bool step();

    const std::map<IRobot *, std::pair<int, int>> & getRobots();
    IRobot* getActiveCollector();

    std::string getActiveModeName();

private:
    int activeCollectorID;
    std::string curCmd;
    std::vector<std::string> curArgs;
    std::map<std::string, ICommand*> commandsContainer;
    std::map<IRobot*, std::pair<int, int>> robots;
    IMode* mode;
    Map* globalMap;
    Repeater* repeater;
};

#endif
