#include <bits/stdc++.h>
using namespace std;

// dp, need use trick to compress state space
// dp(i, j, diff) can we match string from index i of s1 onwards and index j of s2 onwards, with the diff in wildcards
// between s1 and s2 = diff
// so if diff > 0, we have surplus of wildcards in s1, if diff < 0, s2 has surplus
// if diff == 0, then we have to manually match

struct Pair {
    int num, len;
};

class Solution {
public:
    string s1, s2;
    int dp[41][41][2000]; // we only need to track the difference between the num of the 2 strings4
                          // +ve means surplus for s1, i.e is num s1 - num s2

    bool isLetter(char c) {
        int x = c - 'a';
        return x >= 0 && x < 26;
    }

    bool isDigit(char c) {
        int x = c - '0';
        return x >= 0 && x < 10;
    }

    vector<Pair> possibleDigits(int start, bool side) {
        string& s = (side == 0) ? s1 : s2;
        vector<Pair> out;

        for (int x = 1; x <= 3; x ++) {
            if (start + x - 1 >= s.size() || !isDigit(s[start + x - 1])) break;

            int num = stoi(s.substr(start, x));
            out.push_back({num, x});
        }

        return out;
    }

    bool helper(int i, int j, int diff) {
        int actual = diff - 999;
        

        if (i == s1.size() && j == s2.size()) {
            return actual == 0;
        } else if (i == s1.size() && actual <= 0) {
            return false;
        } else if (j == s2.size() && actual >= 0) {
            return false;
        } else if (dp[i][j][diff] != -1) {
            return dp[i][j][diff];
        }

        int& mySol = dp[i][j][diff];
        if (actual == 0) {
            if (isLetter(s1[i]) && isLetter(s2[j])) {
                if (s1[i] == s2[j]) {
                    mySol = helper(i + 1, j + 1, diff);
                } else {
                    return false;
                }
            } else if (isDigit(s1[i]) && isLetter(s2[j])) {
                vector<Pair> poss = possibleDigits(i, 0);
                bool ans = false;
                for (Pair& p : poss) {
                    ans = ans || helper(i + p.len, j, diff + p.num);
                }
                mySol = ans;
            } else if (isLetter(s1[i]) && isDigit(s2[j])) {
                vector<Pair> poss = possibleDigits(j, 1);
                bool ans = false;
                for (Pair& p : poss) {
                    ans = ans || helper(i, j + p.len, diff - p.num);
                }
                mySol = ans;
            } else {
                vector<Pair> poss1 = possibleDigits(i, 0), poss2 = possibleDigits(j, 1);
                bool ans = false;
                for (Pair& p1 : poss1) {
                    for (Pair& p2 : poss2) {
                        ans = ans || helper(i + p1.len, j + p2.len, diff + p1.num - p2.num);
                    }
                }
                mySol = ans;
            }
        } else if (actual > 0) {
            if (isLetter(s2[j])) {
                mySol = helper(i, j + 1, diff - 1);
            } else {
                vector<Pair> poss = possibleDigits(j, 1);
                bool ans = false;
                for (Pair& p : poss) {
                    ans = ans || helper(i, j + p.len, diff - p.num);
                }
                mySol = ans;
            }
        } else {
            if (isLetter(s1[i])) {
                mySol = helper(i + 1, j, diff + 1);
            } else {
                vector<Pair> poss = possibleDigits(i, 0);
                bool ans = false;
                for (Pair& p : poss) {
                    ans = ans || helper(i + p.len, j, diff + p.num);
                }
                mySol = ans;
            }
        }

        return mySol;
    }
    

    bool possiblyEquals(string s1, string s2) {
        for (int i = 0; i < 41; i ++) {
            for (int j = 0; j < 41; j ++) {
                for (int k = 0; k < 2000; k ++) {
                    dp[i][j][k] = -1;
                }
            }
        }
        this->s1 = s1;
        this->s2 = s2;

        bool ans = helper(0, 0, 999);
        return ans;
    }
};

int main() {
    Solution sol;

    string s1 = "internationalization";
    string s2 = "i18n";

    cout << sol.possiblyEquals(s1, s2) << endl;
}