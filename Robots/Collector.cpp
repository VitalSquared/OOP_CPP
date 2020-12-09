#include "Utils.h"
#include "Collector.h"

Collector::Collector(Repeater* repeater, int id) : IRobot(id) {
    apples = 0;
    this->repeater = repeater;
}

void Collector::initMap() {
    auto pos = getPosition();
    MapElement elem = repeater->getMapElement(this, pos.first, pos.second);
    getMap().addElement(pos.first, pos.second, elem);
    repeater->notifyAllUpdatedMap(this, pos, elem);
    getMap().mergeMap(repeater->getCollectorsScannedMap(this));
}

int Collector::getInvestment() const {
    return apples;
}

std::pair<RobotType, int> Collector::getRobotID() const {
    return std::make_pair(RobotType::COLLECTOR, getID());
}

std::set<MapElement> Collector::getWalkable() const {
    return { MapElement::EMPTY, MapElement::APPLE };
}

std::set<MapElement> Collector::getInvestible() const {
    return { MapElement::APPLE };
}

void Collector::receiveNotificationUpdatedMap(std::pair<int, int> node, MapElement elem) {
    getMap().addElement(node.first, node.second, elem);
}

void Collector::receiveNotificationLanding(std::pair<int, int> pos) {
    if (getPosition() != pos) return;
    for (auto adj : getAdjacentCoords(0, 0)) {
        if (move(convertDeltaToDirection(adj))) {
            return;
        }
    }
    setActive(false);
}

bool Collector::move(Direction dir) {
    std::pair<int, int> newPos = getPosition() + convertDirectionToDelta(dir);
    if (containerContains(getWalkable(), getMap().getElement(newPos))) {
        if (!repeater->anyRobotsInPosition(this, newPos)) {
            setPosition(newPos);
            return true;
        }
    }
    else if (getMap().getElement(newPos) == MapElement::BOMB) {
        setActive(false);
        return true;
    }
    return false;
}

bool Collector::invest() {
    if (containerContains(getInvestible(), getMap().getElement(getPosition()))) {
        apples++;
        getMap().addElement(getPosition().first, getPosition().second, MapElement::EMPTY);
        repeater->notifyAllUpdatedMap(this, getPosition(), MapElement::EMPTY);
        return true;
    }
    return false;
}

bool Collector::scan() {
    for (auto adj: getAdjacentCoords(getPosition())) {
        if (!getMap().containsLocation(adj.first, adj.second)) {
            getMap().addElement(adj.first, adj.second, repeater->getMapElement(this, adj.first, adj.second));
            repeater->notifyAllUpdatedMap(this, adj, getMap().getElement(adj.first, adj.second));
        }
    }
    return true;
}