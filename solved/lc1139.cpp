#include <bits/stdc++.h>
using namespace std;

// very easy, for each coor (x, y) get the longest 1 range in direction up, right, down, left
// then we can query (x, y, len) in O(1)
// so total time complexity is O(10^6)

class Solution {
public:
    int R, C;

    int DIRS[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
    int store[100][100][4];

    bool valid(int r, int c) {
        return r >= 0 && r < R && c >= 0 && c < C;
    }

    int helper(int r, int c, int dir[2], vector<vector<int>>& grid) {
        int cnt = 0;
        while (1) {
            if (!valid(r, c) || grid[r][c] == 0) break;
            cnt ++;
            r += dir[0];
            c += dir[1];
        }
        return cnt;
    }

    void process(vector<vector<int>>& grid) {
        for (int r = 0; r < R; r ++) {
            for (int c = 0; c < C; c ++) {
                for (int i = 0; i < 4; i ++) {
                    store[r][c][i] = helper(r, c, DIRS[i], grid);
                }
            }
        }
    }

    // find largest 1-border square, with (r, c) as the top left corner
    int largestSquare(int r, int c) {
        int (&res)[4] = store[r][c];
        int MAX = min(res[1], res[2]);
        
        for (int l = MAX; l >= 1; l --) {
            int nr = r + l - 1, nc = c + l - 1;
            if (!valid(nr, nc)) continue;

            int (&resN)[4] = store[nr][nc];
            int MAX_N = min(resN[0], resN[3]);

            if (MAX_N >= l) return l;

        }

        return 0;
    }

    int largest1BorderedSquare(vector<vector<int>>& grid) {
        R = grid.size(); C = grid[0].size();
        process(grid);
        
        int best = 0;
        for (int r = 0; r < R; r ++) {
            for (int c = 0; c < C; c ++) {
                int ans = largestSquare(r, c);
                best = max(best, ans);
            }
        }
        return best * best;
    }

    

};

int main() {
    Solution sol;
    vector<vector<int>> grid = {{1,1,1}};

    int ans = sol.largest1BorderedSquare(grid);
    cout << ans << endl;
}