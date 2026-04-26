#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class Solution {
public:
    int compareBitonicSums(vector<int>& nums) {
        int idx;
        for (idx = 1; idx < nums.size() - 1; idx++) {
            if (nums[idx - 1] < nums[idx] && nums[idx] > nums[idx + 1]) break;
        }

        ll lsum = accumulate(nums.begin(), nums.begin() + idx + 1, 0LL, [] (ll a, ll b) { return a + b; });
        ll rsum = accumulate(nums.begin() + idx, nums.end(), 0LL, [] (ll a, ll b) { return a + b; });

        if (lsum > rsum) return 0;
        if (rsum > lsum) return 1;
        return -1;
    }
};