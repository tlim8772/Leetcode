#include <bits/stdc++.h>
using namespace std;

// dp(p): chance of winning with current score of p
// e.g dp(0) = 1 / maxPts * (dp(1) + dp(2) + dp(3) ... dp(maxPts))
// have to do bottom up dp, keep a sliding window of the sum

class Solution {
public:
    double new21Game(int n, int k, int maxPts) {
        if (k == 0) return 1.0;

        vector<double> store(k + maxPts, 0);

        for (int p = k; p <= min(n, (int) store.size() - 1); p++) {
            store[p] = 1;
        }

        // find store[k - 1]
        double sum = 0;
        for (int p = k; p <= k - 1 + maxPts; p++) {
            sum += store[p];
        }
        store[k - 1] = (1.0 / maxPts) * sum;

        for (int p = k - 2; p >= 0; p--) {
            sum += store[p + 1];
            sum -= store[p + 1 + maxPts];
            
            store[p] = (1.0 / maxPts) * sum;
        }
        
        return store[0];
    }
};

int main() {
    int n = 0, k = 0, maxPts = 1;
    Solution sol;

    cout << sol.new21Game(n, k, maxPts) << endl;
}