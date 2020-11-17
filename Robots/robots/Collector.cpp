#include "Collector.h"

Collector::Collector(Field &field) {
    isDead = false;
    apples = 0;
    pos_r = random(field.getRows());
    pos_c = random(field.getCols());
    scanned = new set<pair<int, int>>();
    scanned->insert({pos_r, pos_c});
    this->field = &field;
}

Collector::~Collector() {
    scanned->clear();
    delete scanned;
    scanned = nullptr;
}

void Collector::setNewPosition(pair<int, int> new_pos) {
    pos_r = new_pos.first;
    pos_c = new_pos.second;
    if (field->getCell(pos_r, pos_c) == Cell::BOMB) isDead = true;
}

pair<int, int> Collector::getPosition() {
    return make_pair(pos_r, pos_c);
}

bool Collector::hasScanned(int r_, int c_) {
    return scanned->find({r_, c_}) != scanned->end();
}

void Collector::scan() {
    scanned->insert({pos_r, pos_c - 1});
    scanned->insert({pos_r, pos_c + 1});
    scanned->insert({pos_r - 1, pos_c});
    scanned->insert({pos_r + 1, pos_c});
}

bool Collector::collectApple() {
    if (field->getCell(pos_r, pos_c) == Cell::APPLE) {
        apples++;
        field->setCell(pos_r, pos_c, Cell::EMPTY);
        return true;
    }
    return false;
}

set<pair<int,int>>* Collector::getScanned() {
    return scanned;
}

int Collector::getApples() const {
    return apples;
}

bool Collector::getDeadState() const {
    return isDead;
}