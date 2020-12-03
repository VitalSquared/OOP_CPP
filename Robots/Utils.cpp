#include <chrono>
#include <thread>
#include <ctime>
#include <iostream>
#include <cmath>
#include <queue>
#include <fstream>
#include <windows.h>
#include "Utils.h"

using namespace std;

int random(int max) {
    return rand() % max;
}

void delay(size_t ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

void generateMap(int w, int h, ofstream& sv_file) {
    sv_file << h << " " << w << endl;
    std::cout << "0%\r";
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            int type = random(10);

            if (type == 2) sv_file << "B";
            else if (type == 6) sv_file << "R";
            else if (type == 8) sv_file << "A";
            else sv_file << " ";
        }
        sv_file << endl;
        int percent = (int)(100.0 * r / h);
        std::cout << std::string(percent, '.') << percent << "%" << "\r";
    }
    std::cout << std::string(100, '.') << "100%" << std::endl;
}

std::pair<int, int> operator+(std::pair<int, int> p1, std::pair<int, int> p2) {
    return std::make_pair(p1.first + p2.first, p1.second + p2.second);
}

std::pair<int, int> operator-(std::pair<int, int> p1, std::pair<int, int> p2) {
    return std::make_pair(p1.first - p2.first, p1.second - p2.second);
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

bool fileExists(const std::string& file_name) {
    ifstream file(file_name);
    if (file.is_open()) {
        file.close();
        return true;
    }
    return false;
}


std::vector<std::pair<int, int>> findSuitablePos(int count, const std::map<std::pair<int, int>, MapElement>& data, const std::set<MapElement>& allowed) {
    std::vector<std::pair<int, int>> possible;
    std::vector<std::pair<int, int>> result;
    for(auto cell: data) {
        if (!containerContains(allowed, cell.second)) continue;
        possible.emplace_back(cell.first);
    }
    for (int i = 0; i < count; i++) {
        int idx = random(possible.size());
        result.emplace_back(possible[idx]);
        containerRemove(possible, idx);
    }
    return result;
}

vector<pair<int, int>> buildPath(std::pair<int, int> start, std::pair<int, int> end, const Map& scannedMap,
                                 const set<MapElement>& canWalkOn, const std::set<std::pair<int, int>>& unreachable) {
    int rs = start.first, cs = start.second, rf = end.first, cf = end.second;
    set<pair<int, int>> visited;
    queue<vector<pair<int,int>>> _queue;

    vector<pair<int,int>> init_path;
    init_path.emplace_back(make_pair(rs, cs));
    _queue.push(init_path);

    while (!_queue.empty()) {
        vector<pair<int,int>> cur_path = vector<pair<int,int>>(_queue.front());
        _queue.pop();

        if (visited.find(cur_path.back()) != visited.end()) continue;

        int r = cur_path.back().first, c = cur_path.back().second;
        if (r == rf && c == cf) {
            cur_path.erase(cur_path.begin());
            return cur_path;
        }

        visited.insert(make_pair(r, c));

        for (auto adj : getAdjacentCoords(r, c)) {
            if (scannedMap.containsLocation(adj.first, adj.second) &&
                !containerContains(unreachable, adj) &&
                containerContains(canWalkOn, scannedMap.getElement(adj.first, adj.second)))
            {
                if (!containerContains(visited, adj)) {
                    vector<pair<int, int>> new_path(cur_path);
                    new_path.emplace_back(adj);
                    _queue.push(new_path);
                }
            }
            else if (rf == adj.first && cf == adj.second) return {};
        }
    }
    return {};
}

std::vector<std::pair<int, int>> getAdjacentCoords(int pos_r, int pos_c) {
    return {{pos_r, pos_c - 1}, {pos_r, pos_c + 1}, {pos_r - 1, pos_c}, {pos_r + 1, pos_c}};
}

std::vector<std::pair<int, int>> getAdjacentCoords(std::pair<int, int> pos) {
    return getAdjacentCoords(pos.first, pos.second);
}

double calcDistance(std::pair<int, int> point1, std::pair<int, int> point2) {
    return sqrt(pow(abs(point1.first - point2.first), 2) + pow(abs(point1.second - point2.second), 2));
}

bool convertStringToInt(const std::string& str, int& out) {
    try {
        out = stoi(str);
        return true;
    }
    catch (exception&) {
        return false;
    }
}

Direction convertStringToDirection(const std::string &str) {
    if (str == "U") return Direction::UP;
    else if (str == "D") return Direction::DOWN;
    else if (str == "R") return Direction::RIGHT;
    else if (str == "L") return Direction::LEFT;
    return Direction::NONE;
}

Direction convertDeltaToDirection(std::pair<int, int> _pair) {
    if (std::make_pair(1, 0) == _pair) return Direction::DOWN;
    else if (std::make_pair(-1, 0) == _pair) return Direction::UP;
    else if (std::make_pair(0, 1) == _pair) return Direction::RIGHT;
    else if (std::make_pair(0, -1) == _pair) return Direction::LEFT;
    else return Direction::NONE;
}

std::pair<int, int> convertDirectionToDelta(Direction dir) {
    std::pair<int, int> delta;
    switch(dir) {
        case Direction::RIGHT: delta = std::make_pair(0, 1); break;
        case Direction::DOWN: delta = std::make_pair(1, 0); break;
        case Direction::UP: delta = std::make_pair(-1, 0); break;
        case Direction::LEFT: delta = std::make_pair(0, -1); break;
        case Direction::NONE: delta = std::make_pair(0, 0); break;
    }
    return delta;
}