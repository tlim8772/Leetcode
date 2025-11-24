#include <bits/stdc++.h>
using namespace std;

// 3d dp. dp(i, j, k) means longest palindrome substring for string[i, j] with k ops left
// we try to match the 2 endpoints, if cannot either i move forward by 1 or j move backward by 1

class Solution {
public:
    int I, J, K;
    vector<int> dp;

    inline int coor(int i, int j, int k) {
        return i * J * K + j * K + k;
    }

    int diff(char a, char b) {
        if (a > b) swap(a, b); // a < b
        int x = a - 'a', y = b - 'a';
        return min(y - x, x + 26 - y);
    }

    int helper(int i, int j, int k, const string& s) {
        int idx = coor(i, j, k);
        
        if (i > j) {
            return 0;
        } else if (dp[idx] != -1) {
            return dp[idx];
        } else if (i == j) {
            dp[idx] = 1;
            return 1;
        } else {
            int d = diff(s[i], s[j]);
            
            // try to match the 2 end points
            int opt1 = (k >= d) ? 2 + helper(i + 1, j - 1, k - d, s) : 0;

            int opt2 = helper(i, j - 1, k, s);
            int opt3 = helper(i + 1, j, k, s);

            int ans = max(max(1, opt1), max(opt2, opt3));
            dp[idx] = ans;
            return ans;
        }
    }

    
    int longestPalindromicSubsequence(string s, int k) {
        I = J = s.size();
        K = k + 1;

        dp = vector(I * J * K, -1);

        return helper(0, s.size() - 1, k, s);
    }
};

int main() {
    Solution sol;

    string s = "bt";
    int k = 10;
    cout << sol.longestPalindromicSubsequence(s, k);
}