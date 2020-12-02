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
    int getInvestment() const override;
    RobotType getRobotType() const override;
    std::set<MapElement> getWalkable() const override;
    std::set<MapElement> getInvestible() const override;
    void receiveNotificationUpdatedMap(std::pair<int, int> node, MapElement elem) override;
    bool receiveNotificationLanding(std::pair<int, int> pos) override;
    bool move(Direction dir) override;
    bool invest() override;
    bool scan() override;

private:
    bool bActive;
    int pos_r, pos_c;
    int bombs;
    Map localMap;
    Repeater* repeater;
};

#endif
