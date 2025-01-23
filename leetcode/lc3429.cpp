#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// since 2n is even we split into 2 sets
// 0, 1, 2, 3 ... n   n, n - 1, n - 2, n - 2 ... 3, 2, 1, 0
// dp(i, c1, c2) means coloring from index i (and of course its mirror) with the predecing color of i - 1, and its mirror
// as c1 and c2

// TC is O(k^n) where k is number of colors, n is number of houses

class Solution {
public:
    int len;
    int halfLen; // if len == 8, halfLen == 4, we do not need to care when index is >= halfLen
    vector<vector<int>> cost;
    vector<vector<vector<ll>>> dp;

    ll helper(int idx, int c1, int c2) {
        if (c1 == -1) {
            ll best = 1e12;
            for (int i = 0; i < 3; i ++) {
                for (int j = 0; j < 3; j ++) {
                    if (i == j) continue;
                    ll res = cost[idx][i] + cost[len - 1 - idx][j] + helper(idx + 1, i, j);
                    best = min(best, res);
                }
            }
            return best;
        } else if (idx >= halfLen) {
            return 0;
        } else if (dp[idx][c1][c2] != -1) {
            return dp[idx][c1][c2];
        } else {
            ll best = 1e12;
            for (int i = 0; i < 3; i ++) {
                for (int j = 0; j < 3; j ++) {
                    if (i == j || i == c1 || j == c2) continue;
                    ll res = cost[idx][i] + cost[len - 1 - idx][j] + helper(idx + 1, i, j);
                    best = min(best, res);
                }
            }
            dp[idx][c1][c2] = best;
            return best;
        }
    }

    long long minCost(int n, vector<vector<int>>& cost) {
        len = n;
        halfLen = n / 2;
        this->cost = cost;
        dp = vector(halfLen, vector(3, vector<ll>(3, -1L)));

        return helper(0, -1, -1);
    }

};

int main() {
    vector<vector<int>> cost = {{7,9,4},{2,7,3}};
    int n = 2;
    Solution sol;
    cout << sol.minCost(4, cost) << endl;

}