#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int firstUniqueFreq(vector<int>& nums) {
        unordered_map<int, int> store1;
        for (int x : nums) store1[x] += 1;
        
        unordered_map<int, int> store2;
        for (auto [k, v] : store1) store2[v] += 1;
        
        for (int x : nums) {
            if (store2[store1[x]] == 1) return x;
        }
        return -1;
    }
};