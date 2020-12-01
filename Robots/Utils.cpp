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