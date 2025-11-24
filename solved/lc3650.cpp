#include <bits/stdc++.h>
using namespace std;

// just use dijkstra
// except also consider reversed edges
// no need to do anything else, because we only visit each node once

struct Edge {
    int v;
    int w;
    bool isReversed;
};

class Solution {
public:

    vector<vector<Edge>> getAdj(int n, const vector<vector<int>>& edges) {
        vector<vector<Edge>> adj = vector(n, vector<Edge>());
        for (const vector<int>& e : edges) {
            adj[e[0]].push_back(Edge{e[1], e[2], false});
            adj[e[1]].push_back(Edge{e[0], e[2], true});
        }

        return adj;
    }
    
    
    int minCost(int n, vector<vector<int>>& edges) {
        auto cmp = [](pair<int,int> a, pair<int,int> b) { return a.second > b.second; };
        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq(cmp);
        vector<int> dists(n, -1);
        vector<vector<Edge>> adj = getAdj(n, edges);

        pq.push({0, 0});
        while (!pq.empty()) {
            const auto [node, d] = pq.top(); pq.pop();
            if (dists[node] != -1) continue;
            dists[node] = d;
            
            if (node == n - 1) break;

            for (Edge& e : adj[node]) {
                if (dists[e.v] != -1) continue;
                pq.push(pair{e.v, d + ((e.isReversed) ? 2 * e.w : e.w)});
            }
        }

        return dists[n - 1];
    }
};