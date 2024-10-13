#include <bits/stdc++.h>
using namespace std;

// we want to know when to use to use the wildcard
// let ptr be the idx of s we are matching right now, and i be the idx of the start of pattern we are starting
// if suffix of patt starting at i + 1 can be match using suffix of s starting at ptr + 1
// then to get the lexicographically shortest solution, we need to use the wildcard now
// if not, we can replace the idx that patt[i] gets used with to ptr which is smaller

// if cannot, then we cannot use the wildcard. We increment ptr until s[ptr] = pattern[i] and continue

class Solution {
public:
    vector<int> canDo; // canDo[i]: stores the earliest index pattern[i] can be matched to, -1 if cannot

    void helper1(string& s, string& patt) {
        int ptr = s.size();
        for(int i = patt.size() - 1; i >= 0; i --) {
            while (ptr >= 0 && s[ptr] != patt[i]) {
                ptr --;
            }

            canDo[i] = ptr;
            ptr --;
        }
    }

    vector<int> helper2(string& s, string& patt) {
        vector<int> out;
        
        int ptr = 0;
        bool used = false;
        for (int i = 0; i < patt.size(); i ++) {
            if (ptr >= s.size()) {
                out.push_back(ptr);
            } else if (used) {
                while (ptr < s.size() && s[ptr] != patt[i]) {
                    ptr ++;
                }
                out.push_back(ptr);
                ptr ++;
            } else if (i == patt.size() - 1) {
                // reached last char, and have not used wildcard
                out.push_back(ptr);
                ptr ++;
            } else if (s[ptr] == patt[i]) {
                // just take, best case already
                out.push_back(ptr);
                ptr ++;
            } else if (canDo[i + 1] >= ptr + 1) {
                // can use wildcard, so just use so as to make lexicographically smallest sequence
                out.push_back(ptr);
                used = 1;
                ptr ++;
            } else {
                while (ptr < s.size() && s[ptr] != patt[i]) {
                    ptr ++;
                }
                out.push_back(ptr);
                ptr ++;
            }
        }

        if (out[out.size() - 1] >= s.size()) out.clear();
        return out;
    }

    vector<int> validSequence(string word1, string word2) {
        canDo = vector(word2.size(), -1);
        helper1(word1, word2);
        return helper2(word1, word2);
    }

};

int main() {
    string word1 = "ghh";
    string word2 = "xy";
    Solution sol;
    vector<int>&& ans = sol.validSequence(word1, word2);
    for (int x : ans) {
        cout << x << " ";
    }
    cout << endl;
}