#include "Sapper.h"

Sapper::Sapper(Field &field, Collector *collector) {
    this->field = &field;
    this->collector = collector;
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
        if (new_pos == collector->getPosition()) {
            vector<pair<int, int>> collNewPos;
            int rc = new_pos.first, cc = new_pos.second;
            pair<int, int> adjs[4] = {{rc - 1, cc}, {rc + 1, cc}, {rc, cc - 1}, {rc, cc + 1}};
            for (auto adj : adjs) {
                Cell cell = field->getCell(adj.first, adj.second);
                if (cell != Cell::BOMB && cell != Cell::ROCK) {
                    collNewPos.emplace_back(adj);
                }
            }
            collector->setNewPosition(collNewPos[random(collNewPos.size())]);
        }
    }
}

pair<int, int> Sapper::getPosition() {
    return make_pair(pos_r, pos_c);
}

void Sapper::toggleSapper(bool newActive) {
    active = newActive;
    if (active) setNewPosition(findSuitablePos());
}

bool Sapper::isActive() const {
    return active;
}

pair<int, int> Sapper::findSuitablePos() {
    vector<pair<int, int>> possible;
    for (auto pos : *collector->getScanned()) {
        Cell cell = field->getCell(pos.first, pos.second);
        if (cell != Cell::ROCK) {
            if (pos == collector->getPosition()) {
                int cntSuitable = 0;
                int rc = pos.first, cc = pos.second;
                pair<int, int> adjs[4] = {{rc - 1, cc}, {rc + 1, cc}, {rc, cc - 1}, {rc, cc + 1}};
                for (auto adj : adjs) {
                    Cell cell = field->getCell(adj.first, adj.second);
                    if (cell != Cell::BOMB && cell != Cell::ROCK) cntSuitable++;
                }
                if (cntSuitable == 0) continue;
            }
            possible.emplace_back(pos);
        }
    }
    int idx = random(possible.size());
    return possible[idx];
}