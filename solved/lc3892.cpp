#include <bits/stdc++.h>
using namespace std;

// just dp, but since it is circular, we need to handle the case where arr[0] is a peak
// and when it is definitely not a peak.
// max number of peaks is floor(n / 2).
// once we have made k peaks, we can stop already, there is no benefit to creating more peaks.

int MAX = 1e9;
int store[5000][2501];

void init(int n, int k) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k + 1; j++) {
            store[i][j] = -1;
        }
    }
}

int to_add(int to_peak, int l, int r) {
    return max(0, max(l, r) + 1 - to_peak);
}

class Solution {
public:

    // in dp1, arr[0] must be made a peak.
    int dp1(int i, int k, const vector<int>& nums) {
        // arr[n - 1] cannot be a peak, as arr[0] is a peak already.
        if (i >= nums.size() - 1) {
            if (k == 0) {
                return 0;
            } else {
                return MAX;
            }
        } 

        if (k == 0) return 0;

        if (store[i][k] != -1) return store[i][k];

        int& ans = store[i][k];
        if (i == 0) {
            return ans = to_add(nums[0], nums.back(), nums[1]) + dp1(i + 2, k - 1, nums);
        } else {
            int take = to_add(nums[i], nums[i - 1], nums[i + 1]) + dp1(i + 2, k - 1, nums);
            int notake = dp1(i + 1, k, nums);
            return ans = min(take, notake);
        }
    }

    // in dp2, arr[0] cannot be a peak
    int dp2(int i, int k, const vector<int>& nums) {
        if (i >= nums.size()) {
            if (k == 0) {
                return 0;
            } else {
                return MAX;
            }
        }

        if (k == 0) return 0;

        if (store[i][k] != -1) return store[i][k];

        int& ans = store[i][k];
        int take = to_add(nums[i], nums[i - 1], nums[(i + 1) % nums.size()]) + dp2(i + 2, k - 1, nums);
        int notake = dp2(i + 1, k, nums);
        return ans = min(take, notake);
    }


    int minOperations(vector<int>& nums, int k) {
        if (k > nums.size() / 2) return -1;

        init(nums.size(), k);
        int ans1 = dp1(0, k, nums);
        init(nums.size(), k);
        int ans2 = dp2(1, k, nums);

        int ans = min(ans1, ans2);
        return (ans >= MAX) ? -1 : ans;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {4, 5, 3, 6};
    int k = 2;

    int ans = sol.minOperations(nums, 1);
    println("Ans: {}", ans);
}