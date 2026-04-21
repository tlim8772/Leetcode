#include <bits/stdc++.h>
using namespace std;

// simple prefix max and suffix mean.

class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k) {
        vector<int> prefix_max(nums.size(), 0), suffix_min(nums.size(), 0);

        for (int i = 0; i < nums.size(); i++) {
            prefix_max[i] = max(nums[i], (i == 0) ? -1 : prefix_max[i - 1]);
        }

        for (int i = nums.size() - 1; i >= 0; i--) {
            suffix_min[i] = min(nums[i], (i == nums.size() - 1) ? (int) 2e9 : suffix_min[i + 1]);
        }

        for (int i = 0; i < nums.size(); i++) {
            if (prefix_max[i] - suffix_min[i] <= k) return i;
        }
        
        return -1;
    }
};