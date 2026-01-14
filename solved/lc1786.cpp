#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// disjktra to find shortest path from node i to node n - 1 for all i.
// then is just simple dynamic programming. (or dfs in topological order).

class Solution {
public:
    const int MOD = 1e9 + 7;
    int n;
    vector<vector<pair<int,int>>> adj;
    vector<ll> dists;
    vector<int> num_paths;

    void make_adj(int n, vector<vector<int>> edges) {
        adj = vector(n, vector<pair<int,int>>());
        for (auto& e : edges) {
            adj[e[0] - 1].emplace_back(e[1] - 1, e[2]);
            adj[e[1] - 1].emplace_back(e[0] - 1, e[2]);
        }
    }

    void dijkstra(int src) {
        auto cmp = [] (const pair<int,int>& p1, const pair<int,int>& p2) { return p1.second > p2.second; };
        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq(cmp);
        dists = vector(n, -1LL);
        
        pq.emplace(src, 0);

        while (!pq.empty()) {
            auto [v, d] = pq.top(); pq.pop();
            if (dists[v] != -1) continue;
            
            dists[v] = d;
            for (auto [next, w] : adj[v]) {
                if (dists[next] != -1) continue;
                pq.emplace(next, d + w);
            }
        }
    }

    int dfs(int v) {
        if (v == n - 1) return 1;
        if (num_paths[v] != -1) return num_paths[v];
        int &sum = num_paths[v];
        int my_dist = dists[v];
        
        sum = 0;
        for (auto [c, w] : adj[v]) {
            if (dists[c] >= my_dist) continue;
            sum = (sum + dfs(c)) % MOD;
        }
        
        return sum;
    }
    
    int countRestrictedPaths(int n, vector<vector<int>>& edges) {
        this->n = n;
        make_adj(n, edges);
        dijkstra(n - 1);
        num_paths = vector(n, -1);
        return dfs(0);
    }
};

int main() {
    Solution sol;
    int n = 5;
    vector<vector<int>> edges = {{1,2,3},{1,3,3},{2,3,1},{1,4,2},{5,2,2},{3,5,1},{5,4,10}};

    cout << sol.countRestrictedPaths(n, edges) << endl;
}