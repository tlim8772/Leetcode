#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numSteps(string s) {
        int cnt = 0;
        for (int i = s.size() - 1; i > 0;) {
            if (s[i] == '0') {
                cnt++;
                i--; 
            } else {
                int end = i;
                while (i >= 0 && s[i] == '1') {
                    i--;
                }
                if (i > -1) s[i] = '1';
                cnt += 1 + (end - i);
            }
        }
        return cnt;
    }
};

int main() {
    Solution sol;
    string s = "11001";
    cout << sol.numSteps(s) << endl;
}