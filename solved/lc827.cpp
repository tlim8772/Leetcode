#include <bits/stdc++.h>
using namespace std;

// use union find.
// for all 0s, make it 1, see which connected components it joins, then find the new size.

vector<pair<int,int>> DIRS = {{-1,0}, {0,1}, {1,0}, {0,-1}};

struct UnionFind {
    int n;
    vector<int> ps, ws;

    UnionFind(int n): n(n), ps(n, 0), ws(n, 1) {
        for (int i = 0; i < n; i++) ps[i] = i;
    }

    int find(int u) {
        return (ps[u] == u) ? u : ps[u] = find(ps[u]);
    } 

    void join(int u, int v) {
        int pu = find(u), pv = find(v);
        if (pu == pv) return;
        int &wu = ws[pu], &wv = ws[pv];
        if (wu < wv) {
            wv += wu;
            ps[pu] = pv;
        } else {
            wu += wv;
            ps[pv] = pu;
        }
    }
};

class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int R = grid.size(), C = grid[0].size();
        UnionFind uf{static_cast<int>(grid.size() * grid[0].size())};
        
        auto to_pos = [C] (int r, int c) { return r * C + c; };
        auto is_valid = [R, C] (int r, int c) { return r >= 0 && r < R && c >= 0 && c < C; };

        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                if (grid[r][c] == 0) continue;
                
                int my_pos = to_pos(r, c);
                for (auto [dr, dc] : DIRS) {
                    if (!is_valid(r + dr, c + dc)  || grid[r + dr][c + dc] == 0) continue;
                    int next_pos = to_pos(r + dr, c + dc);
                    uf.join(my_pos, next_pos);
                }
            }
        }

        int best = *max_element(uf.ws.begin(), uf.ws.end());
        
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                if (grid[r][c] == 1) continue;

                unordered_set<int> roots;
                for (auto [dr, dc] : DIRS) {
                    if (!is_valid(r + dr, c + dc) || grid[r + dr][c + dc] == 0) continue;
                    roots.insert(uf.find(to_pos(r + dr, c + dc)));
                }

                int sum = 1;
                for (int root : roots) sum += uf.ws[root];
                best = max(best, sum);
            }
        }

        return best;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> grid = {{1,1},{1,0}};
    cout << sol.largestIsland(grid) << endl;
} 

