#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    vector<vector<vector<long long>>> dp;

    // x means some elem has been chosen for subarray j
    long long helper(int i, int j, int x, vector<int>& nums) {
        if (j == 0) {
            return 0;
        } else if (i == nums.size()) {
            return (j == 1 && x == 1) ? 0 : -100000000000000L;
        } else if (dp[i][j][x] != -100000000000000L) {
            return dp[i][j][x];
        } else if (!x) {
            int sign = (j % 2 == 1) ? 1 : -1;
            long long option1 = nums[i] * j * sign + helper(i + 1, j, 1, nums);
            long long option2 = helper(i + 1, j, 0, nums);
            dp[i][j][x] = max(option1, option2);
            return dp[i][j][x];
        } else {
            int sign = (j % 2 == 1) ? 1 : -1;
            long long option1 = helper(i, j - 1, 0, nums); // go to the next subarray already, in the next group, can dont choose elem
            long long option2 = nums[i] * j * sign + helper(i + 1, j, 1, nums);
            dp[i][j][x] = max(option1, option2);
            return dp[i][j][x];
        }
    }
    
    long long maximumStrength(vector<int>& nums, int k) {
        dp = vector(nums.size(), vector<vector<long long>>(k + 1, vector<long long>(2, -100000000000000L)));
        return helper(0, k, 0, nums);
    }
};

int main() {
    vector<int> nums = {1,2,3,-1,2};
    int k = 3;
    cout << Solution().maximumStrength(nums, k);
}