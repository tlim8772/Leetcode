#include <bits/stdc++.h>
using namespace std;

// simple 2 pointer

class Solution {
public:

    bool canSwitch(char c1, char c2) {
        return (c1 == 'z') ? c2 == 'a' : c2 - c1 == 1;
    }
    bool canMakeSubsequence(string str1, string str2) {
        int p1 = 0;
        int p2 = 0;

        while (p1 < str1.size() && p2 < str2.size()) {
            if (str1[p1] == str2[p2] || canSwitch(str1[p1], str2[p2])) {
                p1 ++;
                p2 ++;
            } else {
                p1 ++;
            }
        }

        return (p2 == str2.size());
    }
};

int main() {
    string s1 = "ab";
    string s2 = "d";

    Solution sol;
    cout << sol.canMakeSubsequence(s1, s2) << endl;
}