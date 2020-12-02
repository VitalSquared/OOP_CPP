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
        if (repeater->notifyAllLanding(this, new_pos)) {
            pos_r = new_pos.first;
            pos_c = new_pos.second;
            invest();
        }
        else bActive = false;
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

void Sapper::receiveNotificationUpdatedMap(std::pair<int, int> node, MapElement elem) {
    localMap.addElement(node.first, node.second, elem);
}

bool Sapper::receiveNotificationLanding(std::pair<int, int> pos) {
    if (getPosition() != pos) return true;

    std::vector<std::pair<int, int>> adjs = getAdjacentCoords(0, 0);
    for (auto adj : adjs) {
        if (move(convertPairToDirection(adj))) {
            return true;
        }
    }
    return false;
}

bool Sapper::move(Direction dir) {
    std::pair<int, int> delta = convertDirectionToDelta(dir);
    int dr = delta.first, dc = delta.second;

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
        repeater->notifyAllUpdatedMap(this, std::make_pair(pos_r, pos_c), MapElement::EMPTY);
        return true;
    }
    return false;
}

bool Sapper::scan() {
    localMap.mergeMap(repeater->getCollectorsScannedMap());
    return true;
}