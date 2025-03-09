#include <bits/stdc++.h>
using namespace std;

// concat the 2 strings together, find longest palindromic subsequence
// however, we need to take at least 1 char from string 1 and 1 char from string 2

class Solution {
public:
    int INVALID = -1e6;
    
    int split; // idx < split means is string 1, >= split means is string 2

    int R, C;
    string str;
    vector<int> dp;
    

    inline int coor(int t0, int t1, int r, int c) {
        return c + r * C + t1 * R * C + t0 * 2 * R * C;
    }

    int helper(int t0, int t1, int s, int e) {
        int idx = coor(t0, t1, s, e);

        if (s > e) {
            return (t0 && t1) ? 0 : INVALID;
        } else if (dp[idx] != -1) {
            return dp[idx];
        } else if (s == e) {
            int ans;
            if ((s < split && t1) || (e >= split && t0)) {
                ans = 1;
            } else {
                ans = INVALID;
            }

            dp[idx] = ans;
            return ans;
        } else if (str[s] != str[e]) {
            int opt1 = helper(t0, t1, s, e - 1);
            int opt2 = helper(t0, t1, s + 1, e);
            int ans = max(opt1, opt2);
            dp[idx] = ans;
            return ans;
        } else {
            int ans = 2 + helper(t0 || (s < split), t1 || (e >= split), s + 1, e - 1);
            dp[idx] = ans;
            return ans;
        }
    }

    int longestPalindrome(string word1, string word2) {
        str = word1 + word2;
        R = C = str.size();
        split = word1.size();
        dp = vector(4 * R * C, -1);

        int ans = helper(0, 0, 0, str.size() - 1);
        return (ans < 0) ? 0 : ans;
    }


};

int main() {
    Solution sol;

    string word1 = "cacb";
    string word2 = "cbba";

    cout << sol.longestPalindrome(word1, word2) << endl;
}