#include <bits/stdc++.h>
using namespace std;

// while the numbers are in [1, 2^800 - 1], after the 1st op, number of bits is <= 800

class Solution {
public:
    vector<int> k_cnt;
    vector<vector<vector<int>>> dp;
    int MOD = 1000000007;

    void process_k_cnt(int max_len) {
        k_cnt = vector(max_len + 1, 0);
        k_cnt[1] = 0;
        for (int i = 2; i <= max_len; i ++) {
            k_cnt[i] = 1 + k_cnt[bitset<10>(i).count()];
        }
    }

    // flag == 1 means prefix [0, idx - 1] is the same as prefix of str, otherwise 0.
    // idx is curr index we are at.
    // bitcnt is how many 1s be can still place.
    // we want to know how many ways to make numbers with bitcnt 1s while still being lesser than number represented by str
    
    int helper(int flag, int idx, int bitcnt, string& str) {
        // cannot have flag to be 1, as that means number is equal
        if (idx == str.size()) return (bitcnt == 0 && flag == 0) ? 1 : 0;
        else if (dp[flag][idx][bitcnt] != -1) return dp[flag][idx][bitcnt];
        
        if (bitcnt == 0) {
            dp[flag][idx][bitcnt] = helper(flag == 1 && str[idx] == '0', idx + 1, bitcnt, str);
        } else if (flag == 1) {
            if (str[idx] == '0') {
                dp[flag][idx][bitcnt] = helper(flag, idx + 1, bitcnt, str);
            } else {
                int put1 = helper(flag, idx + 1, bitcnt - 1, str);
                int put0 = helper(0, idx + 1, bitcnt, str);
                dp[flag][idx][bitcnt] = (put1 + put0) % MOD;
            } 
        } else {
            int put1 = helper(0, idx + 1, bitcnt - 1, str);
            int put0 = helper(0, idx + 1, bitcnt, str);
            dp[flag][idx][bitcnt] = (put1 + put0) % MOD;
        }
        return dp[flag][idx][bitcnt];
    }

    int cnt_ones(string& s) {
        return accumulate(s.begin(), s.end(), 0, [](int accu, char c) {return accu + (c == '1');});
    }

    int countKReducibleNumbers(string s, int k) {
        int max_len = s.size();
        process_k_cnt(max_len);
        dp = vector(2, vector(s.size(), vector(max_len + 1, -1)));
        
        int sum = 0;
        for (int i = 1; i <= max_len; i ++) {
            if (k_cnt[i] >= k) continue;

            sum += helper(1, 0, i, s);
            sum %= MOD;
        }
        return sum;
        
    }



};

int main() {
    Solution sol;
    cout << sol.countKReducibleNumbers("1", 3) << endl;
}