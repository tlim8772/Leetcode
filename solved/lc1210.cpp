#include <bits/stdc++.h>
using namespace std;

// bfs on state (r, c, dir)

enum class Dir {
    right, down,
};

struct State {
    int r = -1, c = -1;
    Dir d = Dir::right;

    State() {}

    State(int r, int c, Dir d): r(r), c(c), d(d) {}

    bool operator==(const State& s) const {
        return r == s.r && c == s.c && d == s.d;
    }
};

struct Hash {
    int operator()(State s) const {
        return s.r * 100 * 2 + s.c * 2 + static_cast<int>(s.d);
    }
};

class Solution {
public:
    int R, C;
    vector<vector<int>> grid;
   
    bool validPos(int r, int c) {
        return r >= 0 && r < R && c >= 0 && c < C;
    }

    bool validAndClearPos(int r, int c) {
        return validPos(r, c) && grid[r][c] == 0;
    }
    
    optional<State> canMoveRight(const State& s) {
        auto [r, c, d] = s;
        if (d == Dir::right) {
            if (validAndClearPos(r, c + 2)) {
                return make_optional<State>(r, c + 1, d);
            }
        } else if (d == Dir::down) {
            if (validAndClearPos(r, c + 1) && validAndClearPos(r + 1, c + 1)) {
                return make_optional<State>(r, c + 1, d);
            }
        }
        return optional<State>();
    }

    optional<State> canMoveDown(const State& s) {
        auto [r, c, d] = s;
        if (d == Dir::right) {
            if (validAndClearPos(r + 1, c) && validAndClearPos(r + 1, c + 1)) {
                return make_optional<State>(r + 1, c, d);
            }
        } else if (d == Dir::down) {
            if (validAndClearPos(r + 2, c)) {
                return make_optional<State>(r + 1, c, d);
            }
        }
        return optional<State>();
    }
    
    optional<State> canRotateClockWise(const State& s) {
        auto [r, c, d] = s;
        if (s.d == Dir::right && validAndClearPos(r + 1, c) && validAndClearPos(r + 1, c + 1)) {
            return make_optional<State>(r, c, Dir::down);
        }
        return optional<State>();
    }

    optional<State> canRotateAntiClockwise(const State& s) {
        auto [r, c, d] = s;
        if (s.d == Dir::down && validAndClearPos(r, c + 1) && validAndClearPos(r + 1, c + 1)) {
            return make_optional<State>(r, c, Dir::right);
        }
        return optional<State>();
    }
    
    int minimumMoves(vector<vector<int>>& grid) {
        R = grid.size(), C = grid[0].size();
        this->grid = grid;
        State start = State{0, 0, Dir::right}, end = State{R - 1, C - 2, Dir::right};

        using Temp = optional<State> (Solution::*) (const State& s); 
        vector<Temp> funcs = {
            &Solution::canMoveRight,
            &Solution::canMoveDown,
            &Solution::canRotateClockWise,
            &Solution::canRotateAntiClockwise
        };

        unordered_set<State, Hash> visited;
        deque<State> q;
        int wave = 0;
        
        visited.insert(start);
        q.push_back(start);

        while (!q.empty()) {
            for (int len = q.size(); len > 0; len--) {
                State s = q.front(); q.pop_front();
                if (s == end) return wave;

                for (auto& f : funcs) {
                    optional<State> next = (this->*f)(s);
                    if (!next.has_value() || visited.contains(next.value())) continue;
                    
                    visited.insert(next.value());
                    q.push_back(next.value());
                }
            }
            wave++;            
        }

        return -1;

    }
};

int main() {
    Solution sol;
    vector<vector<int>> grid = {{0,0,0,0,0,1},
                                {1,1,0,0,1,0},
                                {0,0,0,0,1,1},
                                {0,0,1,0,1,0},
                                {0,1,1,0,0,0},
                                {0,1,1,0,0,0}};

    int ans = sol.minimumMoves(grid);
    cout << ans << endl;
    
}