#ifndef ROBOTS_IROBOT_H
#define ROBOTS_IROBOT_H

#include <set>
#include "Map.h"

enum class RobotType { COLLECTOR, SAPPER };
enum class Direction { NONE, UP, DOWN, LEFT, RIGHT };

class IRobot {
public:
    IRobot(int _id) {
        bActive = true;
        pos_r = 0;
        pos_c = 0;
        id = _id;
    }
    virtual ~IRobot() = default;

    const Map& getLocalMap() const { return localMap; }
    bool isActive() const { return bActive; }
    std::pair<int, int> getPosition() const { return std::make_pair(pos_r, pos_c); }
    virtual int getInvestment() const = 0;
    virtual std::pair<RobotType, int> getRobotID() const = 0;

    virtual std::set<MapElement> getWalkable() const = 0;
    virtual std::set<MapElement> getInvestible() const = 0;

    virtual void receiveNotificationUpdatedMap(std::pair<int, int> node, MapElement elem) = 0;
    virtual void receiveNotificationLanding(std::pair<int, int> pos) = 0;

    virtual void initMap() = 0;
    virtual bool move(Direction dir) = 0;
    virtual bool invest() = 0;
    virtual bool scan() = 0;

protected:
    void setActive(bool newActive) { bActive = newActive; }
    void setPosition(std::pair<int, int> newPos) { pos_r = newPos.first; pos_c = newPos.second; }

    int getID() const { return id; }
    Map& getMap() { return localMap; }

private:
    bool bActive;
    int pos_r;
    int pos_c;
    int id;
    Map localMap;
};

#endif
