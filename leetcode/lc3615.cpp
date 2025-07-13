#include <bits/stdc++.h>
using namespace std;

// bitmask dp
// dp(i, j, bm)
// bm: bitmask of nodes taken
// i, j is the current left, right, we expand outwards

class Solution {
public:
    int N, MAX_BM;
    string label;
    vector<vector<int>> adj;
    
    vector<int> store;

    int coor(int i, int j, int bm) {
        return i * N * MAX_BM + j * MAX_BM + bm;
    }

    void processAdj(const vector<vector<int>>& edges) {
        for (const vector<int>& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
    }

    int dp(int i, int j, int bm) {
        int pos = coor(i, j, bm);
        if (store[pos] != -1) {
            return store[pos];
        }

        int best = 0;
        for (int c1 : adj[i]) {
            if (((bm >> c1) & 1) == 1) continue;
            
            for (int c2 : adj[j]) {
                if (c1 == c2) continue;
                
                if (((bm >> c2) & 1) == 1) continue;
                
                if (label[c1] != label[c2]) continue;

                int newBm = bm | (1 << c1) | (1 << c2);
                int res = 2 + dp(c1, c2, newBm);
                best = max(best, res);
            }
        }

        store[pos] = best;
        return best;
    }
    
    int maxLen(int n, vector<vector<int>>& edges, string label) {
        N = n;
        MAX_BM = 1 << N;
        this->label = label;
        adj = vector(N, vector<int>());

        processAdj(edges);

        store = vector(N * N * MAX_BM, -1);

        int best = 0;

        // check single node as center
        for (int i = 0; i < n; i++) {
            int ans = 1 + dp(i, i, 1 << i);
            best = max(best, ans);
        }

        // check 2 nodes as center
        for (const vector<int>& e : edges) {
            if (label[e[0]] != label[e[1]]) continue;
            int ans = 2 + dp(e[0], e[1], (1 << e[0]) | (1 << e[1]));
            best = max(best, ans);
        }

        return best;
    }
};

int main()  {
    Solution sol;

    int n = 5;
    vector<vector<int>> edges = {{2,0},{0,1},{1,2},{2,3},{1,4},{3,4},{0,3},{2,4},{1,3},{4,0}};
    string label = "daeed";

    int ans = sol.maxLen(n, edges, label);
    cout << ans << endl;
}