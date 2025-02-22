#include <vector>
#include <iostream>
#include <stdio.h>
using namespace std;

// bottom up dp + optimisation by resuing the best next right and best next bottom result

class Solution {
public:
    int get(vector<vector<int>>& grid, int x, int y) {
        if (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size()) {
            return 0;
        }
        return grid[x][y];
    }

    bool check(vector<vector<int>>& grid, int x, int y) {
        return (x < 0 || y < 0 || x >= grid.size() || y >= grid[0].size()) ? false : true;
    }

    int getMax(vector<vector<int>>& grid) {
        int m = -999999999;
        for (int i = 0; i < grid.size(); i ++) {
            for (int j = 0; j < grid[0].size(); j ++) {
                if (i != grid.size() - 1 || j != grid[0].size()) m = max(m, grid[i][j]);
            }
        }
        return m;
    }

    void print(vector<vector<int>> grid) {
        for (int i = 0; i < grid.size(); i ++) {
            for (int j = 0; j < grid[0].size(); j ++) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }
    int maxScore(vector<vector<int>>& grid) {
        vector<vector<int>> dp = vector(grid.size(), vector(grid[0].size(), 0));
        vector<vector<int>> maxRows = vector(grid.size(), vector(grid[0].size(), 0));
        vector<vector<int>> maxCols = vector(grid.size(), vector(grid[0].size(), 0));
        int maxScore = 0;
        int k = grid.size() + grid[0].size() - 2;
        for (; k >= 0; k --) {
            for (int x = 0; x <= k; x ++) {
                int y = k - x;
                if (!check(grid, x, y)) continue;
                int maxRight = (y == grid[0].size() - 1) ? -999999999 : maxRows[x][y + 1];
                int maxBottom = (x == grid.size() - 1) ? -999999999 : maxCols[x + 1][y];
                dp[x][y] = max(maxRight, maxBottom);
                maxScore = max(dp[x][y], maxScore);
                if (check(grid, x, y - 1)) {
                    int op2 = (y == grid[0].size() - 1) ? -999999999 : maxRows[x][y + 1] + grid[x][y] - grid[x][y - 1]; 
                    int op1 = (x == grid.size() - 1 && y == grid[0].size() - 1) ? grid[x][y] - grid[x][y - 1] : dp[x][y] + grid[x][y] - grid[x][y - 1];
                    int op3 =  grid[x][y] - grid[x][y - 1]; // i.e just go from grid[x][y - 1] to grid[x][y]
                    maxRows[x][y] = max(max(op3, op1), op2);
                }
                if (check(grid, x - 1, y)) {
                    int op2 = (x == grid.size() - 1) ? -999999999 : maxCols[x + 1][y] + grid[x][y] - grid[x - 1][y];
                    int op1 = (x == grid.size() - 1 && y == grid[0].size() - 1) ? grid[x][y] - grid[x - 1][y] : dp[x - 1][y] + grid[x][y] - grid[x - 1][y];
                    int op3 = grid[x][y] - grid[x - 1][y];
                    maxCols[x][y] = max(max(op3, op1), op2);
                }

            }
        }
        print(dp);
        return getMax(dp);
    }
};

int main() {
    vector<vector<int>> nums = {{9,5,7,3},{8,9,6,1},{6,7,14,3},{2,5,3,1}};
     vector<vector<int>> nums2 ={{6,10,7},{5,9,4}};
    Solution sol;
    cout << sol.maxScore(nums2);
}