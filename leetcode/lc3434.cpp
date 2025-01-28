#include <bits/stdc++.h>
using namespace std;

// key here is that elems are int in [1,50]
// op: in any subrange, we can only range 1 value (e.g 10) to k.
// let say we are targeting a specific value, 10.
// in the array, change all k to -1, change all 10 to 1, all other numbers to 0
// we choose a subrange, and the addition to freq of k is the sum of that subarray (1 means targeted value change to k
// and -1 means elem of value k got change to something else)
// so result is init freq of k + max subarray sum
// use kadane algo to find max subarray sum
// TC is O(50 * 1e5)

class Solution {
public:
    int kadane(const vector<int>& arr) {
        vector<int> dp(arr.size(), 0);
        
        dp[arr.size() - 1] = max(0, arr.back());
        for (int i = arr.size() - 2; i >= 0; i --) {
            dp[i] = max(0, arr[i] + dp[i + 1]);
        }

        return accumulate(dp.begin(), dp.end(), 0, [](int acc, int x) -> int {return max(acc, x);});
    }

    vector<int> changeArr(int target, int k, const vector<int>& arr) {
        vector<int> out;
        for (int x : arr) {
            if (x == target) out.push_back(1);
            else if (x == k) out.push_back(-1);
            else out.push_back(0);
        }
        return out;
    }

    int maxFrequency(vector<int>& nums, int k) {
        int kFreq = accumulate(nums.begin(), nums.end(), 0, [k](int cnt, int x) {return cnt + (x == k);});
        

        int best = kFreq;
        for (int i = 1; i <= 50; i ++) {
            if (i == k) continue;
            vector<int> arr2 = changeArr(i, k, nums);
            int maxSubarraySum = kadane(arr2);
            best = max(best, kFreq + maxSubarraySum);
        }

        return best;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1,2,3,4,5,6};
    int k = 1;

    cout << sol.maxFrequency(nums,k) << endl;
}