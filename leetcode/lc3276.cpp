#include <bits/stdc++.h>
using namespace std;

// dp. Since all elems are in [1, 100] we create a 2d vector with 100 rows
// for each row of index j, we store in it ri, if row i contains j + 1
// our dp is dp(j, bitset) where j means we are searching from elems of value j + 1 and above, and bitset is the rows taken already

class Solution {
public:
    vector<vector<int>> store = vector(100, vector<int>());
    vector<vector<int>> dp;

    void process(vector<vector<int>>& grid) {
        for (int r = 0; r < grid.size(); r ++) {
            for (int c = 0; c < grid[0].size(); c ++) {
                store[grid[r][c] - 1].push_back(r);
            }
        }
    }

    int helper(int bitset, int idx) {
        if (idx == store.size()) return 0;
        else if (dp[idx][bitset] != -1) return dp[idx][bitset];
        else {
            int best = 0;
            for (int r : store[idx]) {
                // if row r is not taken
                if (!((bitset >> r) & 1)) {
                    best = max(best, idx + 1 + helper(bitset + (1 << r), idx + 1));
                }
            }
            best = max(best, helper(bitset, idx + 1)); // dont take elem idx + 1
            dp[idx][bitset] = best;
            return best;
        }
    }

    int maxScore(vector<vector<int>>& grid) {
        int s = grid.size();
        dp = vector(100, vector(1 << s, -1));
        process(grid);
        return helper(0, 0);
    }




};

int main() {
    vector<vector<int>> grid = {{1,2,3},{4,3,2},{1,1,1}};
    Solution sol;
    cout << sol.maxScore(grid);
}