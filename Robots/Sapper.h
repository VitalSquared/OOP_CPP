#ifndef ROBOTS_SAPPER_H
#define ROBOTS_SAPPER_H

#include "IRobot.h"
#include "Repeater.h"
#include "Map.h"

class Sapper : public IRobot {
public:
    Sapper(Repeater* repeater, int id);
    ~Sapper() override = default;

    const Map& getLocalMap() const override;
    bool isActive() const override;
    std::pair<int, int> getPosition() const override;
    int getInvestment() const override;
    std::pair<RobotType, int> getRobotID() const override;

    std::set<MapElement> getWalkable() const override;
    std::set<MapElement> getInvestible() const override;

    void receiveNotificationUpdatedMap(std::pair<int, int> node, MapElement elem) override;
    void receiveNotificationLanding(std::pair<int, int> pos) override;

    void initMap() override;
    bool move(Direction dir) override;
    bool invest() override;
    bool scan() override;

private:
    bool bActive;
    int pos_r;
    int pos_c;
    int bombs;
    int id;
    Map localMap;
    Repeater* repeater;

    void init();
};

#endif
