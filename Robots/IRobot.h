#ifndef ROBOTS_IROBOT_H
#define ROBOTS_IROBOT_H

#include <set>
#include "Map.h"

enum class RobotType { COLLECTOR, SAPPER };
enum class Direction { NONE, UP, DOWN, LEFT, RIGHT };

class IRobot {
public:
    virtual ~IRobot() = default;
    virtual const Map& getLocalMap() const = 0;
    virtual bool isActive() const = 0;
    virtual std::pair<int, int> getPosition() const = 0;
    virtual int getInvestment() const = 0;
    virtual std::pair<RobotType, int> getRobotID() const = 0;
    virtual std::set<MapElement> getWalkable() const = 0;
    virtual std::set<MapElement> getInvestible() const = 0;
    virtual void receiveNotificationUpdatedMap(std::pair<int, int> node, MapElement elem) = 0;
    virtual bool receiveNotificationLanding(std::pair<int, int> pos) = 0;
    virtual bool move(Direction dir) = 0;
    virtual bool invest() = 0;
    virtual bool scan() = 0;
};

#endif
