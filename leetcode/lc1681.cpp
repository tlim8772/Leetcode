#include <bits/stdc++.h>
using namespace std;

// bitmask dp
// if bm[i] == 1 means taken already
// let K = #elems in each set
// we only store results for dp(bm) where bm has a multiple of K elems
// for the intermediary state, we just backtrack

// to prune, we store num elems to choose left, and nums elem left
// end when nums elems left < nums elems to choose left

class Solution {
public:
    int K;
    vector<int> dp;

    // count number of 0 bits in a bitmask of length len
    int elemsLeft(int bm, int len) {
        int cnt = 0;
        for (int i = 0; i < len; i++) {
            if (((bm >> i) & 1) == 0) cnt++;
        }
        return cnt;
    }

    int helper2(vector<int>& nums, int bm) {
        if (dp[bm] != -1) {
            return dp[bm];
        } 

        if (bm == (1 << nums.size()) - 1) {
            dp[bm] = 0;
        } else {
            // choose the smallest unchosen index as the starting element
            int i = 0;
            for (; i < nums.size(); i++) {
                if (((bm >> i) & 1) == 1) continue;
                break;
            }
            
            int newBm = bm | (1 << i);
            int cnt = elemsLeft(newBm, nums.size());
           
            int ans = helper1(nums, newBm, i + 1, nums[i], nums[i], K - 1, cnt);
            dp[bm] = ans;
        }
        return dp[bm];
    }

    int helper1(vector<int>& nums, int bm, int idx, int start, int prev, int left, int elemsLeft) {
        if (left == 0) {
            int ans = prev - start + helper2(nums, bm);
            return ans;
        } else if (idx == nums.size()) {
            // did not choose enough elems
            return 9999; 
        } else if (elemsLeft < left) {
            // not enough elems to choose from
            return 9999;
        }

        if (((bm >> idx) & 1) == 1) {
            // nums[idx] has been taken
            return helper1(nums, bm, idx + 1, start, prev, left, elemsLeft);
        } else if (nums[idx] == prev) {
            // equal elem so cannot take
            return helper1(nums, bm, idx + 1, start, prev, left, elemsLeft - 1);
        } else {
            int take = helper1(nums, bm | (1 << idx), idx + 1, start, nums[idx], left - 1, elemsLeft - 1);
            int notake = helper1(nums, bm, idx + 1, start, prev, left, elemsLeft - 1);
            return min(take, notake);
        }
    }
   
    
    int minimumIncompatibility(vector<int>& nums, int k) {
        // edge case when k == nums.size()
        if (k == nums.size()) return 0;

        K = nums.size() / k;
        dp = vector(1 << nums.size(), -1);

        sort(nums.begin(), nums.end());
        
        int ans = helper2(nums, 0);
        return (ans >= 9999) ? -1 : ans;
    }
};

int main() {
   Solution sol;

   vector<int> nums = {6,3,8,1,3,1,2,2};
   int k = 4;

   cout << sol.minimumIncompatibility(nums, k) << endl;

}