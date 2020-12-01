#include "Sapper.h"

Sapper::Sapper(Repeater* repeater) {
    bActive = false;
    bombs = 0;
    pos_r = 0;
    pos_c = 0;
    this->repeater = repeater;
    repeater->connectRobot(this);
}

const Map & Sapper::getLocalMap() const {
    return localMap;
}

bool Sapper::isActive() const {
    return bActive;
}

void Sapper::setActive(bool newActive) {
    bool bOldActive = bActive;
    bActive = newActive;
    if (!bOldActive && newActive) {
        scan();
        std::pair<int, int> new_pos = findSuitablePos(localMap.getMap(), getWalkable());
        pos_r = new_pos.first;
        pos_c = new_pos.second;
        invest();
    }
}

std::pair<int, int> Sapper::getPosition() const {
    return std::make_pair(pos_r, pos_c);
}

int Sapper::getInvestment() const {
    return bombs;
}

RobotType Sapper::getRobotType() const {
    return RobotType::SAPPER;
}

std::set<MapElement> Sapper::getWalkable() const {
    return { MapElement::EMPTY, MapElement::APPLE, MapElement::BOMB };
}

std::set<MapElement> Sapper::getInvestible() const {
    return { MapElement::BOMB };
}

void Sapper::receiveNotification(std::pair<int, int> node, MapElement elem) {
    localMap.addElement(node.first, node.second, elem);
}

bool Sapper::move(Direction dir) {
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
            invest();
            return true;
        }
    }
    return false;
}

bool Sapper::invest() {
    std::set<MapElement> investible = getInvestible();
    if (bActive && investible.find(localMap.getElement(pos_r, pos_c)) != investible.end()) {
        localMap.addElement(pos_r, pos_c, MapElement::EMPTY);
        bombs++;
        repeater->notifyAll(this, std::make_pair(pos_r, pos_c), MapElement::EMPTY);
        return true;
    }
    return false;
}

bool Sapper::scan() {
    localMap.mergeMap(repeater->getCollectorsScannedMap());
    return true;
}