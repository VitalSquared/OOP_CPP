#include <queue>
#include <vector>
#include <cmath>
#include "Mode.h"
#include "Utils.h"

using namespace std;

vector<pair<int, int>> Mode::buildPath(int rs, int cs, int rf, int cf, Cell ignore) {
    set<pair<int, int>> visited;
    queue<vector<pair<int,int>>> q;

    vector<pair<int,int>> init_path;
    init_path.emplace_back(make_pair(rs, cs));
    q.push(init_path);

    while (!q.empty()) {
        vector<pair<int,int>> cur_path = vector<pair<int,int>>(q.front());
        q.pop();

        if (visited.find(cur_path.back()) != visited.end()) continue;

        int r = cur_path.back().first, c = cur_path.back().second;
        if (r == rf && c == cf) return cur_path;

        visited.insert(make_pair(r, c));

        pair<int,int> neighbours[4] = { {r, c - 1}, {r, c + 1}, {r - 1, c}, {r + 1, c} };
        for (auto neighbour : neighbours) {
            if (visited.find(neighbour) == visited.end() && validateCell(neighbour.first, neighbour.second, ignore)) {
                vector<pair<int, int>> new_path(cur_path);
                new_path.emplace_back(make_pair(neighbour.first, neighbour.second));
                q.push(new_path);
            }
        }
    }
    return vector<pair<int,int>>();
}

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
        sapper->getActive() && make_pair(new_r, new_c) == sapper->getPosition()) {
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
    if (sapper->getActive()) {
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

bool ManualMode::validateCell(int r, int c, Cell ignore) {
    return true;
}

ScanMode::ScanMode(Field *field, Collector *collector, ConsoleView *gameView, int n) {
    this->field = field;
    this->collector = collector;
    this->gameView = gameView;
    this->pendingMessage = "";
    this->gameView->setModeName("SCANNING");
    startAutoScanning(n);
}

void ScanMode::move(Direction dir) {
    pendingMessage = "You have to switch to MANUAL mode to execute this command";
}

void ScanMode::grab() {
    pendingMessage = "You have to switch to MANUAL mode to execute this command";
}

void ScanMode::scan() {
    pendingMessage = "You have to switch to MANUAL mode to execute this command";
}

void ScanMode::toggleSapper(bool enable) {
    pendingMessage = "You have to switch to MANUAL mode to execute this command";
}

void ScanMode::startAutoScanning(int n) {
    set<pair<int, int>> *scanned = collector->getScanned();
    set<pair<int, int>> unreachable;
    int steps = 0;

    while(steps < n) {
        bool foundUnknown = false;
        int rc = collector->getPosition().first, cc = collector->getPosition().second;
        int ru = 0, cu = 0;
        double min_dist = -1;
        set<pair<int, int>> min_unknown;
        for (auto scan: *scanned) {
            int rs = scan.first, cs = scan.second;

            if ((rs == rc && cs == cc && scanned->size() > 1) ||
                    field->getCell(rs, cs) == Cell::BOMB || field->getCell(rs, cs) == Cell::ROCK ||
                    unreachable.find(make_pair(rs, cs)) != unreachable.end()) {
                continue;
            }

            pair<int, int> neighbours[4] = { {rs,cs - 1}, {rs,cs + 1}, {rs - 1, cs}, {rs + 1, cs} };
            for (auto neighbour : neighbours) {
                if (!collector->hasScanned(neighbour.first, neighbour.second)) {
                    double dist = sqrt(pow(abs(rs - rc), 2) + pow(abs(cs - cc), 2));
                    if (min_dist < 0 || dist < min_dist) {
                        foundUnknown = true;
                        min_dist = dist;
                        min_unknown.clear();
                    }
                    if (dist <= min_dist) min_unknown.insert(make_pair(rs, cs));
                }
            }
        }
        if (!foundUnknown) break;

        int i = 0, j = random(min_unknown.size());
        for (auto un : min_unknown) {
            if (i == j) {
                ru = un.first;
                cu = un.second;
                break;
            }
            i++;
        }

        vector<pair<int, int>> path = buildPath(rc, cc, ru, cu);
        if (path.empty()) {
            unreachable.insert(make_pair(ru, cu));
            continue;
        }

        for (auto cell : path) {
            int r = cell.first, c = cell.second;
            collector->setNewPosition(make_pair(r, c));

            if (rc != r || cc != c) {
                steps++;
                gameView->renderField();
                delay(1000);
            }

            int old_scanned = scanned->size();
            collector->scan();

            if (old_scanned != scanned->size()) {
                gameView->renderField();
                delay(1000);
            }

            if (steps >= n) break;
        }
    }
}

bool ScanMode::validateCell(int r, int c, Cell ignore) {
    if (r < 0 || r >= field->getRows() || c < 0 || c >= field->getCols()) return false;
    if (field->getCell(r, c) != ignore && (field->getCell(r, c) == Cell::BOMB || field->getCell(r, c) == Cell::ROCK)) return false;
    return true;
}

string ScanMode::getPendingMessage() {
    string msg = pendingMessage;
    pendingMessage = "";
    return msg;
}

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