#include <bits/stdc++.h>
using namespace std;

// dp(i, c) means how many distinct subsequence starting at sp[i:] and the 1st char must c (cannot be empty).
// this prevents double counting.

// suppose s = 'aabaa'
// substring is 'aba'.
// the corresponding operations is (0, a) -> (2, b) -> (3, a).
// no double counting as we take the 1st available char if it is the same.

// the operations to make eg 'aba' is to take 1a 1b 1a happens only 1 time.
// i.e there is only 1 such path in the DAG of the dp transitions.


class Solution {
public:
    vector<vector<int>> store;
    const int MOD = int(1e9 + 7);

    int dp(int i, int c, const string& s) {
        if (i == s.size()) {
            return c == 26;
        } else if (c == 26) {
            return 1;
        } else if (store[i][c] != -1) {
            return store[i][c];
        }

        int& ans = store[i][c];
        if (s[i] - 'a' == c) {
            int sum = 0;
            for (int j = 0; j < 27; j++) {
                sum += dp(i + 1, j, s);
                sum %= MOD;
            }
            return ans = sum;
        } else {
            return ans = dp(i + 1, c, s);
        }



    }

    int distinctSubseqII(string s) {
        store = vector(s.size(), vector(26, -1));
        
        int sum = 0;
        for (int j = 0; j < 26; j++) {
            sum += dp(0, j, s);
            sum %= MOD;
        }

        return sum;
    }
};

int main() {
    Solution sol;

    string s = "aaa";
    int ans = sol.distinctSubseqII(s);
    cout << ans << endl;
}