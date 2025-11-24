#include <bits/stdc++.h>
using namespace std;

// use sliding windows
class Solution {
public:
    bool isValid(vector<int>& counts, int k) {
        return accumulate(counts.begin(), counts.end(), false, [k](bool accu, int cnt) {return accu || cnt >= k;});
    }

    int numberOfSubstrings(string s, int k) {
        int res = 0;

        vector<int> counts(26, 0);
        int p0 = 0;
        int p1 = 0;
        counts[s[0] - 'a'] ++;

        while (true) {
            if (isValid(counts, k)) {
                res += (s.size() - p1);
                counts[s[p0] - 'a'] --;
                p0 ++;
            } else {
                if (p1 < s.size() - 1) {
                    counts[s[p1 + 1] - 'a'] ++;
                    p1 ++;
                } else {
                    break;
                }
            }
        }

        return res;

    }
};

int main() {
    Solution sol;
    string s = "abcde";
    cout << sol.numberOfSubstrings(s, 2) << endl;
}