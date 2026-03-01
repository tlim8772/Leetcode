#include <bits/stdc++.h>
using namespace std;

// we iterate from left to right.
// at index i, we get char c, we check the previous char c position.
// if the difference is <= k, we remove this char.
// since we merge right to left, the positions of previous characters do not change.
// there will be no merges of previous characters, we can just continue right.

class Solution {
public:
    string mergeCharacters(string s, int k) {
        vector<int> store(26, -1);
        string out = "";
        for (char c : s) {
            int& prev = store[c - 'a'];
            if (prev == -1 || out.size() - prev > k) {
                prev = out.size();
                out.push_back(c);
            }
            // else, we can merge this character with the prev same character.
        }
        return out;
    }
};

int main() {
    Solution sol;
    string s = "yybyzybz";
    int k = 2;
    string ans = sol.mergeCharacters(s, k);
    println("Ans: {}", ans);
}