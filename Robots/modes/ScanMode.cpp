#include "ScanMode.h"

ScanMode::ScanMode(Field *field, Collector *collector, Sapper *sapper, ConsoleView *gameView, int n) {
    this->field = field;
    this->collector = collector;
    this->sapper = sapper;
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

        vector<pair<int, int>> path = buildPath(rc, cc, ru, cu, {Cell::EMPTY, Cell::APPLE, Cell::DEFUSED_BOMB});
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

bool ScanMode::validateCell(int r, int c, const set<Cell>& canWalkOn) {
    if (sapper->isActive() && make_pair(r, c) == sapper->getPosition()) return false;
    if (canWalkOn.find(field->getCell(r, c)) == canWalkOn.end()) return false;
    return true;
}

string ScanMode::getPendingMessage() {
    string msg = pendingMessage;
    pendingMessage = "";
    return msg;
}
