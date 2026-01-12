#include <bits/stdc++.h>
using namespace std;

// simple O(n^2) sol can pass.

class Solution {
public:
    int centeredSubarrays(vector<int>& nums) {
        unordered_set<int> store;
        int cnt = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            store.clear();
            int sum = 0;
            for (int j = i; j < nums.size(); j++) {
                sum += nums[j];
                store.insert(nums[j]);
                if (store.contains(sum)) cnt++;
            }
        }

        return cnt;
    }
};