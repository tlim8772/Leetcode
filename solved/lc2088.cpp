#include <bits/stdc++.h>
using namespace std;

// consider up pyramids first.
// (i, j) is a pyramid of height h, if (i, j), (i + 1, j - 1), (i + 1, j), (i + 1, j + 1)
// are pyramids of height h - 1
// for down pyramids, just reverse the grid.
// for space optimisation, we only need to store the grid for height h - 1.

class Solution {
public:
    int dp(const vector<vector<int>>& grid) {
        const int R = grid.size(), C = grid[0].size();
        auto valid = [R, C] (int r, int c) -> bool {return r >= 0 && r < R && c >= 0 && c < C;};
        int cnt = 0;
        vector<vector<int>> prev_height_store = grid;
        
        // start from height = 2.
        while (1) {
            bool found = false;
            vector<vector<int>> store(R, vector<int>(C, 0));
            for (int i = 0; i < R - 1; i++) {
                for (int j = 0; j < C; j++) {
                    bool res = prev_height_store[i][j];
                    if (!res) continue;

                    for (int k = j - 1; k < j + 2; k++) {
                        if (!valid(i, k)) {
                            res = false;
                            break;
                        }
                        res = res && prev_height_store[i + 1][k];
                        if (!res) break;
                    }
                    
                    store[i][j] = res;
                    cnt += res;
                    found = found || res;
                }
            }
           
            if (!found) {
                return cnt;
            } else {
                prev_height_store = store;
            }
        }
    }

    int countPyramids(vector<vector<int>>& grid) {
        int up = dp(grid);
        reverse(grid.begin(), grid.end());
        int down = dp(grid);
        return up + down;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> grid = {{0,1,1,0},{1,1,1,1}};
    int ans = sol.countPyramids(grid);
    cout << ans << endl;
}