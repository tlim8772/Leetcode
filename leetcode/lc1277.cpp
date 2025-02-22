#include <bits/stdc++.h>

using namespace std;

class Solution {
    public:
        vector<vector<int>>* dp;

        int helper(int x, int y, vector<vector<int>>& matrix) {
            if (x < 0 || x >= matrix.size() || y < 0 || y >= matrix[0].size()) {
                return 0;
            } else if ((*dp)[x][y] != -1) {
                return (*dp)[x][y];
            } else if (matrix[x][y] == 0) {
                return 0;
            } else {
                int a = helper(x, y + 1, matrix);
                int b = helper(x + 1, y + 1, matrix);
                int c = helper(x + 1, y, matrix);
                int len = min(a, min(b, c));
                (*dp)[x][y] = len + 1;
                return len + 1;
            }
        }

        int countSquares(vector<vector<int>>& matrix) {
            dp = new vector(matrix.size(), vector(matrix[0].size(), -1));
            int count = 0;
            for (int x = 0; x < matrix.size(); x ++) {
                for (int y = 0; y < matrix[0].size(); y ++) {
                    int ans =  helper(x, y, matrix);
                    //cout << x << " " << y << " " << ans << endl;
                    count += ans;
                }
            }
            return count;
        }
};

int main() {
    Solution s;
    vector<vector<int>> x = {{0,1,1,1},{1,1,1,1},{0,1,1,1}};
    cout << s.countSquares(x) << endl;
    return 0;
}



