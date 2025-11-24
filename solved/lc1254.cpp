#include <bits/stdc++.h>
using namespace std;

// count number of 0 connected components, then count number of 0 CC that lie on the edge

struct UnionFind {
    vector<int> ps;
    vector<int> ws;

    UnionFind(int n): ps(n, 0), ws(n, 1) {
        for (int i = 0; i < n; i ++) ps[i] = i;
    }

    int find(int v) {
        if (ps[v] == v) return v;
        ps[v] = find(ps[v]);
        return ps[v];
    }

    void join(int u, int v) {
        int pu = find(u), pv = find(v);
        if (pu == pv) return;

        if (ws[pv] < ws[pu]) {
            ws[pu] += ws[pv];
            ps[pv] = pu;
        } else {
            ws[pv] += ws[pu];
            ps[pu] = pv;
        }
    }

    int numCC() {
        int sum = 0;
        for (int i = 0; i < ps.size(); i ++) {
            if (ps[i] == i) sum ++;
        }
        return sum;
    }
};

class Solution {
public:
    int R, C;
    vector<vector<int>> DIRS = {{-1,0},{0,1},{1,0},{0,-1}};

    inline int coor(int r, int c) {
        return r * C + c;
    }

    inline bool valid(int r, int c) {
        return r >= 0 && r < R && c >= 0 && c < C;
    }

    int closedIsland(vector<vector<int>>& grid) {
        R = grid.size(), C = grid[0].size();
        UnionFind uf(grid.size() * grid[0].size());

        for (int r = 0; r < R; r ++) {
            for (int c = 0; c < C; c ++) {
                if (grid[r][c] == 1) continue;

                for (vector<int>& dir : DIRS) {
                    int nr = r + dir[0], nc = c + dir[1];
                    if (!valid(nr, nc) || grid[nr][nc] == 1) continue;
                    uf.join(coor(r, c), coor(nr, nc));
                }
            }
        }

        int cc = 0;
        for (int r = 0; r < R; r ++) {
            for (int c = 0; c < C; c ++) {
                int pos = coor(r, c);
                if (grid[r][c] == 0 && uf.find(pos) == pos) cc ++;
            }
        }
        
        int notCount = 0;
        vector<bool> taken(R * C, false);
        for (int c = 0; c < C; c ++) {
            int i1 = coor(0, c);
            if (grid[0][c] == 0) {
                int p = uf.find(i1);
                if (!taken[p]) {
                    notCount ++;
                    taken[p] = true;
                }
            }

            int i2 = coor(R - 1, c);
            if (grid[R - 1][c] == 0 && R > 1) {
                int p = uf.find(i2);
                if (!taken[p]) {
                    notCount ++;
                    taken[p] = true;
                }
            }

        }
        //cout << notCount << endl;

        for (int r = 1; r < R - 1; r ++) {
            int i1 = coor(r, 0);
            if (grid[r][0] == 0) {
                int p = uf.find(i1);
                if (!taken[p]) {
                    notCount ++;
                    taken[p] = true;
                }
            }

            int i2 = coor(r, C - 1);
            if (C > 1 && grid[r][C - 1] == 0) {
                int p = uf.find(i2);
                if (!taken[p]) {
                    notCount++;
                    taken[p] = true;
                }
            }
            
        }

        //cout << cc << " " << notCount << endl;
        return cc - notCount;


    }
};

int main() {
    Solution sol;

    vector<vector<int>> grid = {{0,0,1,1,0,1,0,0,1,0},{1,1,0,1,1,0,1,1,1,0},{1,0,1,1,1,0,0,1,1,0},{0,1,1,0,0,0,0,1,0,1}};
    cout << sol.closedIsland(grid) << endl;
}