#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007

// 3d dp
// dp(i, x, y) = number of disjoint subsequence pairs from index i onwards, with accumulated gcd in seq 1 = x
// and accumulated gcd in seq 2 = y, such that the resultant 2 seq are disjoint
// take or leave dp

class Solution {
public:
    vector<vector<vector<int>>> dp;
    vector<int> nums;
    
    int gcd(int a, int b) {
        if (a < b) return gcd(b, a);
        if (b == 0) return a;
        return gcd(b, a % b);
    }

    int helper(int i, int x, int y) {
        if (i == nums.size()) return (x == 0 || y == 0 || x != y) ? 0 : 1;
        else if (dp[i][x][y] != -1) return dp[i][x][y];
        else {
            // either put nums[i] in seq 1 or seq 2
            int noTake = helper(i + 1, x, y);
            int putInSeq1 = helper(i + 1, gcd(nums[i], x), y);
            int putInSeq2 = helper(i + 1, x, gcd(nums[i], y));

            int temp = (putInSeq1 + putInSeq2) % MOD;
            int res = (noTake + temp) % MOD;
            dp[i][x][y] = res;
            return res;    
        }
    }


    int subsequencePairCount(vector<int>& nums) {
        this->nums = nums;
        dp = vector(nums.size(), vector(201, vector(201, -1)));
        return helper(0, 0, 0);
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1,2,3,4};
    cout << sol.subsequencePairCount(nums) << endl;
}