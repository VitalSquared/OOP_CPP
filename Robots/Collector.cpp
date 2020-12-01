#include "Collector.h"

Collector::Collector(std::pair<int, int> initPos, Repeater* repeater) {
    bActive = true;
    apples = 0;
    pos_r = initPos.first;
    pos_c = initPos.second;
    this->repeater = repeater;
    repeater->connectRobot(this);
    localMap.addElement(pos_r, pos_c, repeater->getMapElement(pos_r, pos_c)); //need to request map element
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

void Collector::receiveNotification(std::pair<int, int> node, MapElement elem) {
    localMap.addElement(node.first, node.second, elem);
}

bool Collector::move(Direction dir) {
    int dr = 0, dc = 0;
    switch(dir) {
        case Direction::RIGHT: dr = 0; dc = 1; break;
        case Direction::DOWN: dr = 1; dc = 0; break;
        case Direction::UP: dr = -1; dc = 0; break;
        case Direction::LEFT: dr = 0; dc = -1; break;
    }

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
        repeater->notifyAll(this, std::make_pair(pos_r, pos_c), MapElement::EMPTY);
        return true;
    }
    return false;
}

bool Collector::scan() {
    std::pair<int, int> adjs[4] = { {pos_r + 1, pos_c}, {pos_r - 1, pos_c},
                                   {pos_r, pos_c + 1}, {pos_r, pos_c - 1} };
    for (auto adj: adjs) {
        if (!localMap.containsLocation(adj.first, adj.second)) {
            localMap.addElement(adj.first, adj.second, repeater->getMapElement(adj.first, adj.second));
            repeater->notifyAll(this, adj, localMap.getElement(adj.first, adj.second));
        }
    }
    return true;
}