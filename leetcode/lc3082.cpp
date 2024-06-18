#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<vector<vector<int>>> dp;
    vector<int> nums;
    long long MOD = 1000000007;

    int helper(int index, int target, int numsLeft) {
        if (index == nums.size() || target == 0 || numsLeft == 0) {
            return (target == 0 && numsLeft == 0) ? 1 : 0;
        } else if (dp[index][target][numsLeft] != -1) {
            return dp[index][target][numsLeft];
        } else {
            // take curr number
            int case1 = (nums[index] <= target) ? helper(index + 1, target - nums[index], numsLeft - 1) : 0;
            // don't take curr number
            int case2 = helper(index + 1, target, numsLeft);
            int res = (case1 + case2) % MOD;
            dp[index][target][numsLeft] = res;
            return res;
        }
    }

    void init(vector<int>& nums, int k) {
        dp = vector(nums.size(), vector(k + 1, vector(nums.size() + 1, -1)));
        this->nums = nums;
    }

    int check(int k) {
        int s = 0;
        for (int i = 1; i <= nums.size(); i ++) {
            int a = helper(0, k, i);
            //cout << a << endl;
            s += a;
        }
        return s;
    }
    int fastModPow2(int n) {
        if (n == 0) {
            return 1;
        } else if (n % 2 == 1) {
            long long temp = (long long) fastModPow2((n - 1) / 2);
            long long ans = (temp * temp * 2) % MOD;
            return (int) ans;
        } else {
            long long temp = (long long) fastModPow2(n / 2);
            long long ans = (temp * temp) % MOD;
            return (int) ans;
        }
    }

    int sumOfPower(vector<int>& nums, int k) {
        init(nums, k);
        int score = 0;
        for (int i = 1; i <= nums.size(); i ++) {
            long long nn = helper(0, k, i);
            long long mult = fastModPow2(nums.size() - i);
            long long ans = (nn * mult) % MOD;
            score += (int) ans;
            score %= (int) MOD;
            
        }
        return score;
    }
};


int main() {
    vector<int> n = {1,2,3};
    int k = 7;
    Solution s;
    cout << s.sumOfPower(n, k) << endl;
    cout << s.fastModPow2(10) << endl;
    
}