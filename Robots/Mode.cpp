#include <queue>
#include <list>
#include "Mode.h"
#include "Utils.h"

using namespace std;

list<pair<int, int>> Mode::buildPath(int rs, int cs, int rf, int cf) {
    set<pair<int, int>> visited;
    queue<list<pair<int,int>>> q;

    list<pair<int,int>> init_path;
    init_path.emplace_back(make_pair(rs, cs));
    q.push(init_path);

    while (!q.empty()) {
        list<pair<int,int>> cur_path = list<pair<int,int>>(q.front());
        q.pop();

        if (visited.find(cur_path.back()) != visited.end()) continue;

        int r = cur_path.back().first, c = cur_path.back().second;
        if (r == rf && c == cf) return cur_path;

        visited.insert(make_pair(r, c));

        pair<int,int> neighbours[4] = { {r, c - 1}, {r, c + 1}, {r - 1, c}, {r + 1, c} };
        for (auto neighbour : neighbours) {
            if (visited.find(neighbour) == visited.end() && validateCell(neighbour.first, neighbour.second)) {
                list<pair<int, int>> new_path(cur_path);
                new_path.emplace_back(make_pair(neighbour.first, neighbour.second));
                q.push(new_path);
            }
        }
    }
    return list<pair<int,int>>();
}

ManualMode::ManualMode(Field *field, Collector *collector, ConsoleView *gameView) {
    this->field = field;
    this->collector = collector;
    this->gameView = gameView;
    this->pendingMessage = "";
}

void ManualMode::move(Direction dir) {
    int dr = 0, dc = 0;
    switch(dir) {
        case Direction::UP: dr = -1; break;
        case Direction::DOWN: dr = 1; break;
        case Direction::LEFT: dc = -1; break;
        case Direction::RIGHT: dc = 1; break;
    }
    int new_r = collector->getRow() + dr, new_c = collector->getCol() + dc;
    if (new_r < 0 || new_r >= field->getRows() || new_c < 0 || new_c >= field->getCols() ||
        !collector->hasScanned(new_r, new_c) || field->getCell(new_r, new_c) == Cell::ROCK) {
        pendingMessage = "I can't go there.";
    }
    else collector->setNewPosition(new_r, new_c);
}

void ManualMode::grab() {
    if (!collector->collectApple()) pendingMessage = "There are no apples here.";
}

void ManualMode::scan() {
    collector->scan();
}

void ManualMode::startAutoScanning(int n) {
    pendingMessage = "You need to switch to SCAN mode to execute this command.";
}

string ManualMode::getPendingMessage() {
    string msg = pendingMessage;
    pendingMessage = "";
    return msg;
}

string ManualMode::getModeName() {
    return "MANUAL";
}

bool ManualMode::validateCell(int r, int c) {
    return true;
}

ScanMode::ScanMode(Field *field, Collector *collector, ConsoleView *gameView) {
    this->field = field;
    this->collector = collector;
    this->gameView = gameView;
    this->pendingMessage = "";
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

void ScanMode::startAutoScanning(int n) {
    set<pair<int, int>> *scanned = collector->getScanned();
    set<pair<int, int>> unreachable;
    int steps = 0;

    while(steps < n) {
        bool foundUnknown = false;
        int rc = collector->getRow(), cc = collector->getCol();
        int ru = 0, cu = 0;
        double min_dist = -1;
        set<pair<int, int>> min_unknown;
        for (auto scan: *scanned) {
            int rs = scan.first, cs = scan.second;

            if ((rs == collector->getRow() && cs == collector->getCol() && scanned->size() > 1) ||
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

        srand(time(nullptr));
        int i = 0, j = rand() % min_unknown.size();
        for (auto un : min_unknown) {
            if (i == j) {
                ru = un.first;
                cu = un.second;
                break;
            }
            i++;
        }

        list<pair<int, int>> path = buildPath(rc, cc, ru, cu);
        if (path.empty()) {
            unreachable.insert(make_pair(ru, cu));
            continue;
        }

        for (auto cell : path) {
            int r = cell.first, c = cell.second;
            collector->setNewPosition(r, c);

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

bool ScanMode::validateCell(int r, int c) {
    if (r < 0 || r >= field->getRows() || c < 0 || c >= field->getCols()) return false;
    if (field->getCell(r, c) == Cell::BOMB || field->getCell(r, c) == Cell::ROCK) return false;
    return true;
}

string ScanMode::getPendingMessage() {
    string msg = pendingMessage;
    pendingMessage = "";
    return msg;
}

string ScanMode::getModeName() {
    return "SCANNING";
}

AutoMode::AutoMode(Field *field, Collector *collector, ConsoleView *gameView) {
    this->field = field;
    this->collector = collector;
    this->gameView = gameView;
    this->pendingMessage = "";
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

void AutoMode::startAutoScanning(int n) {
    pendingMessage = "You need to switch to SCAN mode to execute this command.";
}

string AutoMode::getPendingMessage() {
    string msg = pendingMessage;
    pendingMessage = "";
    return msg;
}

string AutoMode::getModeName() {
    return "AUTO";
}

void AutoMode::startAutoCollecting() {
    set<pair<int, int>> *scanned = collector->getScanned();
    set<pair<int, int>> unreachable;

    while(true) {
        bool foundApple = false;
        int rc = collector->getRow(), cc = collector->getCol();
        int ra = 0, ca = 0;
        double min_dist = -1;
        for (auto pair : *scanned) {
            int r = pair.first;
            int c = pair.second;
            if (field->getCell(r, c) == Cell::APPLE && unreachable.find(make_pair(r, c)) == unreachable.end()) {
                double dist = sqrt(pow(abs(r - rc), 2) + pow(abs(c - cc), 2));
                if (min_dist < 0 || dist < min_dist) {
                    foundApple = true;
                    ra = r;
                    ca = c;
                    min_dist = dist;
                }
            }
        }
        if (!foundApple) break;

        list<pair<int, int>> path = buildPath(rc, cc, ra, ca);
        if (path.empty()) {
            unreachable.insert(make_pair(ra, ca));
            continue;
        }
        for (auto pair : path) {
            int r = pair.first, c = pair.second;
            collector->setNewPosition(r, c);
            if (field->getCell(r, c) == Cell::APPLE) collector->collectApple();
            if (r != rc || c != cc) {
                gameView->renderField();
                delay(1000);
            }
        }
    }
}

bool AutoMode::validateCell(int r, int c) {
    if (!collector->hasScanned(r, c)) return false;
    if (field->getCell(r, c) == Cell::BOMB || field->getCell(r, c) == Cell::ROCK) return false;
    return true;
}
