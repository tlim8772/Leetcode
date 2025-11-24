#include <bits/stdc++.h>
using namespace std;

// dp(bm): shortest time to break rest of locks. The time used to break the prev locks are not important, and that time
// may not even be optimal

class Solution {
public:
    int n, k;
    vector<int> times;
    vector<int> dp; 

    int helper(int bm, int howMany) {
        if (bm == (1 << n) - 1) {
            return 0;
        } else if (dp[bm] != -1) {
            return dp[bm];
        } else {
            int currE = 1 + howMany * k;
            int best = 1e7;
            for (int i = 0; i < n; i ++) {
                if (((bm >> i) & 1) == 1) continue;
                
                int res = (int) ceil(times[i] / (double) currE) + helper(bm + (1 << i), howMany + 1);
                best = min(best, res);
            }

            dp[bm] = best;
            return best;
        }
    }

    int findMinimumTime(vector<int>& strength, int k) {
        n = strength.size();
        this->k = k;
        times = strength;
        dp = vector(1 << n, -1);

        int ans = helper(0,0);
        return ans;

    }
};

int main() {
    Solution sol;

    vector<int> strength = {2,5,4};
    int k = 2;

    cout << sol.findMinimumTime(strength, k) << endl;

    
}