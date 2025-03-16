#include <bits/stdc++.h>
using namespace std;

// basically for each num x, x in [0, 1000] find the earliest idx where we can make it 0
// use dp, must repeat for each elem in arr, as their position is different

class Solution {
public:
    int LEN; // length of queries
    vector<int> dp;

    inline int coor(int curr, int idx) {
        return curr * LEN + idx;
    }

    

    // curr != 0
    int helper(int pos, int curr, int idx, vector<vector<int>>& queries) {
        int p = coor(curr, idx);

        if (idx == queries.size()) {
            return 999999;
        } else if (dp[p] != -1) {
            return dp[p];
        } else if (pos < queries[idx][0] || pos > queries[idx][1] || curr < queries[idx][2]) {
            // if out of range or curr - val < 0
            int ans = helper(pos, curr, idx + 1, queries);
            
            dp[p] = ans;
            return ans;
        } else {
            int notake = helper(pos, curr, idx + 1, queries);
            int take = (curr == queries[idx][2]) ? idx : helper(pos, curr - queries[idx][2], idx + 1, queries);
            int ans = min(take, notake);

            dp[p] = ans;
            return ans;
            
        }
    }

    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        LEN = queries.size();
        dp = vector(1001 * LEN, -1);

      

        int worst = 0;
        for (int i = 0; i < nums.size(); i ++) {
            for (int &x : dp) x = -1; // reset dp 

            if (nums[i] == 0) continue;

            int zeroIdx = helper(i, nums[i], 0, queries);
            cout << zeroIdx << endl;
            worst = max(worst, zeroIdx + 1);
        }
        return (worst >= 999999) ? -1 : worst;
    }
};

int main() {
    Solution sol;

    vector<int> nums = {2};
    vector<vector<int>> queries = {{0,2,1},{0,2,1},{1,1,3}};

    int ans = sol.minZeroArray(nums, queries);
    //cout << ans << endl;
}