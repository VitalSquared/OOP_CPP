#ifndef ROBOTS_REPEATER_H
#define ROBOTS_REPEATER_H

#include <vector>
#include "Map.h"
#include "IRobot.h"

class Repeater {
public:
    Repeater(const Map *globalMap, const std::map<IRobot*, std::pair<int, int>>* robots);
    ~Repeater() = default;

    void notifyAllUpdatedMap(IRobot* sender, std::pair<int, int> pos, MapElement elem);
    void notifyAllLanding(IRobot* sender, std::pair<int, int> pos);

    MapElement getMapElement(IRobot* sender, int r, int c);
    Map getCollectorsScannedMap(IRobot* sender);

    bool anyRobotsInPosition(IRobot* sender, std::pair<int, int> pos);

private:
    const Map* globalMap;
    const std::map<IRobot*, std::pair<int, int>>* robots;
};

#endif
