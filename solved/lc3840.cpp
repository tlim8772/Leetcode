#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// traverse the array from left to right.
// group houses of the same color together, so we have several contigous ranges.
// in each subarray, robber cannot rob consective houses, so we do dp in each subarray.

// actually we can just do dp.
// dp(i, robbed_prev_house) = max money we can get from arr[i:], given that we robbed prev house or not.



struct WrongHash {
    size_t operator()(int x) const {
        return x;
    }
};

class Solution {
public:
    struct PairHash {
        size_t operator()(const pair<int, int>& p) const {
            return (p.first << 1) + p.second;
        }
    };

    unordered_map<pair<int, bool>, ll, PairHash> store;

    ll dp(int i, bool prev, const vector<int>& nums, const vector<int>& colors) {
        if (i == nums.size()) return 0;
        if (store.contains({i, prev})) return store[{i, prev}];

        if (!prev) {
            ll rob = nums[i] + dp(i + 1, true, nums, colors);
            ll no_rob = dp(i + 1, false, nums, colors);
            return store[{i, prev}] = max(rob, no_rob);
        } else {
            ll rob = (colors[i - 1] == colors[i]) ? 0 : nums[i] + dp(i + 1, true, nums, colors);
            ll no_rob = dp(i + 1, false, nums, colors);
            return store[{i, prev}] = max(rob, no_rob);
        }
    }

    long long rob(vector<int>& nums, vector<int>& colors) {
        return dp(0, false, nums, colors);
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1,4,3,5};
    vector<int> colors = {1,1,2,2};
    ll ans = sol.rob(nums, colors);
    cout << ans << endl;
}


    