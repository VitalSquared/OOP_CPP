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

bool Sapper::receiveNotificationLanding(std::pair<int, int> pos) {
    if (getPosition() != pos) return true;

    std::vector<std::pair<int, int>> adjs = getAdjacentCoords(0, 0);
    for (auto adj : adjs) {
        if (move(convertDeltaToDirection(adj))) {
            return true;
        }
    }
    bActive = false;
    return true;
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