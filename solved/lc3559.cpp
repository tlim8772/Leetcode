#include <bits/stdc++.h>
using namespace std;

// 2 problems in 1
// problem 1: given nodes u, v in a tree, find the distance. Use LCA
// problem 2: given sequences of 1,2, find # of sequences of length n s.t sum of elems is odd
// use tarjan offline disjoint set union algo to precompute all lca at once

struct UnionFind {
    vector<int> parents, weights, values;

    UnionFind(int n): parents(n, 0), weights(n, 1), values(n, -1) {
        for (int i = 0; i < n; i++) {
            parents[i] = i;
            values[i] = i;
        }
    }

    int find(int u) {
        return (parents[u] == u) ? u : parents[u] = find(parents[u]);
    }

    // which set value u, v to choose? Idk, user decides by calling
    // setValue() after calling join(u, v)
    void join(int u, int v) {
        int pu = find(u), pv = find(v);
        if (pu == pv) return;
        
        int wu = weights[pu], wv = weights[pv];
        if (wu < wv) return join(v, u);
        
        parents[pv] = pu;
        weights[pu] += wv;
    }

    int findValue(int u) {
        return values[find(u)];
    }

    void setValue(int u, int val) {
        values[find(u)] = val;
    }
};

struct FindLCA {
    int N;
    vector<vector<int>> adjQueries;
    vector<bool> processed;
    unordered_map<int, unordered_map<int, int>> results;
    UnionFind uf;

    vector<int> out;

    FindLCA(int N, const vector<vector<int>>& adj, const vector<vector<int>>& queries): adjQueries(N, vector<int>()), processed(N, false), uf(N) {
        processAdjQueries(queries);
        dfs(0, 0, adj);

        for (const vector<int>& q : queries) {
            out.push_back(results[min(q[0], q[1])][max(q[0], q[1])]);
        }
    }

    void processAdjQueries(const vector<vector<int>>& queries) {
        for (const vector<int>& q : queries) {
            adjQueries[q[0]].push_back(q[1]);
            adjQueries[q[1]].push_back(q[0]);
        }
    }

    void dfs(int v, int p, const vector<vector<int>>& adj) {
        for (int next : adj[v]) {
            if (next == p) continue;
            dfs(next, v, adj);
            uf.join(next, v);
            uf.setValue(v, v);
        }
        
        for (int qp : adjQueries[v]) {
            if (processed[qp]) {
                results[min(v, qp)][max(v, qp)] = uf.findValue(qp); // not findValue(v), at this point findValue(v) is always v
            }
        }

        processed[v] = true;
    }
};

// dp(parity, length): # of 1/2 sequences s.t sum is odd/even
// parity = 0 is even, 1 is odd
// 1st num is either odd or even, recurse accordingly
struct DP {
    int MOD = 1e9 + 7;
    int N;
    vector<vector<int>> store;

    DP(int N): N(N), store(2, vector(N, -1)) {
        store[0][0] = store[1][0] = 1;
        for (int i = 1; i < N; i++) {
            // put even, then put odd
            store[0][i] = (store[0][i - 1] + store[1][i - 1]) % MOD;
            store[1][i] = (store[1][i - 1] + store[0][i - 1]) % MOD;
        }
    }
};

class Solution {
public:
    int N;
    vector<vector<int>> adj;
    vector<int> heights;

    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        N = edges.size() + 1;
        adj = vector(N, vector<int>());
        heights = vector(N, 0);

        processAdj(edges);
        processHeight(0, 0, 0);

        for (vector<int>& q : queries) {
            q[0]--; q[1]--;
        }
        
        FindLCA findLCA(N, adj, queries);
        DP dp(N);

        vector<int> out;
        for (int i = 0; i < queries.size(); i++) {
            vector<int>& q = queries[i];
            if (q[0] == q[1]) {
                out.push_back(0);
                continue;
            }

            int lca = findLCA.out[i];
            int dist = heights[q[0]] + heights[q[1]] - 2 * heights[lca];
            int ans = dp.store[1][dist - 1];
            out.push_back(ans);
        }

        return out;

    }

    
    void processAdj(vector<vector<int>>& edges) {
        for (vector<int>& e : edges) {
            adj[e[0] - 1].push_back(e[1] - 1);
            adj[e[1] - 1].push_back(e[0] - 1);
        }
    }

    void processHeight(int v, int p, int h) {
        heights[v] = h;
        for (int next : adj[v]) {
            if (next == p) continue;
            processHeight(next, v, h + 1);
        }
    }
};

int main() {
    vector<vector<int>> edges = {{1,2},{1,3},{3,4},{3,5}};
    vector<vector<int>> queries = {{1,4},{3,4},{2,5}};
    vector<int> out = Solution().assignEdgeWeights(edges, queries);
    for (int x : out) cout << x << " "; cout << endl;
}