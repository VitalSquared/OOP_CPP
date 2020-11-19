#include "ManualMode.h"

ManualMode::ManualMode(Field *field, Collector *collector, Sapper *sapper, ConsoleView *gameView) {
    this->field = field;
    this->collector = collector;
    this->sapper = sapper;
    this->gameView = gameView;
    this->pendingMessage = "";
    this->gameView->setModeName("MANUAL");
}

void ManualMode::move(Direction dir) {
    int dr = 0, dc = 0;
    switch(dir) {
        case Direction::UP: dr = -1; break;
        case Direction::DOWN: dr = 1; break;
        case Direction::LEFT: dc = -1; break;
        case Direction::RIGHT: dc = 1; break;
    }
    int new_r = collector->getPosition().first + dr, new_c = collector->getPosition().second + dc;
    if (new_r < 0 || new_r >= field->getRows() || new_c < 0 || new_c >= field->getCols() ||
        !collector->hasScanned(new_r, new_c) || field->getCell(new_r, new_c) == Cell::ROCK ||
        sapper->isActive() && make_pair(new_r, new_c) == sapper->getPosition()) {
        pendingMessage = "I can't go there.";
    }
    else collector->setNewPosition(make_pair(new_r, new_c));
}

void ManualMode::grab() {
    if (!collector->collectApple()) pendingMessage = "There are no apples here.";
}

void ManualMode::scan() {
    collector->scan();
}

void ManualMode::toggleSapper(bool enable) {
    if (sapper->isActive()) {
        if (enable) pendingMessage = "There is already a Sapper present.";
        else sapper->toggleSapper(false);
    }
    else {
        if (enable) sapper->toggleSapper(true);
        else pendingMessage = "There is no Sapper anyway.";
    }
}

string ManualMode::getPendingMessage() {
    string msg = pendingMessage;
    pendingMessage = "";
    return msg;
}

bool ManualMode::validateCell(int r, int c, const set<Cell>& canWalkOn) {
    return true;
}