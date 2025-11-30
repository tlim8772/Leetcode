#include <bits/stdc++.h>
using namespace std;

/*
no contradictions means 2 different paths from a to b must produce the same value
*/

class Solution {
public:
    unordered_map<string, vector<pair<string, double>>> adj;
    unordered_map<string, unordered_map<string, double>> path_res;

    void make_adj(vector<vector<string>>& equations, vector<double>& values) {
        for (int i = 0; i < equations.size(); i++) {
            auto& e = equations[i];
            double v = values[i];
            adj[e[0]].emplace_back(e[1], v);
            adj[e[1]].emplace_back(e[0], 1.0 / v);
        }
    }

    void dfs(string src, string v, double store = 1.0) {
        path_res[src][v] = store;
        for (auto [next, val] : adj[v]) {
            if (path_res[src].contains(next)) continue;
            dfs(src, next, store * val);
        }
    }




    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        make_adj(equations, values);

        for (auto& [key, val] : adj) {
            dfs(key, key);
        }

        vector<double> out;
        for (auto& q : queries) {
            if (!path_res.contains(q[0]) || !path_res[q[0]].contains(q[1])) out.push_back(-1.0);
            else out.push_back(path_res[q[0]][q[1]]);
        }

        return out;
    }
};