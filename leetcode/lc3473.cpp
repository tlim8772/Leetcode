#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    const int INVALID = -5 * 1e7;
    const int MIN = -2 * 1e7;
    vector<int> nums;
    int I, K, M;

    vector<int> dp;

    int coor(int i, int k, int m) {
        return i * ((K + 1) * (M + 1)) + k * (M + 1) + m;
    }

    

   

    void process(vector<int>& nums) {
        for (int k = 0; k <= K; k ++) {
            for (int m = 0; m <= M; m ++) {
                dp[coor(I, k, m)] = (k == 0 && m == 0) ? 0 : MIN;
            }
        }

        for (int i = nums.size() - 1; i >= 0; i --) {
            for (int k = 0; k <= K; k ++) {
                for (int m = 0; m <= M; m ++) {
                    // no take, but can only skip if have not taken any elems
                    int opt1 = (m != M) ? MIN : dp[coor(i + 1, k, m)];

                    // take elem 
                    int opt2 = nums[i] + dp[coor(i + 1, k, max(0, m - 1))];

                    // fill next array
                    int opt3 = (k == 0 || m != 0) ? MIN : dp[coor(i, k - 1, M)];

                    // if already filled all, can just return 0
                    int opt4 = (k == 0 && m == 0) ? 0 : MIN;
                    dp[coor(i, k, m)] = max(max(opt1, opt2), max(opt3, opt4));
                }
            }
        }
    }

    int maxSum(vector<int>& nums, int k, int m) {
        this->I = nums.size();
        this->K = k;
        this->M = m;
        //this->nums = nums;
        dp = vector((nums.size() + 1) * (k + 1) * (m + 1), INVALID);

        process(nums);
        return dp[coor(0, k - 1, m)];
    }
};

int main() {
    vector<int> nums = {-2,-10,15,12,8,11,5};
    int k = 3;
    int m = 2;
    Solution sol;

    cout << sol.maxSum(nums, k, m) << endl;
}