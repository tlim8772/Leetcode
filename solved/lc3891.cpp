#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// dp problem.
// suppose have 6 elems x _ _ _ _ x
// we can choose idx (1, 4), (2, 4).
// if len is even, we can skip once.
// i.e 1, 4, 6 ... instead of 1, 3, 5 ...
// if len is odd, we cannot skip at all we must take 1, 3, 5 ...

ll INVALID = (ll) 1e15;
ll store[100000][2];

void init(int len) {
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < 2; j++) {
            store[i][j] = -1;
        }
    }
}

inline int to_add(int x, int l, int r) {
    return max(0, max(l, r) + 1 - x);
}

class Solution {
public:

    ll dp(int i, int skip, const vector<int>& nums) {
        if (i >= nums.size() - 1) return 0;

        ll& ans = store[i][skip];

        if (ans != -1) return ans;

        // if we have skipped an element, must take this index.
        if (skip == 1) {
            return ans = to_add(nums[i], nums[i - 1], nums[i + 1]) + dp(i + 2, skip, nums);
        } 

        ll take = to_add(nums[i], nums[i - 1], nums[i + 1]) + dp(i + 2, skip, nums);
        ll notake = dp(i + 1, 1, nums);
        return ans = min(take, notake);
    }

    long long minIncrease(vector<int>& nums) {
        init(nums.size());
        int skip = (nums.size() - 2) % 2;
        ll ans = dp(1, skip, nums);
        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {12,23,13,17,21,3};

    ll ans = sol.minIncrease(nums);
    println("Ans: {}", ans);
}