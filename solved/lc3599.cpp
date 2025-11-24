#include <bits/stdc++.h>
using namespace std;

// simple dp
// dp(idx, left) means best result for prefix[0..idx] with left + 1 subarrays to form 
// optimise using bottom up dp and flattened (1d instead of 2d) array to store results
// and not considering invalid states (i.e num of elems < num of subarrays left)

class Solution {
public:
    const int INVALID = -1;

    vector<int> getPrefixXor(const vector<int>& nums) {
        vector<int> out;
        
        out.push_back(nums[0]);
        for (int i = 1; i < nums.size(); i++) {
            out.push_back(out.back() ^ nums[i]);
        }
        
        return out;
    }


    int minXor(vector<int>& nums, int k) {
        vector<int> store(nums.size() * k, 0);

        // process left == 0 first
        store[0] = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            store[i * k] = store[(i - 1) * k] ^ nums[i];
        }

        for (int left = 1; left < k; left++) {
            for (int i = 0; i < nums.size(); i++) {
                if (i < left) {
                    store[i * k + left] = INVALID;
                } else {
                    int best = 1000000007;
                    int curr = 0;
                    for (int j = i; j >= left; j--) {
                        curr ^= nums[j];
                        int res = max(curr, store[(j - 1) * k + left - 1]);
                        best = min(best, res);
                    }

                    store[i * k + left] = best;
                }
            }
        }

        return store[(nums.size() - 1) * k + k - 1];

    }
};

int main() {
    Solution sol;

    vector<int> nums = {2,3,3,2};
    int k = 3;

    cout << sol.minXor(nums, k) << endl;
}