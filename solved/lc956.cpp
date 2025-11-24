#include <bits/stdc++.h>
using namespace std;

// take dont take pseudo-polynomial dp
// dp(idx, offset) means that given set A has already offset value i.e current sum of elems in A - current sum of elems in B is offset
// , what is the max value we can get
// splitting (can be not all) elems from idx onwards into set A and set B, such that sum of elems in set A and
// sum of elems in set B is equal

class Solution {
public:
    vector<vector<int>> dp;
    vector<int> rods;

    int helper(int idx, int offset, int sum) {
        if (idx == rods.size()) return (offset == 0) ? 0 : -999999999;
        else if (dp[idx][offset + 5000] != -1) return dp[idx][offset + 5000];
        else {
            // dont take
            int opt0 = helper(idx + 1, offset, sum);

            // put to set 1
            int opt1 = rods[idx] + helper(idx + 1, offset + rods[idx], sum + rods[idx]);

            // put to set 2
            int opt2 = helper(idx + 1, offset - rods[idx], sum);

            dp[idx][offset + 5000] = max(opt0, max(opt1, opt2));
            return dp[idx][offset + 5000];
        }
    }

    int tallestBillboard(vector<int>& rods) {
        this->rods = rods;
        dp = vector(rods.size(), vector(10001, -1));
        int ans = helper(0, 0, 0);
        return max(0, ans);
    }

};

int main() {
    vector<int> rods = {1,2};
    Solution sol;
    cout << sol.tallestBillboard(rods) << endl;
}