#include "Collector.h"

Collector::Collector(std::pair<int, int> initPos, Repeater* repeater) {
    bActive = true;
    apples = 0;
    pos_r = initPos.first;
    pos_c = initPos.second;
    this->repeater = repeater;
    repeater->connectRobot(this);
    localMap.addElement(pos_r, pos_c, repeater->getMapElement(pos_r, pos_c));
}

const Map & Collector::getLocalMap() const {
    return localMap;
}

bool Collector::isActive() const {
    return bActive;
}

void Collector::setActive(bool newActive) {
    bActive = newActive;
}

std::pair<int, int> Collector::getPosition() const {
    return std::make_pair(pos_r, pos_c);
}

int Collector::getInvestment() const {
    return apples;
}

RobotType Collector::getRobotType() const {
    return RobotType::COLLECTOR;
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

bool Collector::receiveNotificationLanding(std::pair<int, int> pos) {
    if (getPosition() != pos) return true;

    std::vector<std::pair<int, int>> adjs = getAdjacentCoords(0, 0);
    for (auto adj : adjs) {
        if (move(convertPairToDirection(adj))) {
            return true;
        }
    }
    return false;
}

bool Collector::move(Direction dir) {
    std::pair<int, int> delta = convertDirectionToDelta(dir);
    int dr = delta.first, dc = delta.second;

    auto walkable = getWalkable();
    if (walkable.find(localMap.getElement(pos_r + dr, pos_c + dc)) != walkable.end()) {
        if (!repeater->anyRobotsInPosition(std::make_pair(pos_r + dr, pos_c + dc))) {
            pos_r += dr;
            pos_c += dc;
            return true;
        }
    }
    return false;
}

bool Collector::invest() {
    std::set<MapElement> investible = getInvestible();
    if (investible.find(localMap.getElement(pos_r, pos_c)) != investible.end()) {
        localMap.addElement(pos_r, pos_c, MapElement::EMPTY);
        apples++;
        repeater->notifyAllUpdatedMap(this, std::make_pair(pos_r, pos_c), MapElement::EMPTY);
        return true;
    }
    return false;
}

bool Collector::scan() {
    std::vector<std::pair<int, int>> adjs = getAdjacentCoords(pos_r, pos_c);
    for (auto adj: adjs) {
        if (!localMap.containsLocation(adj.first, adj.second)) {
            localMap.addElement(adj.first, adj.second, repeater->getMapElement(adj.first, adj.second));
            repeater->notifyAllUpdatedMap(this, adj, localMap.getElement(adj.first, adj.second));
        }
    }
    return true;
}