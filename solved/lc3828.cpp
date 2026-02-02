#include <bits/stdc++.h>
using namespace std;

// gut feeling is max(nums[0], nums.back()).
// but don't know how to proof.

class Solution {
public:
    int finalElement(vector<int>& nums) {
        return max(nums[0], nums.back());
    }
};