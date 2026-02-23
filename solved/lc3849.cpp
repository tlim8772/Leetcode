#include <bits/stdc++.h>
using namespace std;

// get the # of 0s and 1s in t.
// then for s, iterate from left to right (most significant bit to least significant).
// greedily make the most significant bit 1 as much as possible.

class Solution {
public:
    string maximumXor(string s, string t) {
        array<int, 2> t_count{0};
        for (char c : t) t_count[c - '0']++;

        string out;
        auto& [zeros, ones] = t_count;
        for (char c : s) {
            if (c == '0') {
                if (ones > 0) {
                    ones--;
                    out.push_back('1');
                } else {
                    zeros--;
                    out.push_back('0');
                }
            } else {
                if (zeros > 0) {
                    zeros--;
                    out.push_back('1');
                } else {
                    ones--;
                    out.push_back('0');
                }
            } 
        }

        return out;
    }
};

int main() {
    Solution sol;
    string s = "101";
    string t = "011";
    string ans = sol.maximumXor(s, t);
    cout << ans << endl;
}