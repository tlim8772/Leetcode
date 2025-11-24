#include <bits/stdc++.h>
using namespace std;

// take, don't take dp
// state is (idx, sum of time where paid painter takes). We want sum of time >= number of jobs taken by free painter
// while minimising cost of jobs taken by paid painter
// dp(idx, sum) returns the cost needed to clear jobs from index idx onwards
// key insight, sum of time <= len of jobs, any more, we don't need to process anymore

class Solution {
public:
    int n;
    vector<int> jobCost;
    vector<int> jobTime;
    vector<vector<int>> dp;

    int helper(int idx, int time) {
        int actual = time - n;
        if (idx == (int) jobTime.size()) {
            return (actual >= 0) ? 0 : 1e9;
        } else if (actual >= (int) jobTime.size() - idx) { 
            // we have enough 'time' to cover all remaining jobs by free painter
            return 0;
        } else if (dp[idx][time] != -1) {
            return dp[idx][time];
        }

        int take = jobCost[idx] + helper(idx + 1, time + jobTime[idx]);
        if (idx == 0) cout << take << endl;
        int notake = helper(idx + 1, time - 1);
        if (idx == 0) cout << notake << endl;
    
        int best = min(take, notake);
        dp[idx][time] = best;
        return best;
    }

    int paintWalls(vector<int>& cost, vector<int>& time) {
        n = cost.size();
        jobCost = cost;
        jobTime = time;
        dp = vector(n, vector(2 * n + 1, -1));
        
        return helper(0, n);
    }


};

int main() {
    Solution sol;
    vector<int> cost = {1,2,3,2};
    vector<int> time = {1,2,3,2};
    
    
    int ans = sol.paintWalls(cost, time);
    
    for (vector<int>& arr : sol.dp) {
        for (int x : arr) {
            cout << x << " ";
        }
        cout << endl;
    }
}