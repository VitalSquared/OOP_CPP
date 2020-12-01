#include "Utils.h"

using namespace std;

int random(int max) {
    srand(time(nullptr));
    return rand() % max;
}

void delay(size_t ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

vector<string> splitString(const string& str, char ch) {
    vector<string> v;
    size_t pos = str.find(ch);
    size_t initialPos = 0;
    string substr;
    while (pos != string::npos) {
        substr = str.substr(initialPos, pos - initialPos);
        if (!substr.empty()) v.push_back(substr);
        initialPos = pos + 1;
        pos = str.find(ch, initialPos);
    }
    substr = str.substr(initialPos, min(pos, str.size()) - initialPos + 1);
    if (!substr.empty()) v.push_back(substr);
    return v;
}

std::pair<int, int> findSuitablePos(const std::map<std::pair<int, int>, MapElement>& data, const std::set<MapElement>& allowed) {
    std::vector<std::pair<int, int>> possible;
    for(auto cell: data) {
        if (allowed.find(cell.second) == allowed.end()) continue;
        possible.emplace_back(cell.first);
    }
    return possible[random(possible.size())];
}

vector<pair<int, int>> buildPath(int rs, int cs, int rf, int cf, const Map& scannedMap, const set<MapElement>& canWalkOn) {
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
        if (r == rf && c == cf) {
            cur_path.erase(cur_path.begin());
            return cur_path;
        }

        visited.insert(make_pair(r, c));

        pair<int,int> adjs[4] = { {r, c - 1}, {r, c + 1}, {r - 1, c}, {r + 1, c} };
        for (auto adj : adjs) {
            if (scannedMap.containsLocation(adj.first, adj.second) &&
                    canWalkOn.find(scannedMap.getElement(adj.first, adj.second)) != canWalkOn.end()) {
                if (visited.find(adj) == visited.end()) {
                    vector<pair<int, int>> new_path(cur_path);
                    new_path.emplace_back(adj);
                    q.push(new_path);
                }
            }
            else if (rf == adj.first && cf == adj.second) {
                return {};
            }
        }
    }
    return {};
}

Direction calcDirection(std::pair<int, int> start, std::pair<int, int> end) {
    int dr = end.first - start.first, dc = end.second - start.second;
    if (dr == 0) {
        if (dc == 1) return Direction::RIGHT;
        else return Direction::LEFT;
    }
    else {
        if (dr == 1) return Direction::DOWN;
        else return Direction::UP;
    }
}

std::vector<std::pair<int, int>> getAdjacentCoords(int pos_r, int pos_c) {
    return {{pos_r, pos_c - 1}, {pos_r, pos_c + 1}, {pos_r - 1, pos_c}, {pos_r + 1, pos_c}};
}

double calcDistance(std::pair<int, int> point1, std::pair<int, int> point2) {
    return sqrt(pow(abs(point1.first - point2.first), 2) + pow(abs(point1.second - point2.second), 2));
}