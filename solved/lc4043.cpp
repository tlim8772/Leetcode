#include <bits/stdc++.h>
using namespace std;

// just brute force.

class Solution {
public:
    int countRotations(string s, int k) {
        int len = s.size();
        int cnt = 0;
        for (int start = 0; start < len; start++) {
            int c = 0;
            for (int i = 0; i < len - 1; i++) {
                int curr = (start + i) % len;
                int next = (curr + 1) % len;
                c += s[curr] == s[next];
                if (c > k) break;
            }
            cnt += c == k;
        }
        return cnt;
    }
};

int main() {
    Solution sol;
    string s = "aab";
    int k = 1;
    int ans = sol.countRotations(s, k);
    cout << ans << endl;
}