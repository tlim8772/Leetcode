#include <bits/stdc++.h>
using namespace std;


class Solution {
public:

    vector<string> generateNextState(const string& state) {
        static vector<pair<int,int>> dirs = {{-1,0}, {0,1}, {1,0}, {0,-1}};
        
        int r = -1, c = -1;
        for (int i = 0; i < state.size(); i++) {
            if (state[i] == '0') {
                r = i / 3, c = i % 3;
            }
        }

        vector<string> out;
        for (auto [x, y] : dirs) {
            int nr = r + x, nc = c + y;
            if (nr < 0 || nr >= 2 || nc < 0 || nc >= 3) continue;
            string nextState = state;
            nextState[nr * 3 + nc] = '0';
            nextState[r * 3 + c] = state[nr * 3 + nc];
            out.push_back(std::move(nextState));
        }

        return out;
    }

    int bfs(const string& start) {
        string end = "123450";
        unordered_map<string, int> store;
        queue<string> q;
        int d = 0;

        q.push(start);

        while (!q.empty() && !store.contains(end)) {
            int len = q.size();
            for (; len > 0; len--) {
                string state = q.front(); q.pop();
                store[state] = d;
                if (state == end) break;
                
                //vector<string> nexts = generateNextState(state);
                for (const string& next : generateNextState(state)) {
                    if (store.contains(next)) continue;
                    store[next] = d + 1;
                    q.push(std::move(next));
                }
            }
            d++;
        }

        return (!store.contains(end)) ? -1 : store[end];
        
    }

    int slidingPuzzle(vector<vector<int>>& board) {
        string start = "";
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 3; j++) {
                start += to_string(board[i][j]);
            }
        }
        //cout << start << endl;
        return bfs(start);
    }
};

int main() {
    Solution sol;
   
    vector<vector<int>> board = {{4,1,2},{5,0,3}};
    cout << sol.slidingPuzzle(board) << endl;
    
}