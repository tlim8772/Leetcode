#include <bits/stdc++.h>
using namespace std;

// algorithm: start from empty subsequence, only continue adding characters until str is not a K sub sequence

class Solution {
public:
    
    int K;
    string S;
    string bestString = "";



    vector<int> getCntArr(string& s, int k) {
        vector<int> cnt(26, 0);
        for (char c : s) {
            cnt[c - 'a'] ++;
        }

        for (int& x : cnt) {
            x = x / k;
        }
        return cnt;
    }

    bool isKSubSeq(string& s, string& sub, int idx, int k) {
        if (k == 0) return true;

        int ptr = 0;
        while (idx < s.size() && ptr < sub.size()) {
            if (s[idx] == sub[ptr]) {
                idx ++;
                ptr ++;
            } else {
                idx ++;
            }
        }

        if (ptr == sub.size()) return isKSubSeq(s, sub, idx, k - 1);

        return false;
    }

    void updateBest(string& sub) {
        if (sub.size() > bestString.size() || (sub.size() == bestString.size() && sub > bestString)) bestString = sub;
    }


    // invariant sub is a valid k sub seq already, so start with empty string
    void helper(vector<int>& cntArr, string& sub) {
        if (sub.size() >= 7) return;

        for (int i = 0; i < 26; i ++) {
            if (cntArr[i] == 0) continue;

            cntArr[i] --;
            sub.append(1, i + 'a');
            
            if (isKSubSeq(S, sub, 0, K)) {
                updateBest(sub);
                helper(cntArr, sub);
            }

            cntArr[i] ++;
            sub.pop_back();
        }
    }

    string longestSubsequenceRepeatedK(string s, int k) {
        S = s;
        K = k;
        vector<int> cntArr = getCntArr(s, k);
        
        string sub = "";
        helper(cntArr, sub);
        return bestString;
    }

};

int main() {
    Solution sol;
    string s = "bbabbabbbbabaababab";
    string sub = "bbbb";

    cout << sol.isKSubSeq(s, sub, 0, 3) << endl;
    cout << sol.longestSubsequenceRepeatedK(s, 3) << endl;
}