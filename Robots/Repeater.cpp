#include "Repeater.h"

Repeater::Repeater(const Map* globalMap) {
    this->globalMap = globalMap;
}

void Repeater::notifyAll(IRobot* sender, std::pair<int, int> node) {
    for(auto* robot: robots) {
        if (robot != sender) {
            robot->receiveNotification(node);
        }
    }
}

MapElement Repeater::getMapElement(int r, int c) {
    return globalMap->getElement(r, c);
}

void Repeater::connectRobot(IRobot *robot) {
    robots.emplace_back(robot);
}

Map Repeater::getCollectorsScannedMap() {
    Map scannedMap;
    for (auto* robot: robots) {
        if (robot->getRobotType() == RobotType::COLLECTOR) {
            scannedMap.mergeMap(robot->getLocalMap());
        }
    }
    return scannedMap;
}