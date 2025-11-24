#include <bits/stdc++.h>
#include <functional>
using namespace std;

// dijkstra algo
// cost is num of 1-cells we pass through

struct State {
    int r, c, cost;
};

bool cmp(const State& s1, const State& s2) {
    return s1.cost > s2.cost;
}

class Solution {
public:
    int R, C;
    const vector<vector<int>> DIRS = {{-1,0}, {0,1}, {1,0}, {0,-1}};
    vector<vector<int>> dist;
    
    bool isValid(int r, int c) {
        return r >= 0 && r < R && c >= 0 && c < C;
    }

    int dijkstra(vector<vector<int>>& grid) {
        priority_queue<State, vector<State>, bool(*)(const State&, const State&)> pq(cmp);
        
        pq.push({0, 0, grid[0][0]});
        while (1) {
            State s = pq.top(); pq.pop();
            if (dist[s.r][s.c] != -1) continue;

            dist[s.r][s.c] = s.cost;
            if (s.r == R - 1 && s.c == C - 1) break;

            for (const vector<int>& dir : DIRS) {
                int nr = s.r + dir[0];
                int nc = s.c + dir[1];
                
                if (!isValid(nr, nc)) continue;

                int ncost = (grid[nr][nc] == 1) ? s.cost + 1 : s.cost;
                pq.push({nr, nc, ncost});
            }
        }

        return dist[R - 1][C - 1];
        
    }
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        R = grid.size(), C = grid[0].size();
        dist = vector(R, vector(C, -1));

        int minDist = dijkstra(grid);

        cout << minDist << endl;
        return minDist < health;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> grid = {{0,1,0,0,0},{0,1,0,1,0},{0,0,0,1,0}};
    int health = 4;

    cout << sol.findSafeWalk(grid, health) << endl;
}
