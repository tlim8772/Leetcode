#include <bits/stdc++.h>
using namespace std;
constexpr int MOD = 1000000007;

// dp(i, more, less) means we are considering index i of s. 
// The previous digit gives 'more' digits greater than prev digit
// and 'less' digits lesser than prev digit 

class Solution {
public:
    int MORE = 201, LESS = 201;
    unordered_map<int, int> dp;

    inline int coor(int i, int more, int less) {
        return i * MORE * LESS + more * LESS + less;
    }

    int helper(int i, int m, int l, const string& s) {
        int pos = coor(i, m, l);
        if (i == s.size()) {
            return 1;
        } else if (dp.contains(pos)) {
            return dp[pos];
        }

        if (s[i] == 'I') {
            if (m == 0) {
                dp[pos] = 0;
                return 0;
            } else {
                // take smallest digit in m
                int take = helper(i + 1, m - 1, l, s);
                
                // or choose among the remaining m - 1 digits
                // add 1 to l, because now smallest digit in m move to set LESS
                int notake = helper(i, m - 1, l + 1, s);

                int res = (take + notake) % MOD;
                dp[pos] = res;
                return res;
            }
        } else {
            if (l == 0) {
                dp[pos] = 0;
                return 0;
            } else {
                // take largest digit in l
                int take = helper(i + 1, m, l - 1, s);

                // or choose among the remaining l - 1 digits
                // add 1 to m, because biggest digit in l move to set MORE
                int notake = helper(i, m + 1, l - 1, s);

                int res = (take + notake) % MOD;
                dp[pos] = res;
                return res;
            }
        }

    }

    int numPermsDISequence(string s) {
        int n = s.size();
        MORE = LESS = n + 1;

       
        int sum = 0;
        for (int i = 0; i <= n; i ++) {
            int res = helper(0, n - i, i, s);
            sum += res;
            sum %= MOD;
        }

        return sum;
    }
};

int main() {
    Solution sol;

    string s = "D";
    cout << sol.numPermsDISequence(s) << endl;
}