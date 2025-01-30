#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int MOD = 1e9 + 7;

// the root of the current tree is arr[0], let arr1 be all elems < root and arr2 be all elems > root
// we count the ways for arr1 and arr2, lastly to merge, we have n - 1 elems, we can interleave elems in arr1 and arr2
// the order of elems in arr1 and arr2 must be kept, but can we freely interleave elems from arr1 and arr2

struct Combination {
    int n;
    vector<vector<int>> dp;

    Combination() {}

    Combination(int n): n(n), dp(n + 1, vector<int>(n + 1, 0)) {
        process();
    }

    void process() {
       dp[0][0] = 1;

        for (int r = 1; r <= n; r ++) {
            for (int c = 0; c <= r; c ++) {
                int take1 = (c - 1 == -1) ? 0 : dp[r - 1][c - 1];
                int notake = (c > r - 1) ? 0 : dp[r - 1][c];
                dp[r][c] = (take1 + notake) % MOD;
            }
        }
    }

    int getRes(int r, int c) {
        return dp[r][c];
    }
};

class Solution {
public:
    Combination comb;
    int helper(vector<int>& nums) {
        if (nums.size() <= 1) return 1;

        vector<int> l, r;
        for (int i = 1; i < nums.size(); i ++) {
            if (nums[i] < nums[0]) l.push_back(nums[i]);
            else r.push_back(nums[i]);
        }

        int lres = helper(l), rres = helper(r);
        int interleave = comb.getRes(nums.size() - 1, l.size());

        ll temp = (ll) lres * rres;
        temp %= MOD;
        temp *= (ll) interleave;
        temp %= MOD;

        return (int) temp;
    }
    int numOfWays(vector<int>& nums) {
       comb = Combination(nums.size());
       return helper(nums) - 1; // -1 because we ignore the initial permutation


    }
};

int main() {
    vector<int> arr = {1,2,3};
    Solution sol;
    cout << sol.numOfWays(arr);
}
