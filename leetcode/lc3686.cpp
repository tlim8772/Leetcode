#include <bits/stdc++.h>
using namespace std;

// simple dp
// let dp(p, l, n) means starting at index n, with the previous consecutive l elements of parity p taken

class Solution {
public:
    const int MOD = 1e9 + 7;
    int P = 2, L = 3, N;
    vector<int> store;

    inline int coor(int p, int l, int n) {
        return p * L * N + l * N + n;
    }

    int dp(int p, int l, int n, const vector<int>& nums) {
        if (n == N) return 1;

        int pos = coor(p, l, n);
        if (store[pos] != -1) return store[pos];

        int currP = nums[n] % 2;
        int take = 0, notake = 0;
        if (currP != p || l < 2) {
            if (currP == p) {
                take = dp(p, l + 1, n + 1, nums);
            } else {
                take = dp(currP, 1, n + 1, nums);
            }
        }

        notake = dp(p, l, n + 1, nums);
        return store[pos] = (take + notake) % MOD;

    }


    int countStableSubsequences(vector<int>& nums) {
        N = nums.size();
        store = vector(P * L * N, -1);

        int sum = 0;
        // count stable subsequence with 1st element at index i
        for (int i = 0; i < nums.size(); i++) {
            int ans = dp(nums[i] % 2, 1, i + 1, nums);
            //cout << ans << endl;
            sum = (sum + ans) % MOD;
        }

        return sum;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {2,3,4,2};
    cout << sol.countStableSubsequences(nums) << endl;
}