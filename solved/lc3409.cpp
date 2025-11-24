#include <bits/stdc++.h>
using namespace std;

// let dp(i, diff) means that we are at index i, and we want to form the longest non-increasing consectutive diff
// that uses arr[i] !!!
// subsequence, where all consecutive diff are <= diff
// at dp(i, diff), either we get the next elem such that |arr[next] - arr[i]| == diff, or we get dp(i, diff - 1), 
// i.e the optimal solution is to consider newdiff that is < diff
// we have 1 value only for arr[next], and we take the leftmost one that is still to the right of i
// this is because if arr[j] == arr[k], then dp(j, diff) >= dp(k, diff), subsequence for the latter is a valid subsequence for the
// former
// use a hashmap to store all indexes for each value, then binary search
// TC O(300 * 1e4 * log(1e4))

class Solution {
public:
    int len;
    vector<vector<int>> dp;
    unordered_map<int, vector<int>> indexes;

    // returns the smallest elem > key, or -1 if don't have
    int binarySearch(vector<int>& arr, int key) {
        int s = 0, e = arr.size() - 1;
        while (s < e) {
            int m = (s + e) >> 1;
            if (arr[m] > key) e = m;
            else s = m + 1;
        }
        return (arr[s] > key) ? arr[s] : -1;
    }

    int process(vector<int>& nums) {
        len = nums.size();
        dp = vector(len, vector(300, -1));
        int best = 2;

        for (int i = 0; i < nums.size(); i ++) {
            indexes[nums[i]].push_back(i);
        }

        // do for last idx 
        for (int diff = 0; diff < 300; diff++) {
            dp[len - 1][diff] = 1;
        }

        for (int i = len - 2; i >= 0; i --) {
            int curr = nums[i];

            // do diff == 0 first
            int next = binarySearch(indexes[curr], i);
            dp[i][0] = (next == -1) ? 1 : 1 + dp[next][0];

            for (int diff = 1; diff < 300; diff ++) {
                int up = curr + diff;
                int upIdx = (indexes.count(up) == 0) ? -1 : binarySearch(indexes[up], i);
                int upRes = (upIdx == -1) ? 1 : 1 + dp[upIdx][diff];

                int down = curr - diff;
                int downIdx = (indexes.count(down) == 0) ? -1 : binarySearch(indexes[down], i);
                int downRes = (downIdx == -1) ? 1 : 1 + dp[downIdx][diff];

                int opt2 = dp[i][diff - 1];

                dp[i][diff] = max({upRes, downRes, opt2});
                
                best = max(best, dp[i][diff]);
            }
        }

       
        return best;
    }

    int longestSubsequence(vector<int>& nums) {
        return process(nums);
    }


};

int main() {
    vector<int> nums = {68,83,52,70,52};
    Solution sol;
    cout << sol.longestSubsequence(nums) << endl;

}