#include <bitset>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    bitset<100001> dp;
    int LIMIT = 1e5;

    int maxTotalReward(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        dp[0] = 1;
        for (int val : nums) {
            // invariant: after every iteration, bitset[i] is 1 if can achieve score i with prefix nums[0... index of lasr iteration]
            // when we conider val at 
            // we only need to consider val <= score <= 2 * val - 1
            // because any value < val, it can only be done with prefix nums[0... i-1]
            // any value >= 2 * val , impossible
            // to do so only need to consider range val - val = 0 to range 2 * val - 1 = val - 1;
            // once we get the biset consisting of bits [val - 1, 0],
            // we shift another val bits to the right, to get the possible results for range [val, 2 * val - 1]

            int shift = LIMIT - (val - 1);
            bitset<100001> temp = (dp << shift) >> shift;
            dp |= temp << val; 
        }
        for (int i = LIMIT - 1; i >= 0; i --) {
            if (dp[i]) return i;
        }
        return 0;   
    }
};

int main() {
    vector<int> nums = {1, 6,4,3,2};
    Solution sol;
    cout << sol.maxTotalReward(nums) << endl;
}