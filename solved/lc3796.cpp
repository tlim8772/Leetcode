#include <bits/stdc++.h>
using namespace std;

// the maximum of an element is the diff and the propogated restrictions.
// eg if index i is restricted to 10, then eg j, j > i, max[j] <= cumulative diff from i to j
// same reasoning if j < i.

// now if we take the min from doing this propogation, the resulting sequence satisfy the diff requirement.
// proof, let vi < vi+1
// then vi+1 <= vi + diff[i] clearly, so the diff is satisfied.
// same if vi > vi+1.

// we do right propogation and left propogation.
// as we propogate right, if the restricted value is lower than curr, replace curr with the restricted value.
// this way the propogation of n restrictions is in O(n).

class Solution {
public:
    int findMaxVal(int n, vector<vector<int>>& restrictions, vector<int>& diff) {
        vector<int>& last = *max_element(restrictions.begin(), restrictions.end(), 
            [] (const vector<int>& v1, const vector<int>& v2) { return v1[0] < v2[0]; });
        
        unordered_map<int,int> limits;
        limits[0] = 0;
        for (auto& v : restrictions) {
            limits[v[0]] = v[1];
        }

        vector<int> toRightLimits(n, 999999999);
        toRightLimits[0] = 0;
        int curr = diff[0];
        for (int i = 1; i < n; i++) {
            if (limits.contains(i) && limits[i] < curr) {
                curr = limits[i];
            }
            toRightLimits[i] = curr;
            if (i < n - 1) curr += diff[i];
        }

        vector<int> toLeftLimits(n, 999999999);
        toLeftLimits[last[0]] = last[1];
        curr = last[1] + diff[last[0] - 1];
        for (int i = last[0] - 1; i > -1; i--) {
            if (limits.contains(i) && limits[i] < curr) {
                curr = limits[i];
            }
            toLeftLimits[i] = curr;
            if (i > 0) curr += diff[i - 1];
        }

        int best = 0;
        for (int i = 0; i < n; i++) {
            best = max(best, min(toRightLimits[i], toLeftLimits[i]));
        }
        return best;

    }
};

int main() {
    Solution sol;

    int n = 10;
    vector<vector<int>> restrictions = {{3,1},{8,1}};
    vector<int> diff = {2,2,3,1,4,5,1,1,2};

    int ans = sol.findMaxVal(10, restrictions, diff);
    cout << ans << endl;
}