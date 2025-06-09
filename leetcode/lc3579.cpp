#include <bits/stdc++.h>
using namespace std;

// important to note that reverse is fore the entire substring
// so we cannot swap [1,5] and reverse [2,3,4]
// hence, if we reverse at any step, we can reverse at the very start
// so only left swap and replace
// want to maximise swap, so we have freq[26][26] for (s1[i], s2[i]), then we check the other pair
// (s2[i], s1[i]) and take the min of the 2
// so dp(i) is min steps for substring [i..n - 1]
// we split at i, i + 1, ... n - 1

// to find max number of swaps, notice that (x,y) can only swap with (y,x)
// so is min(freq(x,y), freq(y,x)) for all (x,y), x < y

// we check both for normal string and reversed string

// so have O(n) state, transition is O(n^2)

// suppose we precompute the direct results for all possible [start, end] it is still O(n^3)
// because this precompuation is O(n^3)

class Solution {
public:
    vector<int> dp;
    int LEN;
    string s1; // s1.len == s2.len
    string s2;

   

    int direct(const string& s1, const string& s2) {
        int len = s1.size();
        int alreadyDone = 0;
        vector<vector<int>> store(26, vector(26, 0));
        
        for (int i = 0; i < s1.size(); i++) {
            if (s1[i] == s2[i]) {
                alreadyDone++;
                continue;
            }
            store[s1[i] - 'a'][s2[i] - 'a']++;
        }

        

        int cnt = 0;
        for (int x = 0; x < 26; x++) {
            for (int y = x + 1; y < 26; y++) {
                cnt += min(store[x][y], store[y][x]);
            }
        }
        return len - alreadyDone - cnt;
    }

    int helper(int i) {
        if (i >= LEN) {
            return 0;
        } else if (dp[i] != -1) {
            return dp[i];
        } else if (i == LEN - 1) {
            return 1 - (s1[i] == s2[i]);
        }

        int store = 999999;
        for (int k = 1; k <= LEN - i; k++) {
            string sub1 = s1.substr(i, k);
            string rsub1 = sub1;
            reverse(rsub1.begin(), rsub1.end());
            string sub2 = s2.substr(i, k);
            
           
            int noReverse = direct(sub1, sub2);
            int reverse = 1 + direct(rsub1, sub2);
            int best = min(noReverse, reverse);

            int ans = best + helper(i + k);
            store = min(store, ans);

            if (i == 0 && ans == 3) cout << k << endl;
        }
        
        dp[i] = store;
        return store;
    }

    int minOperations(string word1, string word2) {
        LEN = word1.size();
        dp = vector(LEN, -1);

        s1 = word1, s2 = word2;
        

        

        return helper(0);

    }

   

    
};

int main() {
    Solution sol;

    string s1 = "abdcc";
    string s2 = "eacdd";
    cout << sol.direct("bdcc", "acdd") << endl;
    int ans = sol.minOperations(s1, s2);
    cout << ans << endl;
}

