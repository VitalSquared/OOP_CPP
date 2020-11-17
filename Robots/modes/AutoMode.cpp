#include "AutoMode.h"

AutoMode::AutoMode(Field *field, Collector *collector, Sapper *sapper, ConsoleView *gameView) {
    this->field = field;
    this->collector = collector;
    this->sapper = sapper;
    this->gameView = gameView;
    this->pendingMessage = "";
    this->gameView->setModeName("AUTO");
    startAutoCollecting();
}

void AutoMode::move(Direction dir) {
    pendingMessage = "You have to switch to MANUAL mode to execute this command";
}

void AutoMode::grab() {
    pendingMessage = "You have to switch to MANUAL mode to execute this command";
}

void AutoMode::scan() {
    pendingMessage = "You have to switch to MANUAL mode to execute this command";
}

void AutoMode::toggleSapper(bool enable) {
    pendingMessage = "You have to switch to MANUAL mode to execute this command";
}

string AutoMode::getPendingMessage() {
    string msg = pendingMessage;
    pendingMessage = "";
    return msg;
}

void AutoMode::startAutoCollecting() {
    set<pair<int, int>> *scanned = collector->getScanned();
    set<pair<int, int>> unreachable_apples, unreachable_bombs;

    while(true) {
        int rc = collector->getPosition().first, cc = collector->getPosition().second;
        int rs = sapper->getPosition().first, cs = sapper->getPosition().second;
        int ra = 0, ca = 0, rb = 0, cb = 0;
        bool foundApple = findClosestPoint(scanned, unreachable_apples, rc, cc, ra, ca, Cell::APPLE);
        if (!foundApple) break;

        vector<pair<int, int>> path_to_apple = buildPath(rc, cc, ra, ca);
        if (path_to_apple.empty()) {
            unreachable_apples.insert(make_pair(ra, ca));
            continue;
        }

        bool foundBomb = false;
        vector<pair<int, int>> path_to_bomb;
        if (sapper->getActive()) {
            foundBomb = findClosestPoint(scanned, unreachable_bombs, rs, cs, rb, cb, Cell::BOMB);
            if (foundBomb) {
                while (true) {
                    if (!foundBomb) break;
                    path_to_bomb = buildPath(rs, cs, rb, cb, Cell::BOMB);
                    if (path_to_bomb.empty()) {
                        unreachable_bombs.insert(make_pair(rb, cb));
                        foundBomb = findClosestPoint(scanned, unreachable_bombs, rs, cs, rb, cb, Cell::BOMB);
                    }
                    else break;
                }
            }
        }

        while (path_to_bomb.size() > path_to_apple.size()) path_to_bomb.pop_back();

        int i = 0, off = 0;
        for (auto pair : path_to_apple) {
            int r = pair.first, c = pair.second;
            collector->setNewPosition(make_pair(r, c));
            if (field->getCell(r, c) == Cell::APPLE) collector->collectApple();

            if (foundBomb) {
                int r1 = path_to_bomb[i].first, c1 = path_to_bomb[i].second;
                sapper->setNewPosition(make_pair(r1, c1));
            }

            if (r != rc || c != cc) {
                gameView->renderField();
                delay(1000);
            }
            i++;

            if (foundBomb) {
                if (i >= path_to_bomb.size()) {
                    rs = sapper->getPosition().first; cs = sapper->getPosition().second;
                    while (true) {
                        foundBomb = findClosestPoint(scanned, unreachable_bombs, rs, cs, rb, cb, Cell::BOMB);
                        if (!foundBomb) break;
                        path_to_bomb = buildPath(rs, cs, rb, cb, Cell::BOMB);
                        if (path_to_bomb.empty()) unreachable_bombs.insert(make_pair(rb, cb));
                        else break;
                    }
                    if (!path_to_bomb.empty()) path_to_bomb.erase(path_to_bomb.begin());
                    while (path_to_bomb.size() > path_to_apple.size() - off) path_to_bomb.pop_back();
                    off = i;
                    i = 0;
                }
            }
        }
    }
}

bool AutoMode::validateCell(int r, int c, Cell ignore) {
    if (!collector->hasScanned(r, c)) return false;
    if (field->getCell(r, c) != ignore && (field->getCell(r, c) == Cell::BOMB || field->getCell(r, c) == Cell::ROCK)) return false;
    return true;
}

bool AutoMode::findClosestPoint(set<pair<int,int>> *scanned, set<pair<int,int>>& unreachable, int& rr, int& cr, int &rp, int &cp, Cell point) {
    bool foundPoint = false;
    double min_dist = -1;
    for (auto pair : *scanned) {
        int r = pair.first;
        int c = pair.second;
        if (field->getCell(r, c) == point && unreachable.find(make_pair(r, c)) == unreachable.end()) {
            double dist = sqrt(pow(abs(r - rr), 2) + pow(abs(c - cr), 2));
            if (min_dist < 0 || dist < min_dist) {
                foundPoint = true;
                rp = r;
                cp = c;
                min_dist = dist;
            }
        }
    }
    return foundPoint;
}
