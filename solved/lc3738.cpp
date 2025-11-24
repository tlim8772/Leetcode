#include <bits/stdc++.h>
using namespace std;

/*
prefixes[i] = longest non decreasing subarray ending at index i.
suffixes[i] = longest non decreasing subarray starting at index i.
for each index i, there are many cases.
case 1: prefixes[i]
case 2: suffixes[i]

now we change nums[i]
case 3: 1 + prefixes[i - 1]
case 4: 1 + suffixes[i + 1]
case 5: 1 + prefixes[i - 1] + suffixes[i + 1]
*/

class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        vector<int> prefixes(nums.size(), 0), suffixes(nums.size(), 0);
        
        for (int i = 0; i < nums.size(); i++) {
            prefixes[i] = (i > 0 && nums[i] >= nums[i - 1]) ? 1 + prefixes[i - 1] : 1;
        }
        
        for (int i = nums.size() - 1; i > -1; i--) {
            suffixes[i] = (i < nums.size() - 1 && nums[i] <= nums[i + 1]) ? 1 + suffixes[i + 1] : 1;
        }

        int best = 0;
        for (int i = 0; i < nums.size(); i++) {
            int ans = max<int>({
                prefixes[i],
                suffixes[i],
                (i > 0) ? 1 + prefixes[i - 1] : 0,
                (i < nums.size() - 1) ? 1 + suffixes[i + 1] : 0,
                (i > 0 && i < nums.size() - 1 && nums[i - 1] <= nums[i + 1]) ? 1 + prefixes[i - 1] + suffixes[i + 1] : 0
            });

            best = max(best, ans);
        }

        return best;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1,2,3,1,2};
    cout << sol.longestSubarray(nums);
}