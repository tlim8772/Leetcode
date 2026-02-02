#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// binary search k.

ll helper(const vector<int>& nums, int k) {
    ll sum = 0;
    for (int x : nums) {
        sum += (x / k) + (x % k != 0);
    }
    return sum;
}

class Solution {
public:
    int minimumK(vector<int>& nums) {
        int s = 1, e = 100000;
        while (s < e) {
            int m = (s + e) >> 1;
            ll sum = helper(nums, m);
            if (sum <= (ll) m * m) {
                e = m;
            } else {
                s = m + 1;
            }
        }
        return s;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1, 1};
    cout << sol.minimumK(nums);
}