#include <bits/stdc++.h>
using namespace std;
using Pair = tuple<bool, int>;

// 0 means go up, 1 means go down.
// is just prefix-suffix then combining the solution.

class Solution {
public:
    int longestAlternating(vector<int>& nums) {
        vector<int> prefix_up(nums.size(), 1), prefix_down(nums.size(), 1);
        vector<int> suffix_up(nums.size(), 1), suffix_down(nums.size(), 1);

        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1]) continue;
            if (nums[i] > nums[i - 1]) {
                prefix_down[i] = 1 + prefix_up[i - 1];
            } else {
                prefix_up[i] = 1 + prefix_down[i - 1];
            }
        }

        for (int i = nums.size() - 2; i > -1; i--) {
            if (nums[i] == nums[i + 1]) continue;
            if (nums[i] > nums[i + 1]) {
                suffix_down[i] = 1 + suffix_up[i + 1];
            } else {
                suffix_up[i] = 1 + suffix_down[i + 1];
            }
        }
        
        int best = max({
            *max_element(prefix_up.begin(), prefix_up.end()),
            *max_element(prefix_down.begin(), prefix_down.end()),
            *max_element(suffix_up.begin(), suffix_up.end()),
            *max_element(suffix_down.begin(), suffix_down.end())
        });

        for (int i = 1; i < nums.size() - 1; i++) {
            if (nums[i - 1] == nums[i + 1]) continue;
            int ans;
            if (nums[i - 1] < nums[i + 1]) {
                ans = prefix_up[i - 1] + suffix_down[i + 1];
            } else {
                ans = prefix_down[i - 1] + suffix_up[i + 1];
            }
            best = max(ans, best);
        }
        return best;
    }
};