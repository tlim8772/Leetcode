#include <bits/stdc++.h>
using namespace std;

// lets say we want to build a MST, such that the smallest weight is maximised
// we sort the edges in decreasing order, then connect the edge if it does not create a cycle
// greedy will work
// here we join the mandatory edges first
// we use the doubling on the smallest of the non mandatory edges used

struct DSU {
    vector<int> weights, parents;

    DSU(int n): weights(n, 1), parents(n, 0) {
        for (int i = 0; i < n; i++) {
            parents[i] = i;
        }
    }

    int find(int u) {
        if (parents[u] == u) {
            return u;
        } else {
            int p = find(parents[u]);
            parents[u] = p;
            return p;
        }
    }

    void join(int u, int v) {
        int pu = find(u), pv = find(v);
        if (pu == pv) return;
        
        if (weights[pu] < weights[pv]) swap(pu, pv);
        weights[pu] += weights[pv];
        parents[pv] = pu;
    }
};

class Solution {
public:
    int maxStability(int n, vector<vector<int>>& edges, int k) {
        vector<vector<int>> mustEdges;
        vector<vector<int>> notMustEdges;
        for (const vector<int>& e : edges) {
            if (e[3] == 1) {
                mustEdges.push_back(e);
            } else {
                notMustEdges.push_back(e);
            }
        }

        sort(notMustEdges.begin(), notMustEdges.end(), 
            [] (const vector<int>& e1, const vector<int>& e2) { return e1[2] > e2[2]; }
        );

        DSU dsu(n);
        int edgesUsed = 0;
       
        int mustEdgesMin = 999999;
        for (const vector<int>& e : mustEdges) {
            int p1 = dsu.find(e[0]), p2 = dsu.find(e[1]);
            
            if (p1 == p2) return -1; // cannot use this mandatory edge without creating a cycle
            dsu.join(e[0], e[1]);
            edgesUsed++;
            mustEdgesMin = min(mustEdgesMin, e[2]);
        }

        vector<int> ws;
        for (const vector<int>& e : notMustEdges) {
            int p1 = dsu.find(e[0]), p2 = dsu.find(e[1]);
            if (p1 == p2) continue;

            dsu.join(e[0], e[1]);
            edgesUsed++;
            ws.push_back(e[2]);
        }

        if (edgesUsed < n - 1) return -1;

        int kMin = 999999, restMin = 999999;
        for (int i = ws.size() - 1; i >= 0; i--) {
            if (ws.size() - i <= k) {
                kMin = min(kMin, 2 * ws[i]);
            } else {
                restMin = min(restMin, ws[i]);
            }
        }

        int ans = min(min(kMin, restMin), mustEdgesMin);
        return ans;
        
    }
};

int main() {
    Solution sol;

    int n = 3;
    vector<vector<int>> edges = {{0,1,1,1},{1,2,1,1},{2,0,1,1}};
    int k = 2;

    cout << sol.maxStability(n, edges, k);
}