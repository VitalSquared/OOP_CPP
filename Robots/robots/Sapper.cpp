#include "Sapper.h"

Sapper::Sapper(Field &field, set<pair<int,int>> *collectorScanned) {
    this->field = &field;
    this->collectorScanned = collectorScanned;
    active = false;
    pos_r = 0;
    pos_c = 0;
}

void Sapper::setNewPosition(pair<int, int> new_pos) {
    if (active) {
        pos_r = new_pos.first;
        pos_c = new_pos.second;
        if (field->getCell(pos_r, pos_c) == Cell::BOMB) {
            field->setCell(pos_r, pos_c, Cell::DEFUSED_BOMB);
        }
    }
}

pair<int, int> Sapper::getPosition() {
    return make_pair(pos_r, pos_c);
}

void Sapper::toggleSapper(bool newActive) {
    active = newActive;
    if (active) {
        int i = 0, req = random(collectorScanned->size());
        for (auto coord : *collectorScanned) {
            if (i == req) {
                pos_r = coord.first;
                pos_c = coord.second;
                break;
            }
            i++;
        }
        setNewPosition(make_pair(pos_r, pos_c));
    }
}

bool Sapper::getActive() const {
    return active;
}
