#include <bits/stdc++.h>
using namespace std;

// intuitively, the position of char do not matter, only the number of index with wrong chars matter
// hence every swap must increase num of correct pos by >= 1
// also for swap(i,j), if s[i] = s2[i] or s1[j] = s2[j], dont swap
// at most len - 1 swaps

// regardless of the order of swaps in the optimal solution,
// the 1st index s.t s1[index] != s2[index] needs to be swapped out
// and the index j to swap with it, can be any j > index, as long as s1[j] = s2[index]
// even if let say, s1[index] gets its correct character at the 10th swap or something
// so eg.g s1[index] = c, s1[j] = c', c' = s2[index]
// whatever c' is, can do the swap in the 1st move. So in the 1st move, s[index] is c'', swap with c' in s[j']
// hard to prove why this is optimal 

// if s1[j] == s2[j], don't swap (hard to prove)

class Solution {
public:
    unordered_map<string, int> dp;
    string s2;

    int helper(string& s, int index) {
        if (index == s.size()) return 0;
        else if (dp.contains(s)) return dp[s];
        else if (s[index] == s2[index]) {
            int ans = helper(s, index + 1);
            dp[s] = ans;
            return ans;
        } else {
            int best = 999999;
            for (int j = index + 1; j < s.size(); j ++) {
                if (s[j] != s2[j] && s[j] == s2[index]) {
                    swap(s[index], s[j]);
                    best = min(best, 1 + helper(s, index + 1));
                    swap(s[index], s[j]);
                }
            }
            dp[s] = best;
            return best;
        }
    }

    int kSimilarity(string s1, string s2) {
        this->s2 = s2;
        return helper(s1, 0);
    }


};

int main() {
    string s1 = "abcd";
    string s2 = "dcba";
    cout << Solution().kSimilarity(s1, s2);
}