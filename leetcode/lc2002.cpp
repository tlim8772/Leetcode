#include <bits/stdc++.h> 
using namespace std;

class Solution {
public:
    vector<vector<vector<int>>>* dp;

    int helper(int s, int e, int bitMask, string& word) {
        //cout << ((bitMask >> s) & 1)  << endl;
        if (s > e) {
            return 0;
        } else if (s == e) {
            // 1 char left only
            return (bitMask >> s) & 1;
        } else if ((*dp)[bitMask][s][e] != -1) {
            return (*dp)[bitMask][s][e];
        } else if (((bitMask >> s) & 1) == 0) {
            
            int ans = helper(s + 1, e, bitMask, word);
            (*dp)[bitMask][s][e] = ans;
            return ans;
        } else if (((bitMask >> e) & 1) == 0) {
            int ans = helper(s, e - 1, bitMask, word);
            (*dp)[bitMask][s][e] = ans;
            return ans;
        } else if (word[s] == word[e]) {
            int ans = 2 + helper(s + 1, e - 1, bitMask, word);
            (*dp)[bitMask][s][e] = ans;
            return ans;
        } else {
            int maybeUseS = helper(s, e - 1, bitMask, word);
            int maybeUseE = helper(s + 1, e, bitMask, word);
            int ans = max(maybeUseE, maybeUseS);
            (*dp)[bitMask][s][e] = ans;
            return ans;
        }
    }

    int maxProduct(string s) {
        int maxBM = (1 << s.size());
        dp = new vector(maxBM, vector(s.size(), vector(s.size(), -1)));
        int maxRes = 0;
        for (int i = 0; i < maxBM; i ++) {
            int setA = helper(0, s.size() - 1, i, s);
            int bm = (~i) & (maxBM - 1);
            int setB = helper(0, s.size() - 1, bm, s);
            int ans = setA * setB;
            //cout << i << " " << bm << " " << setA << " " << setB << endl;
            maxRes = max(maxRes, ans);
            
        }
        return maxRes;
    }
};

int main() {
    Solution sol;
    string s = "bb";
    cout << sol.maxProduct(s) << endl;
    /*sol.dp = new vector(16, vector(4, vector(4, -1)));
    cout << sol.helper(0, 3, 0b0000, s);*/
    return 0;
}