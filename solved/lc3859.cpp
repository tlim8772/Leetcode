#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 2 pointer sliding window.
// for each index i, let e0, e1, be s.t arr[i:e0] is the 1st valid subarray and arr[1:e1] is the last valid subarray. 
// (note we use python slicing, so exclusive end).
// for e1, we just move right until the next e1 causes # of distinct elems to be k + 1.
// for e0, we have to check also that each element occurs >= m times.
// could be possible we cannot find e0.

class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k, int m) {
        ll out = 0;
        int e0 = 0, e1 = 0;
        int pass_0 = 0;
        unordered_map<int, int> store_0, store_1;

        for (int i = 0; i < nums.size(); i++) {
            while (e0 < nums.size() && store_0.size() < k) {
                int x = nums[e0];
                if (++store_0[x] == m) pass_0++;
                e0++;
            }

            while (e0 < nums.size() && pass_0 < k) {
                int x = nums[e0];
                if (!store_0.contains(x)) break;
                if (++store_0[x] == m) pass_0++;
                e0++;
            }

            while (e1 < nums.size()) {
                int x = nums[e1];
                if (store_1.size() == k && !store_1.contains(x)) break;
                store_1[x]++;
                e1++;
            }

            if (pass_0 == k) out += (e1 - e0 + 1);
            //println("{} {} {}", i, e0, e1);s

            // remove elem i.
            int elem = nums[i];
            int cnt_0 = --store_0[elem], cnt_1 = --store_1[elem];
            if (cnt_0 == m - 1) pass_0--;
            if (cnt_0 == 0) store_0.erase(elem);
            if (cnt_1 == 0) store_1.erase(elem);
        }
        return out;
    }
};

int main() {
    Solution sol;
    vector<int> nums(100000, 1);
    int k = 1, m = 1;
    ll ans = sol.countSubarrays(nums, k, m);
    println("Ans: {}", ans);
}