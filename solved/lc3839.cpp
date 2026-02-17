#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int prefixConnected(vector<string>& words, int k) {
        unordered_map<string, int> store;
        for (auto& w : words) {
            if (w.size() < k) continue;
            store[w.substr(0, k)] += 1;
        }
        int cnt = 0;
        for (auto& [k, v] : store) {
            cnt += (v >= 2);
        }
        return cnt;
    }
};