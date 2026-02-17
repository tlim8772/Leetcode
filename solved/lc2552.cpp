#include <bits/stdc++.h>
using namespace std;

// read problem carefully, want i < j < k < l s.t nums[i] < nums[k] < nums[j] < nums[l].
// j and k are swapped.
// first we find for all possible values of k, and for each index i, # of elems in arr[:i+1]
// s.t elem < nums[k]
// for all possible values of j, and for each index i, # of elems in arr[i:] s.t elem > nums[j]
// then we fix j, k and just count.

class Solution {
public:
    long long countQuadruplets(vector<int>& nums) {
        for (int& x : nums) x--;
        
        vector<vector<int>> store_k(nums.size(), vector<int>(nums.size(), 0));
        for (int k_val = 0; k_val < nums.size(); k_val++) {
            int sum = 0;
            for (int i = 0; i < nums.size(); i++) {
                store_k[k_val][i] = (sum += nums[i] < k_val);
            }
        }

        vector<vector<int>> store_j(nums.size(), vector<int>(nums.size(), 0));
        for (int j_val = 0; j_val < nums.size(); j_val++) {
            int sum = 0;
            for (int i = nums.size() - 1; i > -1; i--) {
                store_j[j_val][i] = (sum += nums[i] > j_val);
            }
        }

        long long sum = 0;
        for (int j = 1; j < nums.size() - 2; j++) {
            for (int k = j + 1; k < nums.size() - 1; k++) {
                int j_val = nums[j], k_val = nums[k];
                if (j_val <= k_val) continue;
                sum += (long long) store_k[k_val][j - 1] * store_j[j_val][k + 1];
            }
        }
        
        return sum;
    }
};

int main() {
    //test_seg_tree();

    Solution sol;
    vector<int> nums = {1,2,3,4};
    long long ans = sol.countQuadruplets(nums);
    cout << ans << endl;

}