#include "Utils.h"
#include "Sapper.h"

Sapper::Sapper(Repeater* repeater, int id) {
    bActive = true;
    this->id = id;
    bombs = 0;
    this->repeater = repeater;
    pos_r = 0;
    pos_c = 0;
    init();
}

void Sapper::init() {
    scan();
    std::pair<int, int> new_pos = findSuitablePos(1, localMap.getMap(), getWalkable())[0];
    repeater->notifyAllLanding(this, new_pos);
    pos_r = new_pos.first;
    pos_c = new_pos.second;
    invest();
}

const Map & Sapper::getLocalMap() const {
    return localMap;
}

bool Sapper::isActive() const {
    return bActive;
}

std::pair<int, int> Sapper::getPosition() const {
    return std::make_pair(pos_r, pos_c);
}

int Sapper::getInvestment() const {
    return bombs;
}

std::pair<RobotType, int> Sapper::getRobotID() const {
    return std::make_pair(RobotType::SAPPER, id);
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

void Sapper::receiveNotificationLanding(std::pair<int, int> pos) {
    if (getPosition() != pos) return;
    for (auto adj : getAdjacentCoords(0, 0)) {
        if (move(convertDeltaToDirection(adj))) {
            return;
        }
    }
    bActive = false;
}

bool Sapper::move(Direction dir) {
    std::pair<int, int> newPos = getPosition() + convertDirectionToDelta(dir);

    if (containerContains(getWalkable(), localMap.getElement(newPos))) {
        if (!repeater->anyRobotsInPosition(newPos)) {
            pos_r = newPos.first;
            pos_c = newPos.second;
            invest();
            return true;
        }
    }
    return false;
}

bool Sapper::invest() {
    if (containerContains(getInvestible(), localMap.getElement(pos_r, pos_c))) {
        bombs++;
        localMap.addElement(pos_r, pos_c, MapElement::EMPTY);
        repeater->notifyAllUpdatedMap(this, getPosition(), MapElement::EMPTY);
        return true;
    }
    return false;
}

bool Sapper::scan() {
    localMap.mergeMap(repeater->getCollectorsScannedMap());
    return true;
}