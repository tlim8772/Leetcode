#include <vector>
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

// O(nnk) dp, but optimise to O(nk)
// let dp(i, j) = num of paritions into j non empty subtrings starting at s[i]
// we need to iterate from i + 2 to s.size() - 1, to find the split
// however, when we calculate dp(i - 1, j), the indexes that we can split for dp(i, j) can be used for dp(i - 1, j)
// so we use a ptr to store the leftmost possible next split, and all dp(s.size() - 1, j), dp(s.size() - 2, j) ... dp(i, j)
// only move the ptr to the left

class Solution {
public:
    vector<vector<int>> dp;
    int MOD = 1000000007;

    bool isPrime(char c) {
        return (c == '2' ||c == '3' || c == '5' || c == '7');
    }

    // dp[i][j] is how many ways to partiton into j + 1 'beautiful' substrings
    // minLength >= 2 as substring must start with prime num and end with non prime
    int helper(string& s, int k, int minLength) {
        dp = vector(s.size(), vector(k, 0));
        for (int i = s.size() - 1; i >= 0; i --) {
            (s.size() - i >= minLength && isPrime(s[i]) && !isPrime(s[s.size() -1])) ? dp[i][0] = 1 : dp[i][0] = 0;
        }

        for (int j = 1; j < k; j ++) {
            int ptr = s.size() - 1; // ptr points to the rightmost next available state
            int sum = 0;
            
            // shift first to correct pos, then calculate num of ways
            for (int i = s.size() - 1; i >= 0; i --) {
                while (ptr >= i + minLength && ptr > 0) {
                    if (!isPrime(s[ptr - 1])) {
                        sum += dp[ptr][j - 1];
                        sum %= MOD;
                    }
                    ptr --;
                }
                dp[i][j] = (isPrime(s[i])) ? sum : 0;
            }
        }
        //cout << dp[4][1] << endl;
        //cout <<dp[9][0] << endl;
        return dp[0][k - 1];
    }

    int beautifulPartitions(string s, int k, int minLength) {
        return helper(s, k, (minLength < 2) ? 2 : minLength);
    }
};

int main() {
    Solution sol;
    string s = "3312958";
    int k = 3;
    int minLength = 1;
    cout << sol.beautifulPartitions(s, k, minLength);
}