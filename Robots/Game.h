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

    const std::vector<IRobot*>& getRobots();
    IRobot* getActiveCollector();

private:
    int activeCollectorID;
    CommandType curCmd;
    std::vector<std::string> curArgs;
    std::map<std::string, ICommand*> commandsContainer;
    std::vector<IRobot*> robots;
    IMode* mode;
    Map* globalMap;
    Repeater* repeater;

    bool modeActivity();
    bool toggleSapper();
    bool switchCollector();
};

#endif
