#include "Repeater.h"

Repeater::Repeater(const Map* globalMap, const std::vector<IRobot*>* robots) {
    this->globalMap = globalMap;
    this->robots = robots;
}

void Repeater::notifyAllUpdatedMap(IRobot* sender, std::pair<int, int> node, MapElement elem) {
    if (robots == nullptr || sender == nullptr) return;
    for(auto* robot: *robots) {
        if (robot != sender) {
            robot->receiveNotificationUpdatedMap(node, elem);
        }
    }
}

void Repeater::notifyAllLanding(IRobot* sender, std::pair<int, int> pos) {
    if (robots == nullptr || sender == nullptr) return;
    for(auto* robot: *robots) {
        if (robot != sender) {
            robot->receiveNotificationLanding(pos);
        }
    }
}

MapElement Repeater::getMapElement(int r, int c) {
    return globalMap->getElement(r, c);
}

Map Repeater::getCollectorsScannedMap() {
    Map scannedMap;
    if (robots != nullptr) {
        for (auto *robot: *robots) {
            if (robot->getRobotID().first == RobotType::COLLECTOR) {
                scannedMap.mergeMap(robot->getLocalMap());
            }
        }
    }
    return scannedMap;
}

bool Repeater::anyRobotsInPosition(std::pair<int, int> pos) {
    if (robots == nullptr) return false;
    for (auto* robot : *robots) {
        if (robot->isActive() && robot->getPosition() == pos) return true;
    }
    return false;
}
