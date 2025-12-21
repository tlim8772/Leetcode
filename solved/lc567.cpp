#include <bits/stdc++.h>
using namespace std;

// use 2 pointer.
// since we want permutation of s1 as a substring of s2, we keep a freq map of the characters of s1.
// we want to check for each index i of s2, can a substring have the same character frequency.
// however, suppose we fail at index j when checking index i, for index i + 1, we can start checking from 
// index j, not index i + 1.

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        vector<int> freq(26, 0);
        for (char c : s1) freq[c - 'a']++;

        int p1 = 0, p2 = 0;
        while (p1 < s2.size()) {
            if (p2 < p1) p2 = p1;

            while (p2 < s2.size()) {
                int& cnt = freq[s2[p2] - 'a'];
                if (cnt > 0) {
                    cnt--;
                    p2++;
                } else {
                   break; 
                }
            } 

            if (p2 - p1 == s1.size()) {
                return true;
            } else {
                if (p2 > p1) freq[s2[p1] - 'a']++;
                p1++;
            }
        }

        return false;
    }
};

int main() {
    Solution sol;
    string s1 = "adc";
    string s2 = "dcda";
    cout << sol.checkInclusion(s1, s2) << endl;
}