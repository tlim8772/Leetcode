#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// another 2 pointer problem

class Solution {
public:
    int minLength(vector<int>& nums, ll k) {
        unordered_map<int, int> store;
        for (int x : nums) store[x] = 0;

        int best = 999999;
        int p = 0;
        ll sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            for (; p < nums.size() && sum < k; p++) {
                int n = nums[p];
                store[n]++;
                if (store[n] == 1) sum += n;
            }

            if (sum >= k) best = min(best, p - i);

            int my = nums[i];
            store[my]--;
            if (store[my] == 0) sum -= my;
        }

        return (best == 999999) ? -1 : best;
    }
};

int main() {
    Solution sol;

    vector<int> nums = {2,2,3,1};
    int k = 4;

    int ans = sol.minLength(nums, k);
    cout << ans << endl;
}