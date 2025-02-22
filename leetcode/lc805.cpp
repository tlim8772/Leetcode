#include <bits/stdc++.h>
using namespace std;

// use pseudo polynomial dp
// by doing some math, it is true with sum of elements in A / size of A == sum of all elements / size of entire array
// since if successful, one of the arrays have size <= 0.5 * size of entire array
// so sum of elem in A is <= 1/2 * sum of all elements

class Solution {
public:
    bool dp[150001][16][30]; 
    int SUM;
    int SZ;

    bool process(vector<int>& nums, int limitSize, int limitSum) {
        
        for (int sum = 0; sum <= limitSum; sum ++) {
            for (int sz = 0; sz <= limitSize; sz ++) {
                int sumA = (sum + nums[SZ - 1]);
                bool inA = (sumA > limitSum || sz + 1 > limitSize) ? false : sumA * SZ == SUM * (sz + 1); 
                
                bool inB = (sz == 0) ? false : sum * SZ == SUM * sz; // check if sz == 0
                dp[sum][sz][SZ - 1] = inA || inB;
                //cout << dp[sum][sz][SZ - 1] << endl;
                
            }
        }

        

        for (int i = SZ - 2; i >= 0; i --) {
            for (int sum = 0; sum <= limitSum; sum ++) {
                for (int sz = 0; sz <= limitSize; sz ++) {
                    int sumA = sum + nums[i];
                    bool inA = (sumA > limitSum || sz + 1 > limitSize) ? false : dp[sumA][sz + 1][i + 1];

                    bool inB = dp[sum][sz][i + 1];
                    dp[sum][sz][i] = inA || inB;
                }
            }
        }

        return dp[0][0][0];
    }

    bool splitArraySameAverage(vector<int>& nums) {
        SUM = accumulate(nums.begin(), nums.end(), 0, [](int accu, int x) {return accu + x;});
        SZ = nums.size();
        int limitSize = SZ / 2;
        int limitSum = SUM / 2;
        //dp = vector(limitSum + 1, vector(limitSize + 1, vector(SZ, false)));

        cout << SUM << endl;
        int ans = process(nums, limitSize, limitSum);
       
        return ans;
    }



};

int main() {
    Solution sol;
    vector<int> arr = {904,8738,6439,1889,138,5771,8899,5790,662,8402,3074,1844,5926,8720,7159,6793,7402,9466,1282,1748,434,842,22};
    int res = sol.splitArraySameAverage(arr);
    cout << res << endl;
    
}