#include "Utils.h"
#include "Collector.h"

Collector::Collector(int id, Repeater* repeater) {
    bActive = true;
    apples = 0;
    this->id = id;
    pos_r = 0;
    pos_c = 0;
    this->repeater = repeater;
}

void Collector::initMap() {
    MapElement elem = repeater->getMapElement(this, pos_r, pos_c);
    localMap.addElement(pos_r, pos_c, elem);
    repeater->notifyAllUpdatedMap(this, std::make_pair(pos_r, pos_c), elem);
    localMap.mergeMap(repeater->getCollectorsScannedMap(this));
}

const Map& Collector::getLocalMap() const {
    return localMap;
}

bool Collector::isActive() const {
    return bActive;
}
std::pair<int, int> Collector::getPosition() const {
    return std::make_pair(pos_r, pos_c);
}

int Collector::getInvestment() const {
    return apples;
}

std::pair<RobotType, int> Collector::getRobotID() const {
    return std::make_pair(RobotType::COLLECTOR, id);
}

std::set<MapElement> Collector::getWalkable() const {
    return { MapElement::EMPTY, MapElement::APPLE };
}

std::set<MapElement> Collector::getInvestible() const {
    return { MapElement::APPLE };
}

void Collector::receiveNotificationUpdatedMap(std::pair<int, int> node, MapElement elem) {
    localMap.addElement(node.first, node.second, elem);
}

void Collector::receiveNotificationLanding(std::pair<int, int> pos) {
    if (getPosition() != pos) return;
    for (auto adj : getAdjacentCoords(0, 0)) {
        if (move(convertDeltaToDirection(adj))) {
            return;
        }
    }
    bActive = false;
}

bool Collector::move(Direction dir) {
    std::pair<int, int> newPos = getPosition() + convertDirectionToDelta(dir);
    if (containerContains(getWalkable(), localMap.getElement(newPos))) {
        if (!repeater->anyRobotsInPosition(this, newPos)) {
            pos_r = newPos.first;
            pos_c = newPos.second;
            return true;
        }
    }
    else if (localMap.getElement(newPos) == MapElement::BOMB) {
        bActive = false;
        return true;
    }
    return false;
}

bool Collector::invest() {
    if (containerContains(getInvestible(), localMap.getElement(pos_r, pos_c))) {
        apples++;
        localMap.addElement(pos_r, pos_c, MapElement::EMPTY);
        repeater->notifyAllUpdatedMap(this, getPosition(), MapElement::EMPTY);
        return true;
    }
    return false;
}

bool Collector::scan() {
    for (auto adj: getAdjacentCoords(pos_r, pos_c)) {
        if (!localMap.containsLocation(adj.first, adj.second)) {
            localMap.addElement(adj.first, adj.second, repeater->getMapElement(this, adj.first, adj.second));
            repeater->notifyAllUpdatedMap(this, adj, localMap.getElement(adj.first, adj.second));
        }
    }
    return true;
}