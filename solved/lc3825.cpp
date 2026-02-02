#include <bits/stdc++.h>
using namespace std;

// if bitwise AND is > 0, then all num in the subsequence must have a common set bit.
// try all bits 0, 1, 2 ... 30

int longest_increasing_subsequence(const vector<int>& nums) {
    int INF = 1e9 + 1;
    auto store = vector(nums.size() + 1, INF);
    int best = 0;
    
    store[0] = -INF;
 
    for (int x : nums) {
        auto it = upper_bound(store.begin(), store.end(), x);
        if (x < *it && x > *(it - 1)) {
            *it = x;
            best = max((int) best, (int) (it - store.begin()));
        }   
    }
    return best;
}

class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int best = 0;
        vector<int> store;
        for (int i = 0; i < 30; i++) {
            store.clear();
            for (int x : nums) {
                if ((x >> i) & 1) store.push_back(x);
            }
            int ans = longest_increasing_subsequence(store);
            best = max(best, ans);
        }
        return best;
    }
};

int main() {
    cout << longest_increasing_subsequence({1, 1}) << endl;
}