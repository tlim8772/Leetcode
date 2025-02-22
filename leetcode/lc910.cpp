#include <bits/stdc++.h>
using namespace std;

// sort the array in increasing order
// let i be the leftmost elem switch to elem - k, and j be the rightmost elem switch to elem + k
// the max is max(j + k, last elem - k), min is min(i - k, 1st elem + k)
// this gives a O(n^2) algo


// to get O(n) use 2 ptr
// notice that we fix j, the best possible i is actually j - 1
// note that if i < j, min(nums[0] + k, nums[i] - k) <= max(nums[j] + k, last elem - k)
// to get the closest min, only need to consider i = j - 1, moving to the left will only decrease the min
// however, there is a case where the leftmost minus > j, only case is j + 1, so take care accoridingly

// note that we never add k to the last (largest) elem or minus k to the first (smallest) elem

class Solution {
public:
    int smallestRangeII(vector<int>& nums, int k) {
        if (nums.size() == 1) return 0;

        sort(nums.begin(), nums.end());

        int best = nums.back() - nums.front();
        // cout << best << endl;

        

        // for each j, no need to consider if nums[0] - k, this can never 
        // make the result better
        for (int i = nums.size() - 1; i >= 0; i --) {
            if (i == nums.size() - 1) {
                int currMax = nums[i] + k;
                int currMin = min(nums[0] + k, nums[i - 1] - k);
                best = min(best, currMax - currMin);
            } else if (i == 0) {
                int currMax = max(nums[0] + k, nums.back() - k);
                int currMin = min(nums[0] + k, nums[1] - k);

                // cout << currMax - currMin << endl;
                best = min(best, currMax - currMin);
            } else {
                // case 1, leftmost minus is < i
                int currMax = max(nums[i] + k, nums.back() - k);
                int currMin = min(nums[i - 1] - k, nums[0] + k);
                best = min(best, currMax - currMin);

                // case 2, leftmost minus > i, then it can only be i + 1
                int currMin2 = min(nums[0] + k, nums[i + 1] - k);
                best = min(best, currMax - currMin2);

            }
            
        }

        // now consider if the j == 0
        

        return best;
    }
};

int main() {
    vector<int> arr = {0,10};
    int k = 2;
    Solution sol;
    cout << sol.smallestRangeII(arr, k) << endl;
}