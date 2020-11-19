#include "Collector.h"

Collector::Collector(Field &field) {
    active = true;
    apples = 0;
    pos_r = 0;
    pos_c = 0;
    scanned = new set<pair<int, int>>();
    this->field = &field;
    init();
}

Collector::~Collector() {
    scanned->clear();
    delete scanned;
    scanned = nullptr;
}

void Collector::init() {
    pair<int, int> pos = findSuitablePos();
    pos_r = pos.first;
    pos_c = pos.second;
    scanned->insert({pos_r, pos_c});
}

void Collector::setNewPosition(pair<int, int> new_pos) {
    pos_r = new_pos.first;
    pos_c = new_pos.second;
    if (field->getCell(pos_r, pos_c) == Cell::BOMB) active = false;
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

bool Collector::isActive() const {
    return active;
}

pair<int, int> Collector::findSuitablePos() {
    vector<pair<int, int>> possible;
    for (int r = 0; r < field->getRows(); r++) {
        for (int c = 0; c < field->getCols(); c++) {
            Cell cell = field->getCell(r, c);
            if (cell != Cell::BOMB && cell != Cell::ROCK) {
                possible.emplace_back(make_pair(r, c));
            }
        }
    }
    int idx = random(possible.size());
    return possible[idx];
}