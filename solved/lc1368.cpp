#include <bits/stdc++.h>
using namespace std;

// dijkstra, we want path with min cost from (0,0) to (R - 1, C - 1)
// if take diff dir, cost + 1, else cost remains the same
// no need to worry about cycle, in dijkstra algo, if revisit same node, just ignore

struct State {
    int r, c , cost;
};

bool cmp(const State& s1, const State& s2) {
    return s1.cost > s2.cost;
}

class Solution {
public:
    int R, C;
    const vector<vector<int>> DIRS = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    vector<vector<int>> dist;

    bool isValid(int r, int c) {
        return r >= 0 && r < R && c >= 0 && c < C;
    }

    int dijkstra(vector<vector<int>>& grid) {
        priority_queue<State, vector<State>, bool(*)(const State&, const State&)> pq(cmp);
        pq.push({0,0,0});

        while (!pq.empty()) {
            State s = pq.top(); pq.pop();

            if (dist[s.r][s.c] != -1) continue;
            
            dist[s.r][s.c] = s.cost;
            if (s.r == R - 1 && s.c == C - 1) break;

            for (int i = 0; i < 4; i ++) {
                const vector<int>& dir = DIRS[i];
                int nr = s.r + dir[0], nc = s.c + dir[1];

                if (!isValid(nr, nc)) continue;
                int ncost = (grid[s.r][s.c] - 1 == i) ? s.cost : s.cost + 1;

                pq.push({nr, nc, ncost});
            }
        }

        return dist[R - 1][C - 1];
    }

    int minCost(vector<vector<int>>& grid) {
        R = grid.size(), C = grid[0].size();
        dist = vector(R, vector(C, -1));

        return dijkstra(grid);
    }

};

int main() {
    Solution sol;

    vector<vector<int>> grid = {{1,2},{4,3}};

    cout << sol.minCost(grid) << endl;
}