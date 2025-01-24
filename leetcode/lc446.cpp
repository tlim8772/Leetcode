#include <bits/stdc++.h>
using namespace std;
using Pair = tuple<int, int>;
using ll = long long;

// not really dp. Starting from the right, let say for index i + 1, i + 2 ... len - 1
// we know for any value step, the number of length 2 sequences and length >2 sequence
// for i, we iterate through j, i < j < len. We want to know the number of length 2 and length >2 arithmetic subsequence
// starting at i
// if we go to index k, we know the step is arr[k] - arr[i]. We count the number of length 2 and length >2 arithmetic subsequence
// k has for value step
// to get the length 2 subsequence for each possible value of step for i, it is simple. Go through j, i < j < len, and let the step
// be arr[j] - arr[i]
// for length >2 , we need to know the sum of length 2 and length >2 subsequence for each index j

// get<0>(Pair) returns length 2 subsequence with a specific step
// get<1>(Pair) return length >2 subsequence with a specific step

class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        vector<unordered_map<ll, Pair>> dp(nums.size(), unordered_map<ll, Pair>());
        int cnt = 0;
        
        for (int i = nums.size() - 2; i >= 0; i --) {
            unordered_map<ll, Pair>& store = dp[i];
            
            for (int j = i + 1; j < nums.size(); j ++) {
                unordered_map<ll, Pair>& next = dp[j];
                ll step = (ll) nums[j] - nums[i];
                
                
                get<0>(store[step]) ++;
                
                int valid = get<0>(next[step]) + get<1>(next[step]);
               
                get<1>(store[step]) += valid; // add all valid subsequences to get<1>(store[step])
                
                cnt += valid;

            }
            
        }
        
        return cnt;



    }


};

int main() {
    vector<int> nums = {0,2000000000,-294967296};
    Solution sol;
    
    int ans = sol.numberOfArithmeticSlices(nums);
    cout << ans << endl;
}