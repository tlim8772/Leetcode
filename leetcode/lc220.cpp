#include <bits/stdc++.h>
using namespace std;

// we only consider pairs (i,j) where i < j
// sliding windows and multi set

class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
        multiset<int> mySet;

        bool ans = false;
        for (int i = 0; i < nums.size(); i++) {
            if (i == 0) {
                for (int j = 1; j <= min(i + indexDiff, (int) nums.size() - 1); j++) {
                    mySet.insert(nums[j]);
                }
            } else {
                auto it = mySet.find(nums[i]);
                mySet.erase(it);
                
                if (i + indexDiff < nums.size()) {
                    mySet.insert(nums[i + indexDiff]);
                }
            }

            int s = nums[i] - valueDiff;
            int e = nums[i] + valueDiff;

            // val is smallest elem not less than s
            // we only need to consider the smallest value >= s
            // if > e, then cannot find already
            auto ans = mySet.lower_bound(s);
            if (ans == mySet.end()) {
                continue;
            } else if (*ans <= e) {
                return true;
            }
        }

        return false;
    }
};

int main() {
    vector<int> nums = {1,2,3,1};
    int indexDiff = 3;
    int valueDiff = 0;

    Solution sol;
    cout << sol.containsNearbyAlmostDuplicate(nums, indexDiff, valueDiff) << endl;
}