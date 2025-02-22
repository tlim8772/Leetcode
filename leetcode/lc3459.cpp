#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int R, C;
    vector<vector<int>> grid;
    vector<vector<int>> DIRS = {{-1, -1}, {-1, 1}, {1, 1}, {1, -1}};
    vector<vector<int>> dp; // dp[r * C + c][dir][can turn or not]

    inline int coor(int r, int c) {
        return r * C + c;
    }

    inline bool valid(int r, int c) {
        return r >= 0 && r < R && c >= 0 && c < C;
    }

    inline int coor2(int dir, int canTurn) {
        return dir * 2 + canTurn;
    }

   

    
    // grid[r][c] is either 2 or 0
    int helper(int r, int c, int dir, int canTurn) {
        if (dp[coor(r, c)][coor2(dir, canTurn)] != -1) {
            return dp[coor(r, c)][coor2(dir, canTurn)];
        } else if (!canTurn) {
            const vector<int>& Dir = DIRS[dir];
            int nr = r + Dir[0];
            int nc = c + Dir[1];
            int ans = 1;

            if (!valid(nr, nc)) {
                ans = 1;
            } else if ((grid[r][c] == 0 && grid[nr][nc] == 2) || (grid[r][c] == 2 && grid[nr][nc] == 0)) {
                ans = 1 + helper(nr, nc, dir, 0);
            } 

            dp[coor(r, c)][coor2(dir, 0)] = ans;
            return ans;
        } else {
            int ans = 1;

            // no turn
            vector<int> Dir = DIRS[dir];
            int nr1 = r + Dir[0];
            int nc1 = c + Dir[1];

            if (!valid(nr1, nc1)) {
                ans = max(ans, 1);
            } else if ((grid[r][c] == 0 && grid[nr1][nc1] == 2) || (grid[r][c] == 2 && grid[nr1][nc1] == 0)) {
                ans = max(ans, 1 + helper(nr1, nc1, dir, 1));
            }

            // turn
            const vector<int>& Dir2 = DIRS[(dir + 1) % 4];
            int nr2 = r + Dir2[0];
            int nc2 = c + Dir2[1];
            
            if (!valid(nr2, nc2)) {
                ans = max(ans, 1);
            } else if ((grid[r][c] == 0 && grid[nr2][nc2] == 2) || (grid[r][c] == 2 && grid[nr2][nc2] == 0)) {
                ans = max(ans, 1 + helper(nr2, nc2, (dir + 1) % 4, 0));
            }

            dp[coor(r, c)][coor2(dir, 1)] = ans;
            return ans;

        }
    }

    int lenOfVDiagonal(vector<vector<int>>& grid) {
        R = grid.size(); C = grid[0].size();
        this->grid = std::move(grid);
        dp = vector(R * C, vector(8, -1));

        int best = 0;

        for (int r = 0; r < R; r ++) {
            for (int c = 0; c < C; c ++) {
                if (this->grid[r][c] != 1) continue;
                
                best = max(best, 1);
                for (int i = 0; i < 4; i ++) {
                    const vector<int>& Dir = DIRS[i];
                    int nr = r + Dir[0];
                    int nc = c + Dir[1];
                    
                    if (!valid(nr, nc) || this->grid[nr][nc] != 2) continue;

                    int res = 1 + helper(nr, nc, i, 1);
                    //cout << res << endl;
                    best = max(best, res);
                }
            }
        }

        return best;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> grid = {{2,2,1,2,2},{2,0,2,2,0},{2,0,1,1,0},{1,0,2,2,2},{2,0,0,2,2}};

    cout << sol.lenOfVDiagonal(grid) << endl;
}