#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> adj;
    string labels;
    
    vector<int> results;

    void makeAdj(int n, vector<vector<int>>& edges) {
        adj = vector(n, vector<int>());
        for (auto e: edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
    }

    array<int, 26> dfs(int v, int p) {
        array<int, 26> out;
        out.fill(0);
        out[labels[v] - 'a']++;

        for (int c : adj[v]) {
            if (c == p) continue;
            auto res = dfs(c, v);
            for (int i = 0; i < 26; i++) {
                out[i] += res[i];
            }
        }

        results[v] = out[labels[v] - 'a'];
        return out;
    }
    vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels) {
        this->labels = labels;
        results = vector(n, 0);

        makeAdj(n, edges);
        
        dfs(0, 0);

        return results;
    }
};

int main() {
    int n = 4;
    vector<vector<int>> edges = {{0,1}, {1,2}, {0,3}};
    string labels = "bbbb";

    Solution sol;
    vector<int> ans = sol.countSubTrees(n, edges, labels);
    for (int x : ans) cout << x << " ";
    cout << endl;

}