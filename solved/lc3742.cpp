#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxPathScore(vector<vector<int>>& grid, int k) {
        int R = grid.size(), C = grid[0].size();
        vector<int> store(R * C * (k + 1), -999999);

        auto to_idx = [C, k] (int i, int j, int z) { return i * C * (k + 1) + j * (k + 1) + z; };
        
        store[to_idx(0, 0, 0)] = 0;

        for (int s = 1; s <= R - 1 + C - 1; s++) {
            for (int r = max(0, s - C + 1); r <= min(R - 1, s); r++) {
                int c = s - r;

                for (int cost = 0; cost <= k; cost++) {
                    int pos = to_idx(r, c, cost);
                    
                    int next_cost = cost - (grid[r][c] + 1) / 2;

                    if (next_cost < 0) continue;

                    int up = (r > 0) ? grid[r][c] + store[to_idx(r - 1, c, next_cost)] : -999999;
                    int left = (c > 0) ? grid[r][c] + store[to_idx(r, c - 1, next_cost)] : -999999;

                    store[pos] = max(up, left);

                    
                }
            }
        }

        int best = -1;
        for (int cost = 0; cost <= k; cost++) {
            best = max(best, store[to_idx(R - 1, C - 1, cost)]);
        }
        return best;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> grid = {{0,1},{2,0}};
    cout << sol.maxPathScore(grid, 1) << endl;
}