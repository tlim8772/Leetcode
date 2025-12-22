#include <bits/stdc++.h>
using namespace std;

// bin elements according to modulo 3.
// then simply try all possible combinations, s.t the sum is 0 (mod 3).
// we store the elements in a multiset, and at every step, take the largest elem.

class Solution {
public:

    int helper(int m, int idx, int sum, vector<multiset<int>>& bins) {
        if (idx == 2) {
            int final_m = (3 - sum) % 3;
            auto& bin = bins[final_m];
            if (bin.empty()) return -999999;
            return *bin.rbegin();
        } else {
            int best = -999999;
            for (int n = m; n < 3; n++) {
                auto& bin = bins[n];
                if (bin.empty()) continue;

                int v = *bin.rbegin();
                bin.erase(prev(bin.end()));
                best = max(best, v + helper(n, idx + 1, (sum + n) % 3, bins));
                bin.insert(v);
            }

            return best;
        }
    }
    
    
    int maximumSum(vector<int>& nums) {
        vector<multiset<int>> bins(3, multiset<int>());
        for (int x : nums) {
            bins[x % 3].insert(x);
        }

        return max(0, helper(0, 0, 0, bins));
    }
};

int main() {
    Solution sol;
    vector<int> arr = {4,2,3,1};
    cout << sol.maximumSum(arr) << endl;
}