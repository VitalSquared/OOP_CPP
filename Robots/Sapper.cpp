#include "Utils.h"
#include "Sapper.h"

Sapper::Sapper(Repeater* repeater, int id) : IRobot(id) {
    bombs = 0;
    this->repeater = repeater;
}

void Sapper::initMap() {
    scan();
    repeater->notifyAllLanding(this, getPosition());
    invest();
}

int Sapper::getInvestment() const {
    return bombs;
}

std::pair<RobotType, int> Sapper::getRobotID() const {
    return std::make_pair(RobotType::SAPPER, getID());
}

std::set<MapElement> Sapper::getWalkable() const {
    return { MapElement::EMPTY, MapElement::APPLE, MapElement::BOMB };
}

std::set<MapElement> Sapper::getInvestible() const {
    return { MapElement::BOMB };
}

void Sapper::receiveNotificationUpdatedMap(std::pair<int, int> node, MapElement elem) {
    getMap().addElement(node.first, node.second, elem);
}

void Sapper::receiveNotificationLanding(std::pair<int, int> pos) {
    if (getPosition() != pos) return;
    for (auto adj : getAdjacentCoords(0, 0)) {
        if (move(convertDeltaToDirection(adj))) {
            return;
        }
    }
    setActive(false);
}

bool Sapper::move(Direction dir) {
    std::pair<int, int> newPos = getPosition() + convertDirectionToDelta(dir);

    if (containerContains(getWalkable(), getMap().getElement(newPos))) {
        if (!repeater->anyRobotsInPosition(this, newPos)) {
            setPosition(newPos);
            invest();
            return true;
        }
    }
    return false;
}

bool Sapper::invest() {
    if (containerContains(getInvestible(), getMap().getElement(getPosition()))) {
        bombs++;
        getMap().addElement(getPosition().first, getPosition().second, MapElement::EMPTY);
        repeater->notifyAllUpdatedMap(this, getPosition(), MapElement::EMPTY);
        return true;
    }
    return false;
}

bool Sapper::scan() {
    getMap().mergeMap(repeater->getCollectorsScannedMap(this));
    return true;
}