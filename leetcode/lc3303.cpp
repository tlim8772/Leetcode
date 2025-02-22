#include <bits/stdc++.h>
using namespace std;

// for each index i, dp1[i] = longest substring starting at i that matches the prefix of pattern
// dp2[i] = longest substring ending at i that matches a suffix of pattern
// for each i, if i + dp1[i] - 1 >= i + pattern.length - 1 - dp2[i + pattern.length - 1] + 1, then it is suitable

class Solution {
public:
    vector<int> z_function(string s) {
        int n = s.size();
        vector<int> z(n);
        int l = 0, r = 0;
        for(int i = 1; i < n; i++) {
            if(i < r) {
                z[i] = min(r - i, z[i - l]);
            }
            while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
                z[i]++;
            }
            if(i + z[i] > r) {
                l = i;
                r = i + z[i];
            }
        }
        return z;
    }

    int minStartingIndex(string s, string pattern) {
        vector<int> dp1 = z_function(pattern + "#" + s);
        dp1 = vector(dp1.begin() + pattern.size() + 1, dp1.end());

        reverse(s.begin(), s.end());
        reverse(pattern.begin(), pattern.end());
        
        vector<int> dp2 = z_function(pattern + "#" + s);
        dp2 = vector(dp2.begin() + pattern.size() + 1, dp2.end());
        reverse(dp2.begin(), dp2.end());

        /*for (int i = 0; i < dp1.size(); i ++) {
            cout << dp1[i] << " ";
        }
        cout << endl;

        for (int i = 0; i < dp2.size(); i ++) {
            cout << dp2[i] << " ";
        }
        cout << endl;*/

        for (int i = 0; i + pattern.size() - 1 < s.size(); i ++) {
            if (i + dp1[i] - 1 + 2 >= i + pattern.size() - 1 - dp2[i + pattern.size() - 1] + 1) {
                return i;
            }
        }
        return -1;
    }
};

int main() {
    string s = "";
    string pattern =  "bcdffg";
    Solution sol;
    cout << sol.minStartingIndex(s, pattern);
}