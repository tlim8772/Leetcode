#include <bits/stdc++.h>
using namespace std;

// use dp and sparse table to do min range queries.
// we do bottom up dp on i + j = s.
// then for the next node to jump to, we have i_next + j_next > s
// if grid[i][j] = k, we want the min range query of grid[i][j + 1] to grid[i][j + k]
// and grid[i + 1][j] to grid[i + k][j].

template <typename T>
requires default_initializable<T>
struct SparseTable {
    function<T(T, T)> combi;
    
    int MAX_POW = 0, n = 0;
    vector<vector<T>> table;

    SparseTable(int n, function<T(T, T)> func): n(n), combi(func) {
        MAX_POW = (int) floor(log2(n));
        table = vector(n, vector(1 + MAX_POW, T()));
    }

    void insert(int i, T val) {
        table[i][0] = val;
        for (int p = 1; p <= MAX_POW; p++) {
            if (i + (1 << (p - 1)) < n) {
                table[i][p] = combi(table[i][p - 1], table[i + (1 << (p - 1))][p - 1]);
            } else {
                table[i][p] = table[i][p - 1];
            }
        }
    };

    T query(int l, int r) {
        int maxp = (int) floor(log2(r - l + 1));
        return combi(table[l][maxp], table[r - (1 << maxp) + 1][maxp]);
    }
};

function<int(int,int)> f = [](int x, int y) { return min(x, y); };

class Solution {
public:
    int minimumVisitedCells(vector<vector<int>>& grid) {
        int R = grid.size(), C = grid[0].size();
        vector<SparseTable<int>> row_tables(R, SparseTable(C, f)), col_tables(C, SparseTable(R, f));

        vector<vector<int>> store(R, vector(C, 999999));
        store[R - 1][C - 1] = 1;
        row_tables[R - 1].insert(C - 1, 1);
        col_tables[C - 1].insert(R - 1, 1);

        for (int s = R - 1 + C - 1 - 1; s >= 0; s--) {
            for (int r = max(0, s - C + 1); r < min(s + 1, R); r++) {
                int c = s - r, k = grid[r][c];
                
                if (k == 0) {
                    store[r][c] = 999999;
                    row_tables[r].insert(c, 999999), col_tables[c].insert(r, 999999);
                    continue;
                }
                SparseTable<int> &rt = row_tables[r], &ct = col_tables[c];

                int rs = c + 1, re = min(C - 1, c + k);
                int right_res = (rs <= re) ? rt.query(rs, re) : 999999;
        
                int ds = r + 1, de = min(R - 1, r + k);
                int down_res = (ds <= de) ? ct.query(ds, de) : 999999;

                int ans = min(right_res, down_res);
                rt.insert(c, 1 + ans);
                ct.insert(r, 1 + ans);
                store[r][c] = 1 + ans;
                //cout << r << " " << c << " " << 1 + ans << endl;
            }
        }

        int ans = store[0][0];
        return (ans >= 999999) ? -1 : ans;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> grid = {{3,0,0,0},{0,0,0,0},{0,0,0,0},{2,4,0,0}};
    cout << sol.minimumVisitedCells(grid) << endl;
}