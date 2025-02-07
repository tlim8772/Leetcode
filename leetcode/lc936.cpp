#include <bits/stdc++.h>
using namespace std;

// work from the back.
// last stamp must match all characters. So replace them with ????
// now ? is like a wildcard, can match any char

// we can greedily erase the 1st match found. Suppose we do not, and the string is still solvable,
// but making characters into wildcards make the remaining string easier to stamp out, so just take it.

// furthermore, each indices to stamp is used only once. If used twice, the earlier stamp is useless, can remove

// TC is O(n^3) (each removal add at least 1 to cnt, iteratiing all indices to check for match if O(n^2))
// but still pass

class Solution {
public:
    bool canMatch(string& stamp, string& target, int idx) {
        if (idx + stamp.size() - 1 >= target.size()) return false;

        for (int i = 0; i < stamp.size(); i ++) {
            if (target[idx + i] != '?' && stamp[i] != target[idx + i]) return false;
        }
        
        return true;

    }

    vector<int> movesToStamp(string stamp, string target) {
        int cnt = 0;
        vector<bool> usedIdx(target.size(), false);
        vector<int> indices;

        while (cnt < target.size()) {
        bool found = false;
            for (int i = 0; i < target.size(); i ++) {
                if (usedIdx[i]) continue;

                if (canMatch(stamp, target, i)) {
                    found = true;
                    usedIdx[i] = true;
                    indices.push_back(i);
                    
                    for (int j = 0; j < stamp.size(); j ++) {
                        if (target[i + j] != '?') cnt ++;
                        target[i + j] = '?';
                    }
                }
            }

            if (!found) break;

        }

        if (cnt < target.size()) {
            return {};
        } else {
            reverse(indices.begin(), indices.end());
            return indices;
        }


    }

};

int main() {
    string s = "abca";
    string t = "aabcaca";

    Solution sol;
    vector<int> ans = sol.movesToStamp(s, t);
    for (int x : ans) cout << x << " "; 
}