#include <bits/stdc++.h>
using namespace std;

// simple dfs. 
// Recurse on subtree to find 
// {min dist to collect all apples in subtree with start end at that root, whether subtree has apple}.

class Solution {
public:
    vector<vector<int>> adj;

    void process_adj(int n, vector<vector<int>>& edges) {
        adj = vector(n, vector<int>());
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
    }

    // {min dist, whether subtree has apple}
    pair<int, bool> dfs(int v, int p, vector<bool>& hasApples) {
        bool have = hasApples[v];
        int sum = 0;
        for (int c : adj[v]) {
            if (c == p) continue;
            
            auto [s, b] = dfs(c, v, hasApples);
            if (!b) continue;

            sum += s + 2;
            have = have || b;
        }

        return {sum, have};
    }
    int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
        process_adj(n, edges);
        auto [s, b] = dfs(0, 0, hasApple);
        return s;
    }
};