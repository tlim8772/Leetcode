#include <bits/stdc++.h>
using namespace std;

// stupid question
// 1st fill in characters for 'T'

// now for 'F', we iterate from left to right.
// we find the rightmost index that we can change (it can be filled already), call it Idx.
// we check whether there exists a diff char already. If have, fill empty char (denoted by '$') with 'a'
// if not, we make char at Idx 'a' if the corresponding char in s2 is 'b..z' or 'b' if it is 'a'

// special case when for 'F', we have all chars not filled yet
// if str2 is not all 'a', fill everything as 'a'
// if not, get rightmost index we can change, make it 'b', everything else is 'a'

class Solution {
public:
    string res;
    vector<bool> cannotChange;

    bool isS2Alla = true;

    bool canProcessT(const string& s1, const string& s2) {
        for (int i = 0; i < s1.size(); i ++) {
            if (s1[i] == 'F') continue;

            for (int j = 0; j < s2.size(); j ++) {
                cannotChange[i + j] = true;
                
                if (res[i + j] == '$') {
                    res[i + j] = s2[j];
                } else if (res[i + j] != s2[j]) {
                    return false;
                }
            }
        }

        return true;
    }

    int findMaxCanChange(int i, int len) {
        int best = -1;
        for (int j = i; j < i + len; j ++) {
            if (!cannotChange[j]) best = j;
        }
        return best;
    }

    inline bool isAllEmpty(int i, int len) {
        for (int j = i; j < i + len; j ++) {
            if (res[j] != '$') {
                return false;
            }
        }
        return true;
    }



    bool haveDiffChar(int i, const string& s2) {
        for (int j = i; j < i + s2.size(); j ++) {
            if (res[j] != '$' && res[j] != s2[j - i]) return true;
        }
        return false;
    }

    bool canProcessF(const string& s1, const string& s2) {
        for (int i = 0; i < s1.size(); i ++) {
            if (s1[i] == 'T') continue;

            bool haveDiff = haveDiffChar(i, s2);
            int maxChange = findMaxCanChange(i, s2.size());
            bool allEmpty = isAllEmpty(i, s2.size());

           
            
            if (haveDiff) {
                // have existing diff, put remaining slots as 'a'
                for (int j = i; j < i + s2.size(); j ++) {
                    if (res[j] != '$') continue;
                    res[j] = 'a';
                }
            } else if (maxChange == -1) {
                // no diff char, and cannot change anything
                return false;
            } else if (!allEmpty) {
                // noo diff char, so change the rightmost index to something different
                res[maxChange] = (s2[maxChange - i] == 'a') ? 'b' : 'a';
                for (int j = i; j < i + s2.size(); j ++) {
                    if (res[j] != '$') continue;
                    res[j] = 'a';
                }
            } else {
                for (int j = i; j < i + s2.size(); j ++) {
                    res[j] = 'a';
                }

                if (isS2Alla) res[maxChange] = 'b';
            }
        }
        
        return true;
    }

    string generateString(string str1, string str2) {
        for (char c : str2) {
            if (c != 'a') {
                isS2Alla = false;
                break;
            }
        }
        
        
        
        res = string(str1.size() + str2.size() - 1, '$');
        cannotChange = vector(res.size(), false);

        bool chk1 = canProcessT(str1, str2);
        if (!chk1) return "";

        cout << "pass 1" << endl;
        bool chk2 = canProcessF(str1, str2);
        if (!chk2) return "";

        return res;
    }

};

int main() {
    Solution sol;

    string str1 = "F";
    string str2 = "da";

    cout << sol.generateString(str1, str2) << endl;
}