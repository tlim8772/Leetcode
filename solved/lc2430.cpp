#include <bits/stdc++.h>
using namespace std;

// use z algo and dp.
// z algo is to find whether we can cut to s[i].

// we do dp from right to left.
// suppose at index i, z algo for s[i:] is [3,0,0,4]
// we can cut to dp(i + 3), since z_algo[3] >= 3.

vector<int> z_algo(string s) {
    vector<int> out(s.size(), s.size());
    int l = 1, r = 1;

    for (int i = 1; i < s.size(); i++) {
        if (i >= r) {
            l = i, r = i;
            while (r < s.size() && s[r] == s[r - l]) r++;
            out[i] = r - l;
        } else {
            int prev = out[i - l];
            if (i + prev <= r) {
                out[i] = prev;
            } else {
                l = i;
                while (r < s.size() && s[r] == s[r - l]) r++;
                out[i] = r - l;
            }
        }
    }

    return out;
}

class Solution {
public:
    int deleteString(string s) {
        vector<int> store(s.size(), -1);
        store[store.size() - 1] = 1;

        for (int i = s.size() - 2; i > -1; i--) {
            vector<int> z_res = z_algo(string(s.begin() + i, s.end()));
            int best = 1;

            for (int j = 0; j < z_res.size(); j++) {
                if (z_res[j] >= j) {
                    best = max(best, 1 + store[i + j]);
                }
            }

            store[i] = best;
        }

        return store[0];
    }
};

int main() {
    Solution sol;
    string s = "abcabcdabc";
    cout << sol.deleteString(s) << endl;
}