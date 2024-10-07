#include <bits/stdc++.h>
using namespace std;

// find a corner. A corner is a node with degree 2
// then fix a row. Find a row by considering 3 cases
// once we have a row, we can fill up the entire grid;

class Solution {
public:
    vector<vector<int>> adj;
    
    
    vector<vector<int>> grid;
    
    int n;
    int corner;
    int opt;
    
    int COLS;
    int ROWS;
    
    void process(int n, vector<vector<int>>& edges) {
        this->n = n;
        adj = vector(n, vector<int>());
        for (vector<int>& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
    }

    void whichCase() {
        for (int i = 0; i < n; i ++) {
            if (adj[i].size() == 1) {
               opt = 0;
               return;
            } 
        }
        opt = 1;
    }

    void findCorner() {
        for (int i = 0; i < n; i ++) {
            if (!opt && adj[i].size() == 1) {
                corner = i;
            } else if (opt && adj[i].size() == 2) {
                corner = i;
            }
        }
    }

    vector<int> findRowsColAndRow() {
        int cnt = 1;
        int prev = corner;
        vector<int> row;
        
        
        if (adj[prev].size() == 1) { // case1: ROWS == 1 || COLS == 1
            row.push_back(prev);
            COLS = 1;
            ROWS = n;
        } else { 
            bool flag = false;

            // case2: ROWS == 2 || COLS == 2
            for (int c : adj[prev]) {
                if (adj[c].size() == 2) {
                    flag = true;
                    row.push_back(prev);
                    row.push_back(c);
                    COLS = 2;
                    ROWS = n / 2;
                    break;
                }
            }

            // case3: ROWS > 2 && COLS > 2
            if (!flag) {
                vector<int> visited(n, false);
                int cnt = 1;
                row.push_back(prev);
                visited[prev] = true;
                while (true) {
                    for (int c : adj[prev]) {
                        if (adj[c].size() < 4 && !visited[c]) {
                            prev = c;
                            visited[c] = true;
                            break;
                        }
                    }
                    
                    row.push_back(prev);
                    cnt ++;
                    
                    if (adj[prev].size() == 2) {
                        COLS = cnt;
                        ROWS = n / COLS;
                        break;
                    }
                }
            }
        }
        return row;
    }

    void processGrid(vector<int>& row) {
        vector<bool> visited(n, false);
        grid = vector(ROWS, vector(COLS, 0));
        queue<vector<int>> q;
        for (int i = 0; i < row.size(); i ++) {
            q.push({row[i], i});
            visited[row[i]] = true;
            
        }

        int r = 0;
        while (!q.empty()) {
            int len = q.size();
            for (int i = 0; i < len; i++) {
                vector<int> top = q.front();
                q.pop();
                
                int node = top[0];
                int col = top[1];
                grid[r][col] = node;
                for (int c : adj[node]) {
                    if (!visited[c]) {
                        visited[c] = true;
                        q.push({c, col});
                    }
                }
            }
            r ++;
        }
    }

    vector<vector<int>> constructGridLayout(int n, vector<vector<int>>& edges) {
        process(n, edges);
        whichCase();
        findCorner();

        vector<int> row = findRowsColAndRow();
        
        cout << endl;
        processGrid(row);
        return grid;
    }

};

int main() {
    Solution sol;
    vector<vector<int>> edges = {{0,2},{0,4},{0,5},{1,3},{1,9},{2,6},{2,11},{3,6},{3,11},{4,8},{4,10},{4,11},{5,10},{7,8},{7,10},{8,9},{9,11}};
    vector<vector<int>> ans = sol.constructGridLayout(12, edges);

    for (vector<int> r : ans) {
        for (int x : r) {
            cout << x << " ";
        }
        cout << endl;
    }
}