#include <bits/stdc++.h>
using namespace std;

// algo
// 1. starting from the right, find the split index, i.e 1st index s.t nums[i] < nums[i + 1].
// then in nums[i + 1:], find the smallest elem > nums[i], swap with nums[i].
// then sort nums[i + 1:]

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int split_idx = nums.size() - 2;
        for (; split_idx >= 0; split_idx--) {
            if (nums[split_idx] < nums[split_idx + 1]) break;
        }
        //cout << split_idx << endl;

        if (split_idx == -1) {
            sort(nums.begin(), nums.end());
            return;
        }

        for (int i = nums.size() - 1; i > split_idx; i--) {
            if (nums[i] > nums[split_idx]) {
                swap(nums[split_idx], nums[i]);
                break;
            }
        }

        sort(nums.begin() + split_idx + 1, nums.end());
        return;
    }
};

int main() {
    Solution sol;

    vector<int> nums = {1, 3, 2};
    sol.nextPermutation(nums);

    for (int x : nums) cout << x << " ";
    cout << endl;
}