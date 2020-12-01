#ifndef ROBOTS_COLLECTOR_H
#define ROBOTS_COLLECTOR_H

#include "IRobot.h"
#include "Repeater.h"
#include "Map.h"

class Collector : public IRobot {
public:
    Collector(std::pair<int, int> initPos, Repeater* repeater);
    ~Collector() override = default;
    const Map& getLocalMap() const override;
    bool isActive() const override;
    void setActive(bool newActive) override;
    std::pair<int, int> getPosition() const override;
    int getInvestment() const override;
    RobotType getRobotType() const override;
    std::set<MapElement> getWalkable() const override;
    std::set<MapElement> getInvestible() const override;
    void receiveNotification(std::pair<int, int> node, MapElement elem) override;
    bool move(Direction dir) override;
    bool invest() override;
    bool scan() override;

private:
    bool bActive;
    int pos_r, pos_c;
    int apples;
    Map localMap;
    Repeater* repeater;
};

#endif
