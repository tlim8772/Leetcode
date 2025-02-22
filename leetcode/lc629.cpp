#include <vector>
#include <iostream>
using namespace std;

// dp solution
// let dp(n, k) be the number of permuations for nums [0, 1, 2, ... n - 1] s.t the permuation have exactly k inversions
// now notice that for any permutations, the permutation from index 0 to n - 2 can have k, k - 1, k - 2 ... k - min(k, n) inversions
// lets say have k inversions, notice only number you can place is n - 1, if you place n - 2, then n - 1 will appear to the left, 
// increasing inversion count by 1
// now notice for the case where subarray[0, n - 2], we only need to consider relative numbers, i.e numbers
// from 0 to n - 2
// even when subarray[0 ... n - 2] has k - 1 inversion, so we have to place num n - 2 at the last index 
// for every permuations of 0 to n - 2 that has k - 1 inversion, simply take numbers 0, 1, 2 ... n - 3, n - 1
// and place them in the permutation in the order of their relative size, i,e where n - 2 is placed will be where n - 1 is plaed

// so dp(n, k) = dp(n - 1, k) + dp(n - 1, k - 2) + ... + dp(n - 1, k - min(k, n))
// use sliding window sums to decrease TC from O(nk^2) to O(nk)

class Solution {
public:
    int MOD = 1000000007;
    vector<vector<int>> dp;


    // a, b must be non negative
    int add(int a, int b) {
        a %= MOD;
        b %= MOD;
        return (a + b) % MOD;
    }

    int subtract(int a, int b) {
        a %= MOD;
        b %= MOD;
        return (a - b + MOD) % MOD;
    }

    int maxInversePairs(int len) {
        return len * (len - 1) / 2;
    }

    void process(int N, int K) {
        dp = vector(N, vector(K + 1, -1));
        for (int k = 0; k <= K; k ++) {
            dp[0][k] = (k == 0) ? 1 : 0;
        }

        for (int i = 1; i < N; i ++) {
            int sum = dp[i - 1][0];
            int end = 0;
            dp[i][0] = 1;
            for (int k = 1; k <= K; k ++) {
                sum = add(sum, dp[i - 1][k]);
                if (k > i) {
                    sum = subtract(sum, dp[i - 1][end]);
                    end ++;
                }
                dp[i][k] = sum;
            }
        }
    }

    int kInversePairs(int n, int k) {
        process(n, k);
        return dp[n - 1][k];
    }
};

int main() {
    Solution sol;
    int ans = sol.kInversePairs(3, 1);
    cout << ans << endl;
}