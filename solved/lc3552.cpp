#include <bits/stdc++.h>
using namespace std;

// consider all vertices with the same letter as 1 big vertex
// when we reach a vertex with a letter, we can use the teleporter, or not
// if we do not use, we can never touch another vertex with the same letter again
// otherwise why not just teleport there ?

// likewise if we use a teleporter, we can never go back to another vertex with the same letter again
// otherwise why not just teleport there ?


// so we do bfs, and we visit each letter exactly once

class Solution {
public:
    vector<pair<int, int>> DIR = {{-1,0},{0,1},{1,0},{0,-1}};
    vector<vector<pair<int, int>>> letterGroups;

    bool isLetter(char c) {
        int id = c - 'A';
        return c >= 0 && c < 26;
    }

    bool isPosValid(int r, int c, vector<string>& matrix) {
        return r >= 0 && r < matrix.size() && c >= 0 && c < matrix[0].size();
    }

    void process(vector<string>& matrix) {
        int R = matrix.size(), C = matrix[0].size();
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                int id = matrix[i][j] - 'A';
                if (id >= 0 && id < 26) {
                    letterGroups[id].push_back({i, j});
                }
            }
        }
    }

    int bfs(vector<string>& matrix) {
        vector<vector<int>> dist = vector(matrix.size(), vector(matrix[0].size(), -1));
        
        queue<tuple<int,int,int>> q;
        q.push({0,0,0});

        // better to check the validity of the position in the beginning of the for loop
        while (!q.empty()) {
            tuple<int,int,int> next = q.front(); q.pop();
            int r = get<0>(next), c = get<1>(next), d = get<2>(next);
            
            if (!isPosValid(r, c, matrix)) continue;
             

            if (matrix[r][c] == '#') continue;
            
            if (dist[r][c] != -1) continue;
           
            dist[r][c] = d;
            if (r == matrix.size() - 1 && c == matrix[0].size() - 1) break;


            // case 1: current char is '.'
            if (matrix[r][c] == '.') {
                for (pair<int,int> dir : DIR) {
                    int nr = r + dir.first, nc = c + dir.second;
                    q.push({nr, nc, d + 1});
                }
            } else {
                // case 2b: teleport to a vertex with the same letter
                // then go to an adjacent cell of different (or no) color
                
                // case 2a: dont teleport, go to adjacent cell of different (or no color)
                // is contained in case 2b
                for (pair<int,int> pos : letterGroups[matrix[r][c] - 'A']) {
                    int nr = pos.first, nc = pos.second;
                    dist[nr][nc] = d;
                    
                    if (nr == matrix.size() - 1 && nc == matrix[0].size() - 1) break;

                    for (pair<int,int> dir : DIR) {
                        int nr2 = nr + dir.first, nc2 = nc + dir.second;
                        
                        if (!isPosValid(nr2, nc2, matrix)) continue;
                        
                        if (matrix[nr2][nc2] == matrix[r][c]) continue;
                        
                        q.push({nr2, nc2, d + 1});
                    }
                }


            }
        }

        return dist[matrix.size() - 1][matrix[0].size() - 1];

    }

    int minMoves(vector<string>& matrix) {
        letterGroups = vector(26, vector<pair<int,int>>());

        process(matrix);

        int ans = bfs(matrix);
        return ans;
    }
};

int main() {
    Solution sol;

    vector<string> m = {"A..",".A.","..."};

    cout << sol.minMoves(m) << endl;
}