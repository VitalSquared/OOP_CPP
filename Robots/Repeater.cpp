#include "Repeater.h"

Repeater::Repeater(const Map* globalMap) {
    this->globalMap = globalMap;
}

void Repeater::notifyAllUpdatedMap(IRobot* sender, std::pair<int, int> node, MapElement elem) {
    for(auto* robot: robots) {
        if (robot != sender) {
            robot->receiveNotificationUpdatedMap(node, elem);
        }
    }
}

bool Repeater::notifyAllLanding(IRobot* sender, std::pair<int, int> pos) {
    for(auto* robot: robots) {
        if (robot != sender) {
            if (!robot->receiveNotificationLanding(pos)) return false;
        }
    }
    return true;
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
        if (robot->getRobotID().first == RobotType::COLLECTOR) {
            scannedMap.mergeMap(robot->getLocalMap());
        }
    }
    return scannedMap;
}

bool Repeater::anyRobotsInPosition(std::pair<int, int> pos) {
    for (auto* robot : robots) {
        if (robot->isActive() && robot->getPosition() == pos) return true;
    }
    return false;
}
