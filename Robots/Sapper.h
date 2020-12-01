#ifndef ROBOTS_SAPPER_H
#define ROBOTS_SAPPER_H

#include "IRobot.h"
#include "Repeater.h"
#include "Map.h"
#include "Utils.h"

class Sapper : public IRobot {
public:
    Sapper(Repeater* repeater);
    ~Sapper() override = default;
    const Map& getLocalMap() const override;
    bool isActive() const override;
    void setActive(bool newActive) override;
    std::pair<int, int> getPosition() const override;
    RobotType getRobotType() const override;
    std::set<MapElement> getWalkable() const override;
    void receiveNotification(std::pair<int, int> node) override;
    bool move(Direction dir) override;
    bool invest() override;
    bool scan() override;

private:
    bool bActive;
    int pos_r, pos_c;
    Map localMap;
    Repeater* repeater;
};

#endif
