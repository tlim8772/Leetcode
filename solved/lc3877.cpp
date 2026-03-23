#include <bits/stdc++.h>
using namespace std;

// arr.size() = 40, so we split into 2 arr of 20 elems each.
// try all subsets in each of the 2 array, then combine the 2 results together.
// when trying out all possibilities, take the max elems for each xor result that is obtainable.
// basically is Meet in the Middle technique.

void helper(int p, int xr, int num_taken, const vector<int>& arr, unordered_map<int, int>& store) {
    if (p == arr.size()) {
        store[xr] = max(store[xr], num_taken);
        return;
    }

    helper(p + 1, xr, num_taken, arr, store);
    helper(p + 1, xr ^ arr[p], num_taken + 1, arr, store);
}

class Solution {
public:
    int minRemovals(vector<int>& nums, int target) {
        if (nums.size() == 1) {
            return (nums[0] == target) ? 0 : (target == 0) ? 1 : -1;
        }

        int mid = nums.size() / 2;
        vector<int> left(nums.begin(), nums.begin() + mid), right(nums.begin() + mid, nums.end());
        unordered_map<int, int> left_store, right_store;

        helper(0, 0, 0, left, left_store);
        helper(0, 0, 0, right, right_store);

        int best = -1;
        for (auto [xr, num_taken] : left_store) {
            int next = target ^ xr;
            if (!right_store.contains(next)) continue;
            best = max(best, num_taken + right_store[next]);
        }

        return (best == -1) ? best : nums.size() - best;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {2, 4};
    int target = 1;
    int ans = sol.minRemovals(nums, target);
    cout << ans << endl;
}