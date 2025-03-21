#include <bits/stdc++.h>
using namespace std;

// starting at index i, it only matters if we swap or don't swap the prev index

class Solution {
public:
    int LEN;
    vector<int> dp;

    int coor(int swapPrev, int i) {
        return swapPrev * LEN + i;
    }

    int helper(int swapPrev, int i, vector<int>& nums1, vector<int>& nums2) {
        int pos = coor(swapPrev, i);
        if (i == LEN) {
            return 0;
        } else if (dp[pos] != -1) {
            return dp[pos];
        } else if (i == 0) {
            int noswap = helper(false, 1, nums1, nums2);
            int swap = 1 + helper(true, 1, nums1, nums2);
            
            int ans = min(swap, noswap);
            dp[pos] = ans;
            return ans;
        } else {
            int prevA = (swapPrev) ? nums2[i - 1] : nums1[i - 1]; // nums1
            int prevB = (swapPrev) ? nums1[i - 1] : nums2[i - 1]; // nums2

            int noswap = (nums1[i] > prevA && nums2[i] > prevB) ? helper(false, i + 1, nums1, nums2) : 999999;
            int swap = (nums1[i] > prevB && nums2[i] > prevA) ? 1 + helper(true, i + 1, nums1, nums2) : 999999;
            
            int ans = min(noswap, swap);
            dp[pos] = ans;
            return ans;
        }
    }

    int minSwap(vector<int>& nums1, vector<int>& nums2) {
        LEN = nums1.size();
        dp = vector(2 * LEN, -1);
        return helper(false, 0, nums1, nums2);
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {1,3,5,4};
    vector<int> nums2 = {1,2,3,7};

    cout << sol.minSwap(nums1, nums2) << endl;
}