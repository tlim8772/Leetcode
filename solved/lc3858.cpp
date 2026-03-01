#include <bits/stdc++.h>
using namespace std;

// solve greedily.
// try to set the most significant bit to 0.
// then for each row, check if there exists >= 1 number whose most significant bit is 0.
// if have, the most significant bit must be 0, else it must be 1.
// then continue to the next bit, set it to 0, then check the mask (eg 10... if previous result is 1).
// to check if bm_1 is a subset of bm_0, do bm_0 | bm_1 == bm_0.

class Solution {
public:
    int minimumOR(vector<vector<int>>& grid) {
        int bm = 0;
        for (int i = 16; i >= 0; i--) {
            int temp = bm << 1;
            int res = true;
            for (const auto& row : grid) {
                bool ans = any_of(row.begin(), row.end(), [i, temp] (int x) { return ((x >> i) | temp) == temp; });
                if (!ans) {
                    res = false;
                    break;
                }
            }

            bm = (res) ? temp : temp + 1;
        }
        return bm;
    } 
};

int main() {
    Solution sol;
    vector<vector<int>> grid = {{1,5}, {2,4}};
    int ans = sol.minimumOR(grid);
    println("Ans: {}", ans);
}