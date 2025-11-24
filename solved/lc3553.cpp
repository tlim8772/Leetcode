#include <bits/stdc++.h>
using namespace std;

// use binary lifting lca to get dist between vertex x, y
// d(x,y) = d(0,x) + d(0,y) - 2 * d(0, lca)
// the minimum spanning tree containing x, y, z (in a tree !!)
// is (d(x,y) + d(y,z) +d(x,z)) / 2

class Solution {
public:
    int N;
    vector<vector<pair<int,int>>> adj;

    vector<int> dist;
    vector<int> depth;
    
    int MAX_BIN;
    vector<vector<int>> binParents;

    void processAdj(vector<vector<int>>& edges) {
        for (vector<int>& e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
            adj[e[1]].push_back({e[0], e[2]});
        }
    }

    void processBin(int v, int p) {
        if (v != p) {
            binParents[v][0] = p;

            for (int i = 1; i <= MAX_BIN; i++) {
                binParents[v][i] = binParents[binParents[v][i - 1]][i - 1];
                if (binParents[v][i] == -1) break;
            }
        }

        for (pair<int,int> next : adj[v]) {
            if (next.first == p) continue;
            processBin(next.first, v);
        }
    }

    int binJump(int v, int jump) {
        for (int i = 0; i <= MAX_BIN; i++) {
            if (v == -1) break;
            
            if (jump & 1) {
                v = binParents[v][i];
            }

            jump >>= 1;
        }
        return v;
    }

    int lca(int v, int u) {
        if (depth[v] < depth[u]) swap(v, u);
        v = binJump(v, depth[v] - depth[u]);
        if (v == u) return v;

        for (int i = MAX_BIN; i >= 0; i--) {
            if (binParents[v][i] == binParents[u][i]) continue;
            v = binParents[v][i];
            u = binParents[u][i];
        }

        return binParents[v][0];
    }

    int getDist(int u, int v) {
        int p = lca(u, v);
        return dist[u] + dist[v] - 2 * dist[p];
    }



    
    
    
    void dfsDistDepth(int v, int p, int d, int dep) {
        dist[v] = d;
        depth[v] = dep;

        for (pair<int,int> next : adj[v]) {
            if (next.first == p) continue;
            dfsDistDepth(next.first, v, d + next.second, dep + 1);
        }
    }


    vector<int> minimumWeight(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        N = edges.size() + 1;
        adj = vector(N, vector<pair<int,int>>());
        
        dist = vector(N, 0);
        depth = vector(N, 0);

        MAX_BIN = (int) floor(log2(N - 1));
        binParents = vector(N, vector(MAX_BIN + 1, -1));

        processAdj(edges);
        dfsDistDepth(0, 0, 0, 0);
        processBin(0, 0);

        vector<int> out;
        for (vector<int>& q : queries) {
            int ab = getDist(q[0], q[1]), ac = getDist(q[0], q[2]), bc = getDist(q[1], q[2]);
            int sum = ab + ac + bc;
            sum = sum / 2;
            out.push_back(sum);
            
        }


        return out;
    }
};


int main() {
    Solution sol;
    vector<vector<int>> edges = {{0,1,1},{0,2,1},{1,3,1},{1,4,1},{2,5,1},{2,6,1},{3,7,1},{6,8,1}};
    vector<vector<int>> queries = {};

    sol.minimumWeight(edges, queries);


    cout << sol.getDist(0,8) << endl;
}
