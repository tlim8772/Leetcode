#include <bits/stdc++.h>
using namespace std;

// brute force solution.
// case 1: odd length
// let index i be the center, iterate outwards, so start checking from i - 1, i + 1.
// if encounter a mismatch, we can remove the left or right character.
// case 2: even length
// same but we start checking from i, i + 1 instead.

class Solution {
public:

    int helper(int p1, int p2, bool has_cut, const string& s) {
        if (p1 <= -1 && p2 >= s.size()) {
            return 0;
        }

        // if have not cut, we can add 1 element at the left or right end
        if (p1 <= -1 && p2 < s.size() || p1 > -1 && p2 >= s.size()) {
            return has_cut ? 0 : 1;
        }

        if (s[p1] == s[p2]) {
            return 2 + helper(p1 - 1, p2 + 1, has_cut, s);
        } 

        if (has_cut) {
            return 0;
        }

        return 1 + max(helper(p1 - 1, p2, true, s), helper(p1, p2 + 1, true, s));
    }
    
    
    int almostPalindromic(string s) {
        int best = 1;
        for (int i = 0; i < s.size(); i++) {
            int odd = 1 + helper(i - 1, i + 1, false, s);
            int even = (i < s.size() -1 ) ? helper(i, i + 1, false, s) : 0;
            best = max({best, odd, even});
        }
        return best;
    }
};

int main() {
    Solution sol;
    string s = "abca";
    cout << sol.almostPalindromic(s) << endl;
}

