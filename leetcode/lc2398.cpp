#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// binary search on k: length of consecutive robots.
// use ll sum to store the sliding window sum, and multiset to get max and remove elems in log(n).

bool helper(vector<int>& chargeTimes, vector<int>& runningCosts, int k, ll budget) {
    if (k == 0) return true;

    ll sum = 0;
    multiset<int> charges;
    for (int i = 0; i < k; i++) {
        sum += runningCosts[i];
        charges.insert(chargeTimes[i]);
    }

    for (int i = 0; i <= runningCosts.size() - k; i++) {
        ll cost = *(--charges.end()) + k * sum;
        if (cost <= budget) return true;

        if (i < runningCosts.size() - k) {
            sum -= runningCosts[i];
            sum += runningCosts[i + k];

            charges.erase(charges.find(chargeTimes[i]));
            charges.insert(chargeTimes[i + k]);
        }
    }

    return false;

}

class Solution {
public:
    int maximumRobots(vector<int>& chargeTimes, vector<int>& runningCosts, long long budget) {
        int s = 0, e = runningCosts.size();
        while (s < e) {
            int m = (s + e + 1) >> 1;
            bool res = helper(chargeTimes, runningCosts, m, budget);
            if (res) s = m;
            else e = m - 1;
        }
        return s;
    }
};

int main() {
    Solution sol;
    vector<int> 
        c = {3,6,1,3,4}, 
        r = {2,1,3,4,5};
    int b = 25;
    int ans = sol.maximumRobots(c, r, b);
    cout << ans << endl;
    
}

