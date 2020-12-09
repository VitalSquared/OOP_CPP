#ifndef ROBOTS_COLLECTOR_H
#define ROBOTS_COLLECTOR_H

#include "IRobot.h"
#include "Repeater.h"
#include "Map.h"

class Collector : public IRobot {
public:
    Collector(Repeater* repeater, int id);
    ~Collector() override = default;

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
    int apples;
    Repeater* repeater;
};

#endif
