#include "Mode.h"

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