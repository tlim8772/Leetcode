#include <bits/stdc++.h>
using namespace std;

// group strictly increasing subarray together
// best result is either between 2 increasing subarrays or within a subarray

class Solution {
public:

    vector<int> group(vector<int>& arr) {
        vector<int> out;
        int prev = arr[0];
        int s = 1;
        int cnt = 1;
        while (s < arr.size()) {
            if (arr[s] > prev) {
                prev = arr[s];
                s ++;
                cnt ++;
            } else {
               out.push_back(cnt);
               prev = arr[s];
               cnt = 1;
               s ++;
            }
        }

        out.push_back(cnt);
        return out;
    }

    int maxIncreasingSubarrays(vector<int>& nums) {
        vector<int> collected = group(nums);

        int best = 1;
        best = accumulate(collected.begin(), collected.end(), 1, [](int accu, int x) {return max(accu, x / 2);});
    
        for (int i = 0; i < collected.size() - 1; i ++) {
            int lhs = collected[i];
            int rhs = collected[i + 1];
            int ans = min(lhs, rhs);
            best = max(best, ans);
        }
        return best;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1,2,3,4,4,4,4,5,6,7};
    cout << sol.maxIncreasingSubarrays(nums) << endl;
}