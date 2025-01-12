#include <bits/stdc++.h>
using namespace std;

// trick is to work from the back
// consider index i to be the last elem to be burst
// then the 2 subarrays [l, i -1] and [i + 1, r] are independent
// dp(l,r) is the best score we can get, without changing arr[l] and arr[r] at all

class Solution {
public:
    vector<vector<int>> dp;
    vector<int> arr;

    int helper(int l, int r) {
        if (l > r) {
            return 0;
        } else if (dp[l][r] != -1) {
            return dp[l][r];
        } else if (l == r) {
            int a = (l - 1 < 0) ? 1 : arr[l - 1];
            int b = (r + 1 >= arr.size()) ? 1 : arr[r + 1];
            return a * arr[l] * b;
        } else {
            int best = -1;
            for (int i = l; i <= r; i ++) {
                int a = (l - 1 < 0) ? 1 : arr[l - 1];
                int b = (r + 1 >= arr.size()) ? 1 : arr[r + 1];
                int m = arr[i];
                
                int left = helper(l, i - 1);
                int right = helper(i + 1, r);
                
                // last elem multiple by l - 1 and r - 1 (if they exist)
                int ans = left + right + a * m * b; 
                
                best = max(best, ans);
            }
            dp[l][r] = best;
            return best;

        }
    }
    int maxCoins(vector<int>& nums) {
        dp = vector(nums.size(), vector(nums.size(), -1));
        arr = nums;
        return helper(0, nums.size() - 1);
    }
};

int main() { return 0; }