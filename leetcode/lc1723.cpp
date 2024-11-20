#include <bits/stdc++.h>
using namespace std;

// select a subset to assign to the next person, then recurse
// only store dp(currPerson, bitmask) = best laod balancing on currPerson + 1 people, with bitmask tasks left
// bitmask[i] = 1 if tasks[i] is still available

class Solution {
public:
    vector<vector<int>> dp;

    int helper(int currPerson, int bitmask, int idx, int sum, vector<int>& tasks) {
        if (currPerson == -1) return (bitmask == 0) ? 0 : 100000000;
        if (idx == tasks.size()) return max(sum, helper(currPerson - 1, bitmask, 0, 0, tasks));
        
        // starting allocating to next person, and we already got the ans
        if (idx == 0 && dp[currPerson][bitmask] != -1) return dp[currPerson][bitmask];

        int ans = 1000000000;
        int take = 1000000000;
        int notake = 1000000000;
        
        if ((bitmask >> idx) & 1) {
            take = helper(currPerson, bitmask - (1 << idx), idx + 1, sum + tasks[idx], tasks);
        }

        notake = helper(currPerson, bitmask, idx + 1, sum, tasks);
        ans = min(take, notake);

        if (idx == 0) dp[currPerson][bitmask] = ans;
        
        return ans;
        
    }

    int minimumTimeRequired(vector<int>& jobs, int k) {
        dp = vector(k, vector(1 << jobs.size(), -1));
        return helper(k - 1, (1 << jobs.size()) - 1, 0, 0, jobs);
    }
};

int main() {
    Solution sol;
    vector<int> jobs = {1,2,4,7,8};
    int k = 2;
    cout << sol.minimumTimeRequired(jobs, 3) << endl;
}