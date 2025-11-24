#include <bits/stdc++.h>
using namespace std;

// dp(hasTake, i, j, bm)
// bm is the bitmask of group 2, 1 means has matched with an elem in group 1
// i means currently matching for elem i of group 1
// j means currently considering elem j of group 2
// hasTake means has elem i match with at least 1 elem in group 2
// then is just match/no match dp

class Solution {
public:
    int LEN1, LEN2;
    int dp[2][12][12][1 << 12];

    inline void reset() {
        for (int i = 0; i < 2; i ++) {
            for (int j = 0; j < 12; j ++) {
                for (int k = 0; k < 12; k ++) {
                    for (int m = 0; m < (1 << 12); m ++) {
                        dp[i][j][k][m] = -1;
                    }
                }
            }
        }
    }

    int helper(bool hasTake, int i, int j, int bm, vector<vector<int>>& cost) {
        if (i == LEN1) {
            if (bm == (1 << LEN2) - 1) {
                return 0;
            } else {
                return 999999;
            }
        } else if (j == LEN2) {
            if (!hasTake) {
                return 999999;
            } else {
                return helper(false, i + 1, 0, bm, cost);
            }
        } 
        
        int &ans = dp[hasTake][i][j][bm];
        if (ans != -1) {
            return ans;
        } else {
            int match = cost[i][j] + helper(1, i, j + 1, bm | (1 << j), cost);
            int noMatch = helper(hasTake, i, j + 1, bm, cost);
            ans = min(match, noMatch);
            return ans;
        }
    }

    int connectTwoGroups(vector<vector<int>>& cost) {
        LEN1 = cost.size(); LEN2 = cost[0].size();
        reset();

        int ans = helper(false, 0, 0, 0, cost);
        return ans;
    }


};

int main() {
    Solution sol;
    vector<vector<int>> cost = {{15,96},{36,2}};

    cout << sol.connectTwoGroups(cost) << endl;
}