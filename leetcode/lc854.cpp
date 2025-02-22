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
// so eg. s1[index] = c, s1[j] = c', c' = s2[index]
// whatever c' is, can do the swap in the 1st move. So in the 1st move, s[index] is c'', swap with c' in s[j']
// now whatever op c' is in, replace with c''

// suppose there are some ops using c'' befor 1st op with c', in original solution. In original solution, whatever
// op c'' is in, the other party is wrong so is c'' that goes into correct position. So after swapping c' and c''
// modified solution, it is simply c'' that is in a different pos, swap as per normal, just that other party goes to a different
// pos, which is the original pos of c'. That party takes over c'

// if it is op with c' that comes 1st, no problem, replace c' with c'', or whatver that has replaceed c'. 

// bottom line is whatever party that replaces c', and goes to different pos, in original solution is supposed to go
// to pos index, but now goes to the pos of c' in the original solution. So finally when c and c' switched in original position,
// c somehow got to pos index, so now it has to be in the orignal solution of c', which means we have ended up in the same state.





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