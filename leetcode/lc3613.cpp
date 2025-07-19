#include <bits/stdc++.h>
using namespace std;

// simple greedy question
// sort edges in increasing order
// greedily take smallest edges until we have <= k connected components

struct UnionFind {
    vector<int> parents;
    vector<int> weights;

    UnionFind(int n): parents(n, 0), weights(n, 1) {
        for (int i = 0; i < n; i++) {
            parents[i] = i;
        }
    }

    int find(int v) {
        return (parents[v] == v) ? v : parents[v] = find(parents[v]);
    }

    
    void join(int u, int v) {
        int pu = find(u), pv = find(v);
        if (pu == pv) return;
        if (weights[pu] < weights[pv]) swap(pu, pv);

        parents[pv] = pu;
        weights[pu] += weights[pv];
    }
};

class Solution {
public:
    int minCost(int n, vector<vector<int>>& edges, int k) {
        if (k == n) return 0;

        UnionFind uf(n);
        sort(edges.begin(), edges.end(), [](const auto& v1, const auto& v2) { return v1[2] < v2[2]; });

        int cc = n;
        for (const vector<int>& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            int pu = uf.find(u), pv = uf.find(v);
            
            if (pu == pv) continue;
            cc--;
            uf.join(pu, pv);
            if (cc <= k) return w;
        }

        return edges.back()[2];
    }
};