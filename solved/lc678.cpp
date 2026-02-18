#include <bits/stdc++.h>
using namespace std;

// dp(num of '(', idx we are starting from).
// if we encounter *, we can +1 to '(' (i.e treat as '(') or -1 (i.e treat it as ')')
// or do nothing.
// if encounter ')', -1 to # of '(' or return false if count is 0.
// if encounter '(', +1 to # of '('.

struct Hash {
    size_t operator()(const tuple<int,int>& tup) const {
        auto [a, b] = tup;
        return (a << 7) + b;
    }
};

class Solution {
public:
    unordered_map<tuple<int,int>, bool, Hash> store;

    bool dp(int l, int i, const string& s) {
        if (store.contains({l, i})) return store[{l, i}];
        if (i == s.size()) {
            return l == 0;
        }

        bool& ans = store[{l, i}];
        if (s[i] == '(') {
            return ans = dp(l + 1, i + 1, s);
        } else if (s[i] == ')') {
            return ans = (l == 0) ? false : dp(l - 1, i + 1, s);
        } else {
            bool as_left = dp(l + 1, i + 1, s);
            bool as_right = (l == 0) ? false : dp(l - 1, i + 1, s);
            bool nothing = dp(l, i + 1, s);
            return ans = as_left || as_right || nothing;
        }
    }

    bool checkValidString(string s) {
        return dp(0, 0, s);
    }
};

int main() {
    Solution sol;
    string s = "*)()";
    bool ans = sol.checkValidString(s);
    cout << ans << endl;
}