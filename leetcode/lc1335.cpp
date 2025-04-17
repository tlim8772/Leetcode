#include <bits/stdc++.h>
using namespace std;

// O(nnd) algo
// dp(d, i) means best result for prefix [0..i] with d days to finish

class Solution {
public:
    vector<vector<int>> dp;

    int minDifficulty(vector<int>& jobs, int days) {
        dp = vector(days, vector<int>(jobs.size(), 0));

        // for d = 0;
        int ma = 0;
        for (int i = 0; i < jobs.size(); i ++) {
            ma = max(ma, jobs[i]);
            dp[0][i] = ma;
        }

        for (int d = 1; d < days; d ++) {
            for (int i = 0; i < jobs.size(); i ++) {
                if (i < d) {
                    dp[d][i] = 500000;
                } else {
                    int ma = 0;
                    int best = 500000;
                    for (int j = i; j >= 1; j --) {
                        ma = max(ma, jobs[j]);
                        int res = min(best, ma + dp[d - 1][j - 1]);
                        best = min(res, best);
                    }
                    
                    dp[d][i] = best;
                }
            }
        }

        int ans = dp[days - 1][jobs.size() - 1];
        if (ans > 300000) return -1;
        else return ans;
    }
};

int main() {
    Solution sol;

    vector<int> arr = {9,9,9};
    int days = 4;
    cout << sol.minDifficulty(arr, days);
}