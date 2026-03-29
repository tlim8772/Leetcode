#include <bits/stdc++.h>
using namespace std;

// tricky.
// bitwise xor is not monotonic, so for (r, c) we cannot store the best (i.e max) solution.
// we must store all possible values that can be obtained from (r, c) to (R - 1, C - 1).
// since m * n <= 1000 and 0 <= grid[i][j] <= 1023, this is possible.

struct Hash {
    size_t operator()(const pair<int,int>& p) const {
        auto [a, b] = p;
        return ((size_t) a << 32) + b;
    }
};

class Solution {
public:
    int R, C;
    unordered_map<pair<int,int>, unordered_set<int>, Hash> store;

    void dp(int r, int c, const vector<vector<int>>& grid) {
        if (store.contains({r, c})) return;

        int my_num = grid[r][c];
        auto &ans = store[{r, c}];
        if (r == R - 1 && c == C - 1) {
            ans.insert(my_num);
            return;
        }
        
        if (c < C - 1) {
            dp(r, c + 1, grid);
            auto &next = store[{r, c + 1}];
            for (int x : next) {
                ans.insert(my_num ^ x);
            }
        }

        if (r < R - 1) {
            dp(r + 1, c, grid);
            auto &next = store[{r + 1, c}];
            for (int x : next) {
                ans.insert(my_num ^ x);
            }
        }

    }

    int minCost(vector<vector<int>>& grid) {
        R = grid.size(), C = grid[0].size();
        dp(0, 0, grid);
        auto &ans = store[{0, 0}];
        return *min_element(ans.begin(), ans.end());
    }
};

int main() {
    Solution sol;
    vector<vector<int>> grid = {{1,2}, {3,4}};
    int ans = sol.minCost(grid);
    println("{}", ans);
}