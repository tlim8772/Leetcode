#include <bits/stdc++.h>
using namespace std;

// bfs using state as (x, y, mask, energy, steps)
// we flatten (x,y) into a single int -> (pos, mask, energy)
// need to prune


class Solution {
public:
    vector<pair<int,int>> DIRS = {{-1,0},{0,1},{1,0},{0,-1}};

    int R, C;
    int MAX_ENERGY;
    int MAX_LITTER;
    int MASK;
    unordered_map<int, int> idxToPos;
    unordered_map<int, int> posToIdx;

    vector<int> store;
    vector<int> store2; // to prune we store the max energy we have when we are at (pos, mask)
                        // if we reach to (pos, mask) with lower energy, we dont need to search further
                        // we use bfs, so we visit (pos, mask) in increasing distance, so previous
                        // values are written when distance is strictly lesser

    inline int coor(int r, int c) {
        return r * C + c;
    }

    // for store
    inline int coor2(int pos, int mask, int energy) {
        return pos * MASK * (MAX_ENERGY + 1) 
                + mask * (MAX_ENERGY + 1) 
                + energy;
    }

    // for store2
    inline int coor3(int pos, int mask) {
        return pos * MASK
                + mask;
    }

    inline pair<int, int> toCoor(int pos) {
        return {pos / C, pos % C};
    }

    void processLitterPos(const vector<string>& grid) {
        int idx = 0;
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                if (grid[r][c] != 'L') continue;
                int pos = coor(r, c);
                idxToPos[idx] = pos;
                posToIdx[pos] = idx;
                idx++;
            }
        }

        cout << idxToPos.size() << endl;
    }

    pair<int,int> findStartPos(const vector<string>& grid) {
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                if (grid[r][c] == 'S') return {r, c};
            }
        }
        return {-1, -1};
    }

    bool isValidPos(int r, int c) {
        return r < R && r >= 0 && c < C && c >= 0;
    }

    int bfs(const vector<string>& grid, int startEnergy) {
        pair<int, int> start = findStartPos(grid);
        
        queue<tuple<int,int,int,int>> q;
        q.emplace(coor(start.first, start.second), 0, startEnergy, 0);

        while (!q.empty()) {
            auto [pos, mask, energy, dist] = q.front(); q.pop();
            auto [r, c] = toCoor(pos);
            
            int pos2 = coor2(pos, mask, energy);
            int pos3 = coor3(pos, mask);
            if (store[pos2] != -1) continue;

            store[pos2] = dist;
            
            // if we reach (pos, mask) before, definitely at lower dist, with higher energy, we don't need 
            // to search anymore
            if (energy < store2[pos3]) {
                continue;
            } else {
                store2[pos3] = energy; 
            }

            if (mask == ((1 << MAX_LITTER) - 1)) return dist; // just return the 1st time you see complete mask

            if (grid[r][c] == 'R') energy = MAX_ENERGY; // reset energy first, and no matter what

            if (energy == 0) continue; // can't continue

            for (auto [dr, dc]: DIRS) {
                int nr = r + dr, nc = c + dc;
                int npos = coor(nr, nc);
                int nmask = mask;
                
                if (!isValidPos(nr, nc) || grid[nr][nc] == 'X') continue;

                if (grid[nr][nc] == 'L') {
                    nmask = mask | (1 << (posToIdx[npos])); // using OR, we dont need to care if the litter 
                                                            // has been picked up previously
                }

                q.emplace(npos, nmask, energy - 1, dist + 1);
            }
        }

        return -1;
    }


    int minMoves(vector<string>& classroom, int energy) {
        R = classroom.size(), C = classroom[0].size();
        MAX_ENERGY = energy;

        processLitterPos(classroom);
        MAX_LITTER = idxToPos.size();
        MASK = 1 << MAX_LITTER;

        store = vector(R * C * MASK * (energy + 1), -1);
        store2 = vector(R * C * MASK, -1);

        int ans = bfs(classroom, energy);
        return ans;
    }
};

int main() {
    Solution sol;

    vector<string> grid = {"S.", "XL"};
    int energy = 2;

    cout << sol.minMoves(grid, energy) << endl;
}