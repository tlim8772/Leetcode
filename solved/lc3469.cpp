#include <bits/stdc++.h>
using namespace std;

// dp(x, i) means minimum score to remove all elems in arr[i, end] with x as the 1st elem (leftover from prev removes)
class Solution {
public:
    unordered_map<int, unordered_map<int, int>> dp;

    bool contains(int x, int i) {
        return dp.contains(x) && dp[x].contains(i);
    }

    int helper(int x, int i, vector<int>& nums) {
        if (nums.size() - i < 2) {
            return (nums.size() - i == 0) ? x : max(x, *max_element(nums.begin() + i, nums.end()));
        } else if (contains(x, i)) {
            return dp[x][i];
        } else {
            // take x and 1st elem
            int opt1 = max(x, nums[i]) + helper(nums[i + 1], i + 2, nums);

            // take x and 2nd elem
            int opt2 = max(x, nums[i + 1]) + helper(nums[i], i + 2, nums);

            // take 1st and 2nd elem
            int opt3 = max(nums[i], nums[i + 1]) + helper(x, i + 2, nums);

            int best = min(opt1, min(opt2, opt3));
            dp[x][i] = best;

            return best;
        }
    }

    int minCost(vector<int>& nums) {
        if (nums.size() < 3) {
            return *max_element(nums.begin(), nums.end());
        }

        int x1 = max(nums[0], nums[1]);
        int r1 = x1 + helper(nums[2], 3, nums);

        int x2 = max(nums[1], nums[2]);
        int r2 = x2 + helper(nums[0], 3, nums);

        int x3 = max(nums[0], nums[2]);
        int r3 = x3 + helper(nums[1], 3, nums);

        return min(r1, min(r2, r3));
    }

};

int main() {
    vector<int> nums = {12,15,1,15,18};
    Solution sol;
    cout << sol.minCost(nums) << endl;
}