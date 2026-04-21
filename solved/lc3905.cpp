#include <bits/stdc++.h>
using namespace std;

// just bfs from each source.

struct Hash {
    size_t operator()(const pair<int,int>& p1) const {
        return ((long long) p1.first << 32) + p1.second;
    }
};

class Solution {
public:
    vector<vector<int>> colorGrid(int n, int m, vector<vector<int>>& sources) {
        vector<pair<int,int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        auto valid = [n, m] (int r, int c) { return r >= 0 && r < n && c >= 0 && c < m; };

        // grid[r][c] is {color, timestamp}
        auto grid = vector<vector<pair<int,int>>>(n, vector<pair<int,int>>(m, {-1, -1}));
        auto q = deque<array<int, 3>>{};

        for (const auto s : sources) {
            q.push_back({s[0], s[1], s[2]});
        }

        int wave = 0;
        while (!q.empty()) {
            unordered_set<pair<int,int>, Hash> new_coors;

            for (int len = q.size(); len > 0; len--) {
                auto [x, y, c] = q.front(); q.pop_front();
                
                auto& [color, time] = grid[x][y];
                if (time != -1 && time < wave) continue;
                
                color = max(color, c);
                time = wave;
                new_coors.insert({x, y});
            }

            for (auto [x, y] : new_coors) {
                for (auto [dx, dy] : dirs) {
                    if (!valid(x + dx, y + dy)) continue;
                    q.push_back({x + dx, y + dy, grid[x][y].first});
                }
            }

            new_coors.clear();

            wave++;
        }

        auto out = vector<vector<int>>(n, vector<int>(m, -1));
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < m; c++) {
                out[r][c] = grid[r][c].first;
            }
        }
        return out;
    }
};

int main() {
    Solution sol;

    int n = 3, m = 3;
    vector<vector<int>> sources = {{0, 0, 1}, {2, 2, 2}};

    auto ans = sol.colorGrid(n, m, sources);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << ans[i][j] << ' ';
        }
        cout << endl;
    }
}