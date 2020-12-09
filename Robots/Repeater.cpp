#include "Utils.h"
#include "Repeater.h"

Repeater::Repeater(const Map* globalMap, const std::map<IRobot*, std::pair<int, int>>* robots) {
    this->globalMap = globalMap;
    this->robots = robots;
}

void Repeater::notifyAllUpdatedMap(IRobot* sender, std::pair<int, int> pos, MapElement elem) {
    if (robots == nullptr || sender == nullptr) return;
    for(auto robot: *robots) {
        if (robot.first != sender) {
            robot.first->receiveNotificationUpdatedMap(robots->at(sender) + pos - robot.second, elem);
        }
    }
}

void Repeater::notifyAllLanding(IRobot* sender, std::pair<int, int> pos) {
    if (robots == nullptr || sender == nullptr) return;
    for(auto robot: *robots) {
        if (robot.first != sender) {
            robot.first->receiveNotificationLanding(robots->at(sender) + pos - robot.second);
        }
    }
}

MapElement Repeater::getMapElement(IRobot* sender, int r, int c) {
    return globalMap->getElement(robots->at(sender) + std::make_pair(r, c));
}

Map Repeater::getCollectorsScannedMap(IRobot* sender) {
    Map scannedMap;
    if (robots != nullptr) {
        for (auto robot: *robots) {
            if (robot.first->getRobotID().first == RobotType::COLLECTOR) {
                const std::vector<MapElement>& map = robot.first->getLocalMap()._getMap();
                int size = map.size();
                for (int i = 0; i < size; i++) {
                    std::pair<int, int> localPos = robot.second + Cantor_NumberToPair(i) - robots->at(sender);
                    scannedMap.addElement(localPos.first, localPos.second, map[i]);
                }
            }
        }
    }
    return scannedMap;
}

bool Repeater::anyRobotsInPosition(IRobot* sender, std::pair<int, int> pos) {
    if (robots == nullptr || sender == nullptr) return false;
    for (auto robot : *robots) {
        std::pair<int, int> localPos = robots->at(sender) + pos - robot.second;
        if (robot.first->isActive() && robot.first->getPosition() == localPos) return true;
    }
    return false;
}