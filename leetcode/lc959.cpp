#include <bits/stdc++.h>
using namespace std;

// use union find, count islands
// if coor i,j is "/" the left region is i*R + j, right region is i*R + j + R**2
// if coor (i,j) is "\", same left region is i*R + j, right region is i*R + j + R**2
// if coor (i,j) is " ", then take as it have "/" but join the left and right region too

struct UnionFind {
    vector<int> parents;
    vector<int> weights;

    UnionFind() {}

    UnionFind(int n): parents(n, 0), weights(n, 1) {
        for (int i = 0; i < n; i ++) {
            parents[i] = i;
        }
    }

    int find(int x) {
        if (parents[x] == x) return x;

        int p = find(parents[x]);
        parents[x] = p;
        return p;
    }

    void join(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px == py) return;

        if (weights[px] < weights[py]) {
            parents[px] = py;
            weights[py] += weights[px];
        } else {
            parents[py] = px;
            weights[px] += weights[py];
        }
    }

};

class Solution {
public:
    int ROWS;
    int SIZE;
    UnionFind uf;
    vector<string> grid;

    bool valid(int i, int j) {
        return i >= 0 && j >= 0 && i < ROWS && j < ROWS;
    }

    // 0 if left, 1 if right
    int coor(int i, int j, int leftOrRight) {
        
        return i * ROWS + j + leftOrRight * SIZE;
    }

    int up(int i, int j) {
        if (!valid(i - 1, j)) return -1;

        if (grid[i - 1][j] == '\\') {
            return coor(i - 1, j, 0);
        } else {
            return coor(i - 1, j, 1);
        }
    }

    int down(int i, int j) {
        if (!valid(i + 1, j)) return -1;

         if (grid[i + 1][j] == '\\') {
            return coor(i + 1, j, 1);
        } else {
            return coor(i + 1, j, 0);
        }
    }

    int left(int i, int j) {
        if (!valid(i, j - 1)) return -1;
        return coor(i, j - 1, 1);
    }

    int right(int i, int j) {
        if (!valid(i, j + 1)) return -1;
        return coor(i, j + 1, 0);
    }



    int regionsBySlashes(vector<string>& grid) {
        ROWS = grid.size();
        SIZE = ROWS * ROWS;
        this->grid = grid;
        uf = UnionFind(2 * SIZE);
        
        for (int i = 0; i < ROWS; i ++) {
            for (int j = 0; j < ROWS; j ++) {
                int arr[4] = {up(i, j), down(i, j), left(i, j), right(i, j)};
                
                if (grid[i][j] == ' ') {
                    uf.join(coor(i, j, 0), coor(i, j, 1));
                    for (int k = 0; k < 4; k ++) {
                        if (arr[k] != -1) uf.join(arr[k], coor(i, j, 0));
                    }
                } else if (grid[i][j] == '/') {
                    if (arr[0] != -1) {
                        
                        uf.join(arr[0], coor(i, j, 0));
                    }
                    
                    if (arr[1] != -1) {
                        uf.join(arr[1], coor(i, j, 1));
                    }
                    
                    if (arr[2] != -1) {
                        uf.join(arr[2], coor(i, j, 0));
                    }
                    
                    if (arr[3] != -1) {
                        uf.join(arr[3], coor(i, j, 1));
                    }
                } else {
                    if (arr[0] != -1) {
                        uf.join(arr[0], coor(i, j, 1));
                    }
                    
                    if (arr[1] != -1) {
                        uf.join(arr[1], coor(i, j, 0));
                    }
                    
                    if (arr[2] != -1) {
                        uf.join(arr[2], coor(i, j, 0));
                    }
                    
                    if (arr[3] != -1) {
                        uf.join(arr[3], coor(i, j, 1));
                    }
                }
            }
        }

        int cnt = 0;
        for (int i = 0; i < 2 * SIZE; i ++) {
            if (uf.parents[i] == i) cnt ++;
        }
        //cout << uf.find(4) << " " << uf.find(7) << endl;
        return cnt;
        
    }


};

int main() {
    Solution sol;
    vector<string> grid = {"/ ", "  "};
    cout << sol.regionsBySlashes(grid) << endl;
}