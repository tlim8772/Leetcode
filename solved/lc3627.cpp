#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// sort nums
// greedy. in the current array, take the biggest 2 nums and the smallest num

class Solution {
public:
    long long maximumMedianSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int e = nums.size() - 1;
        int cnt = 0;
        ll sum = 0;

        while (cnt < nums.size() / 3) {
            sum += nums[e - 1];
            e -= 2;
            cnt++;
        }

        return sum;

    }
};