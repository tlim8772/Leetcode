#include <bits/stdc++.h>
using namespace std;

struct State {
    int r, c, f;
};

struct Pair {
    State state;
    int t;
};



class Solution {
public:
    vector<vector<vector<int>>> time;
    vector<vector<int>> DIRS = {{0,1}, {1,0}, {0,-1}, {-1,0}};
    int INVALID = 2000000000;
    int R, C;

    bool isValid(int x, int y) {
        return x >= 0 && x < R && y >= 0 && y < C;
    }



    
    int minTimeToReach(vector<vector<int>>& moveTime) {
        R = moveTime.size();
        C = moveTime[0].size();
        time = vector(2, vector(moveTime.size(), vector(moveTime[0].size(), INVALID)));
        auto cmp = [](Pair& p1, Pair& p2) {return p1.t > p2.t;};
        priority_queue<Pair, vector<Pair>, decltype(cmp)> pq(cmp);
        

        pq.push({{0,0,0}, 0});

        while (!pq.empty()) {
            Pair next = pq.top(); 
            pq.pop();

            State& s = next.state;
            int t = next.t;
            if (time[s.f][s.r][s.c] != INVALID) continue;

            time[s.f][s.r][s.c] = t;

            for (vector<int>& dir : DIRS) {
                int nr = s.r + dir[0];
                int nc = s.c + dir[1];
                
                // if coor not valid, or already have shortest dist
                if (!isValid(nr, nc) || time[!s.f][nr][nc] != INVALID) continue;

                pq.push({{nr, nc, !s.f}, max(moveTime[nr][nc], t) + 1 + s.f});
            }
        }

        return min(time[0][R - 1][C - 1], time[1][R - 1][C - 1]);
    }
};

int main() {
    Solution sol;
    vector<vector<int>> arr = {{0,1},{1,2}};
    int ans = sol.minTimeToReach(arr);
    cout << ans << endl;
}