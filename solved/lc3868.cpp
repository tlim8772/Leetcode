#include <bits/stdc++.h>
using namespace std;

// the total occurence of an element in nums1 and nums2 must be even, otherwise it is impossible.
// since we can freely move elements inside an array, the order of elements within an array does not matter.
// if nums1 have some elements < total cnt / 2, then some elements in nums1 must be > total cnt / 2.
// we swap elements as needed.

class Solution {
public:
    int minCost(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> store1, store2, total;
        for (int x : nums1) {
            store1[x]++;
            total[x]++;
        }
        for (int x : nums2) {
            store2[x]++;
            total[x]++;
        }

        // each element must have an even total occurence.
        for (auto [x, cnt] : total) if (cnt % 2 != 0) return -1;
        
        int sum = 0;
        for (auto [x, cnt] : total) {
            sum += abs(cnt / 2 - store1[x]);
        }
        return sum / 2;
    }
};

int main() {
    Solution sol;
    vector<int> nums1 = {10, 10};
    vector<int> nums2 = {20, 20};
    int ans = sol.minCost(nums1, nums2);
    println("Ans: {}", ans);
}