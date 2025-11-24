#include <bits/stdc++.h>
using namespace std;

// the insight is that we cannot have (remove 1 in the middle) (remove 1 by removing the sides until we reach this) (remove 1 in the middle)
// so it is simply (remove from sides) (remove from middle) (remove from sides)

// we use the minRight calculated for i + 1 to optimise calculation for i 
// basically minRight[i + 1] is simply min cost to remove all 1s from i + 2 to end
// where the 1 cost op is only when we remoev from the right

// at iteration i
// supoose we are set on removing indices 0 to i at a cost i + 1 (if there is at least 1 '1' in s[0..i])
// if s[i + 1] is 0, then just add minRight[i + 1]
// if not, it is just min(2 + minRight[i + 1], s.size() - (i + 1))

class Solution {
public:
    vector<int> store;

    int minimumTime(string s) {
        

        // minRight[i] contains min cost to remove all '1's from i + 1 to s.size() - 1
        // where the 1 cost op is only when we remove from the right
        vector<int> minRight(s.size(), 0); 

        vector<bool> hasLeft1(s.size(), false);
        hasLeft1[0] = (s[0] == '1');
        for (int i = 1; i < s.size(); i ++) hasLeft1[i] = (s[i] == '1') || hasLeft1[i - 1];

        int res = hasLeft1[s.size() - 1] ? s.size() : 0;

        minRight[s.size() - 1] = (s[s.size() - 1] == '0') ? 0 : 1;

        for (int i = s.size() - 2; i >= 0; i --) {
            int ans = (hasLeft1[i]) ? i + 1 : 0;
            if (s[i + 1] == '0') {
                ans += minRight[i + 1];
                minRight[i] = (s[i] == '0') ? minRight[i + 1] : min((int) s.size() - 1, 2 + minRight[i + 1]);
            } else {
                
                ans += min((int) s.size() - (i + 1), 2 + minRight[i + 1]);
                minRight[i] = (s[i] == '0') ? minRight[i + 1] : min(2 + minRight[i + 1], (int) s.size() - i);
            }
            //cout << ans << endl;
            res = min(res, ans);
        }

        //for (int x : minRight) cout << x << " ";
        //cout << endl;
        return res;
    }
};

int main() {
    Solution sol;
   
    cout << sol.minimumTime("011001111111101001010000001010011") << endl;
}
