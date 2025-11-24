#include <bits/stdc++.h>
using namespace std;

// use dfs visited idx and low to find cut vertices
// if already disconnnected, return 0
// if have >= 1 cut vertex return 1
// else return 2

// tarjan algo for cut vertices
// a vertex v is a cut vertex, if in the dfs tree, the subtree rooted at the vertex has no backedge to
// any ancestor of v
// low[v] the earliest vertex we can reach in the dfs tree without going back from parent with 1 backedge only
// eg graph is 0 1 1  order of dfs is up right down left
//             1 1 1
//             1 1 0
// clearly for vertex (2, 1), earliest is node 0 at (0, 1)
// but for node (2,0), we do not want low(2,0) to be 0, instead it should be 3, the visited id of node(2, 1)
// so if its backedge, we do not take low[child] but idx[child]
// if it is dfs child, take low[child]


class Solution {
public:
    int R, C;
    vector<array<int, 2>> dirs = {{-1,0},{0,1},{1,0},{0,-1}};

    bool isValid(int r, int c) {
        return r >= 0 && r < R && c >= 0 && c < C;
    }

    inline int coor(int r, int c) {
        return r * C + c;
    }

    int dfs1(int r, int c, vector<vector<int>>& grid, vector<bool>& visited) {
        int pos = coor(r, c);
        visited[pos] = true;
        int sum = 1;
        
        for (array<int, 2> dir : dirs) {
            int nr = r + dir[0], nc = c + dir[1];
            if (!isValid(nr, nc) || grid[nr][nc] == 0 || visited[coor(nr, nc)]) continue;

            sum += dfs1(nr, nc, grid, visited);
        }
        return sum;
    }

    tuple<bool, int> isConnected(vector<vector<int>>& grid) {
        bool flag = false;
        R = grid.size(), C = grid[0].size();
        vector<bool> visited(grid.size() * grid[0].size(), false);
        int sum = 0;

        for (int r = 0; r < grid.size(); r++) {
            for (int c = 0; c < grid[0].size(); c++) {
                int pos = coor(r, c);
                
                if (grid[r][c] == 0 || visited[pos]) {
                    continue;
                } else if (flag) {
                    return {false, 1};
                } else {
                    flag = true;
                    sum += dfs1(r, c, grid, visited);
                }
            }
        }

        return {true, sum};
    }

    // returns true if there is a cut vertex
    // low[pos] == -1 if vertex has not been visited yet
    // also must take into accoun edge case
    // if the root (the 1st node) calls dfs2 more than once, the root is a cut vertex too
    // returns true dfs2 finds a cut vertex
    bool dfs2(int r, int c, int pr, int pc, vector<vector<int>>& grid, int& i, vector<int>& idx, vector<int>& low) {
        bool ans = false;
        int cnt = 0; // for edge case
        
        int temp = i++;
        int pos = coor(r, c);
        idx[pos] = low[pos] = temp;
        
        vector<pair<int, int>> children;

        for (array<int, 2>& d : dirs) {
            int nr = r + d[0], nc = c + d[1];
            int npos = coor(nr, nc);
            
            // cannot take parent val
            if (!isValid(nr, nc) || (nr == pr && nc == pc) || grid[nr][nc] == 0) continue; 
            
            if (low[npos] == -1) {
                children.push_back({nr, nc});
                bool res = dfs2(nr, nc, r, c, grid, i, idx, low);
                ans = ans || res;
                
                if (r == pr && c == pc) cnt++;
                
                low[pos] = min(low[pos], low[npos]);
            } else {
                // this is a backedge, we take idx, not low !!
                low[pos] = min(low[pos], idx[npos]);
            }
        }

        
       

        // we only check the children in the dfs tree!! 
        // very important, suppose we are at vertex v, we have edge to vertex u, but u is not child in dfs tree
        // means from some other child of v, we can go to u, then we must check the low value of that child, not u,
        // u low value may not be the 'lowest' value a node in the subtree rooted at v in dfs tree can reach
        bool flag = false;
        if (r != pr || c != pc) {
            for (pair<int, int>& child : children) {
                int npos = coor(child.first, child.second);
                if (low[npos] >= temp) {
                    flag = true;
                }
            }
        }
        
        bool out = flag || ans || (r == pr && c == pc && cnt > 1);
        
        return out;
    }

    bool hasCutVertex(vector<vector<int>>& grid) {
        R = grid.size(), C = grid[0].size();
        vector<int> idx(R * C, -1);
        vector<int> low(R * C, -1);
        int i = 0;
        bool ans = false;

        for (int r = 0; r < R; r ++) {
            for (int c = 0; c < C; c ++) {
                int pos = coor(r, c);
                if (grid[r][c] == 0 || low[pos] != -1) continue;
                bool res = dfs2(r, c, r, c, grid, i, idx, low);
                ans = ans || res;
            }
        }

        for (int r = 0; r < R; r ++) {
            for (int c = 0; c < C; c ++) {
                cout << low[coor(r, c)] << " ";
            }
            cout << endl;
        }

        return ans;

    }

    int minDays(vector<vector<int>>& grid) {
        tuple<bool, int> connected = isConnected(grid);
        if (!get<0>(connected)) return 0;
        else if (get<1>(connected) == 0) return 0;
        else if (get<1>(connected) == 1) return 1; // handle case where only 1 '1' block

        bool cutVertex = hasCutVertex(grid);
        if (cutVertex) return 1;

        return 2;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> grid = {{0,1,1},{1,1,1},{1,1,0}};
    cout << sol.minDays(grid) << endl;
}