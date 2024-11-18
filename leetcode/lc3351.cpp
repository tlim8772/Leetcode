#include <bits/stdc++.h>
using namespace std;



class Solution {
public:
    int MOD = 1000000007;
    unordered_map<int, vector<int>> dp;

    int mult(int a, int b) {
        a %= MOD;
        b %= MOD;
        long long ans = (long long) a * b;
        return (int) (ans % MOD);
    }

    int add(int a, int b) {
        return ((a % MOD) + (b % MOD)) % MOD;
    }

    int sumOfGoodSubsequences(vector<int>& nums) {
        

        dp[nums.back()] = {1, nums.back()};

        // we do dp from the last index
        // dp[i] stores number of good subsequence starting at number i, and the sum;
        // so at index i, if already have an entry for dp[nums[i]], add to it
        // remeber need to do modulo for cnt, as cnt scales at O(len(nums) ^ 2)
        for (int i = nums.size() - 2; i >= 0; i --) {
            int cnt = 1;
            int sum = nums[i];

            // find num of good subsequences starting with num[i] + 1
            if (dp.find(nums[i] + 1) != dp.end()) {
                int c = dp[nums[i] + 1][0];
                int s = dp[nums[i] + 1][1];
                
                cnt = add(cnt, c);
                sum += add(mult(c, nums[i]), s);
                sum %= MOD;
            }

            // find num of good subsequences starting with num[i] - 1
            if (dp.find(nums[i] - 1) != dp.end()) {
                int c = dp[nums[i] - 1][0];
                int s = dp[nums[i] - 1][1];
                
                cnt = add(cnt, c);
                sum += add(mult(c, nums[i]), s);
                sum %= MOD;
            }

            if (dp.find(nums[i]) != dp.end()) {
              
                cnt = add(cnt, dp[nums[i]][0]);
                sum = add(sum, dp[nums[i]][1]);
            }

           
            dp[nums[i]] = {cnt, sum};
        }


        int res = 0;
        for (const auto& [key, value] : dp) {
            //cout << key << " " << value[0] << " " << value[1] << endl;
            res = add(res, value[1]);
        }
        return res;
    }
};

int main() {
    return 1;
}