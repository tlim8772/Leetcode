#include <bits/stdc++.h>
using namespace std;

// sort the array in increasing order
// let dp(i, k): is it possible to select subsequence from [0..i] s.t the sum is k ?
// then for each x in 1..n
// find the cutoff index i + 1
// for each multple of x eg. x, 2x, 3x ... check dp(i, k - x/2x/3x ...)
// sum of empty subsequence is 0 

// time complexity is
// dp: O(n^2)
// checking for each x: O(n^2)

class Solution {
public:
    int N, K;
    vector<int> store;

    inline int coor(int i, int k) {
        return i * K + k;
    }

    void processDp(const vector<int>& nums) {
        for (int k = 0; k < K; k++) {
            store[coor(0, k)] = (k == 0 || nums[0] == k);
        }

        for (int i = 1; i < N; i++) {
            for (int k = 0; k < K; k++) {
                int notake = store[coor(i - 1, k)];
                int take = (k - nums[i] < 0) ? 0 : store[coor(i - 1, k - nums[i])];
                store[coor(i, k)] = notake || take;
            }
        }
    }

    vector<bool> subsequenceSumAfterCapping(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());

        N = nums.size(), K = k + 1;
        store = vector(N * K, -1);
        processDp(nums);

        vector<bool> out(nums.size(), false);
        int ptr = 0;
        for (int x = 1; x <= nums.size(); x++) {
            while (ptr < nums.size() && nums[ptr] <= x) ptr++;

            int maxXMultiple = nums.size() - ptr;
            int lim = min(maxXMultiple, k / x);
            bool res = false;
            if (ptr == 0) {
                res = k % x == 0 && maxXMultiple >= k / x;
            } else {
                for (int m = 0; m <= lim; m++) {
                    res = res || store[coor(ptr - 1, k - m * x)];
                }
            }

            out[x - 1] = res;
        }

        return out;
    }
};

int main() {
    Solution sol;

    vector<int> nums = {1,2,3,4,5};
    int k = 5;
    vector<bool> out = sol.subsequenceSumAfterCapping(nums, k);

    for (bool b : out) cout << b << " ";
    cout << endl;

}