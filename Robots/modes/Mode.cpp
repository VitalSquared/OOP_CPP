#include "Mode.h"

using namespace std;

vector<pair<int, int>> Mode::buildPath(int rs, int cs, int rf, int cf, const set<Cell>& canWalkOn) {
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
            if (visited.find(neighbour) == visited.end() && validateCell(neighbour.first, neighbour.second, canWalkOn)) {
                vector<pair<int, int>> new_path(cur_path);
                new_path.emplace_back(make_pair(neighbour.first, neighbour.second));
                q.push(new_path);
            }
            if (!validateCell(neighbour.first, neighbour.second, canWalkOn) && rf == neighbour.first && cf == neighbour.second) {
                return {};
            }
        }
    }
    return {};
}

bool Mode::findClosestPoint(Field *field, set<pair<int,int>> *scanned, set<pair<int,int>>& unreachable,
                            int& rr, int& cr, int &rp, int &cp, Cell point) {
    bool foundPoint = false;
    double min_dist = -1;
    set<pair<int, int>> possible;
    for (auto pair : *scanned) {
        int r = pair.first;
        int c = pair.second;
        if (field->getCell(r, c) == point && unreachable.find(make_pair(r, c)) == unreachable.end()) {
            double dist = sqrt(pow(abs(r - rr), 2) + pow(abs(c - cr), 2));
            if (min_dist < 0 || dist < min_dist) {
                foundPoint = true;
                min_dist = dist;
                possible.clear();
            }
            if (dist <= min_dist) possible.insert(make_pair(r, c));
        }
    }

    if (foundPoint) {
        int i = 0, j = random(possible.size());
        for (auto un : possible) {
            if (i == j) {
                rp = un.first;
                cp = un.second;
                break;
            }
            i++;
        }
    }

    return foundPoint;
}
