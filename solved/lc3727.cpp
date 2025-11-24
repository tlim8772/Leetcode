#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        for_each(nums.begin(), nums.end(), [] (int& x) { x = abs(x); });
        sort(nums.begin(), nums.end(), [](int a, int b) { return a > b; });
        
        ll res = 0;
        for (int i = 0; i < (nums.size() + 1) >> 1; i++) {
            res += nums[i] * nums[i];
        }
        for (int i = (nums.size() + 1) >> 1; i < nums.size(); i++) {
            res -= nums[i] * nums[i];
        }
        
        return res;
    }
};