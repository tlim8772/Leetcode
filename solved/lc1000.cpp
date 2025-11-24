#include <bits/stdc++.h>
using namespace std;

// work from the back. The last merge combines k consecutive ranges
// there is a split, i.e arr[0..i] and arr[i + 1...len - 1] are independent, no op merge indexes from these 2 sets
// dp(i, j, m): minimum cost to merge stones[i...j] into m piles
// suppose k = 4
// case 1: merge from size k to 1
// last merge merges [0..i1] [i1 + 1...i2] [i2 + 2...i3] [i3 + 1...n - 1]
// now the splits are clear, e.g we cannot have a merge [i1 - 1 ... i1 + 2]
// so the best transition is dp(0, i1, 1) and dp(i1, n - 1, 3)
// so every dp(i, j, m) has the last merge that takes it from m + (k - 1) to m elems


// case 2: merge from size m + a(k - 1) to m
// the last merge, let say merge to become range [x...y]
// then range [i...x - 1] is independent, just that the number of piles is unknown, have to try
// all possibilities, so we have the split position
// T.C is O(n^3 * kn)


class Solution {
public:
    int n, k;
    int INVALID = 1e6;
    vector<vector<vector<int>>> dp;
    vector<int> prefixSums;

    void processPrefixSums(vector<int>& stones) {
        prefixSums = vector(stones.size(), 0);
        int sum = 0;
        for (int i = 0; i < stones.size(); i ++) {
            sum += stones[i];
            prefixSums[i] = sum;
        }
    }

    int rangeSum(int l, int r) {
        return (l == 0) ? prefixSums[r] : prefixSums[r] - prefixSums[l - 1];
    }

    // check whether it is possinble to re
    bool isPossible(int i, int j, int m) {
        int len = j - i + 1;
        
        if (m > n || len < m || len < 0) return false;
        return ((len - m) % (k - 1)) == 0;
    }
    
    int helper(int i, int j, int m) {
        if (!isPossible(i, j, m)) {
            return INVALID;
        }
        
        if (dp[i][j][m] != -1) {
            return dp[i][j][m];
        } else if ((j - i + 1) == m) {
            dp[i][j][m] = 0;
            return dp[i][j][m];
        } else if (m == 1) {
            int mergeCost = rangeSum(i, j);
            int res = helper(i, j, k);

            dp[i][j][m] = res + mergeCost;
            return res + mergeCost;
        } else {
            int best = 1e7;
            for (int s = i; s < j; s ++) {
                for (int c = 1; c < m; c ++) {
                    int left = helper(i, s, c);
                    int right = helper(s + 1, j, m - c);
                    int res = left + right;
                    best = min(best, res);
                }
            }
            dp[i][j][m] = best;
            return best;
        }
        
    }

    int mergeStones(vector<int>& stones, int k) {
        this->k = k;
        this->n = stones.size();
       
        dp = vector(n, vector(n, vector(n + 1, -1)));
        processPrefixSums(stones);
        
        //cout << helper(0, 1, 1) << endl;
        int ans = helper(0, n - 1, 1);
        
        return (ans >= INVALID) ? -1 : ans;
    }
};

int main() {
    Solution sol;
    vector<int> stones = {1};
    int k = 3;
    int ans = sol.mergeStones(stones, k);
    cout << ans << endl;
}