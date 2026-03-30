#include <bits/stdc++.h>
using namespace std;

// small to large merging union find, cannot use normal path compression and small to large merging.
// odd is 1, even is 0.

// since cycles must have even weight,
// consider all paths from u to v. 
// 1. The weights of these path is all odd or all even.
// otherwise, we can form an odd cycle.
// hence the parity of paths from u to v never change.

// for each connected component, consider the root and consider the earliest tree formed
// the parity of paths from root to all other nodes do not change.

// suppose we connect u and v for the 1st time.
// the roots of connected component (CC) of u and root of CC of v is different.
// we merge CC_u to CC_v
// want to know the parity of path from nodes in CC_u to root of CC_v
// it is p ^ par_u ^ w (weight of new edge) ^ par_v.
// it does not when the LCA between u and x (x is another node in CC_u) is not the root of CC_u
// the parity of path from u to x is par_x ^ par_u, (parity of path from node to CC_u).
// In fact, the LCA can be x or u itself.
// Just prove by exhaustion.

// when checking new edge, if nw edge is between 2 different CC, add the edge.
// Else, check the parity of path from u to v and the parity of the edge.
// If match (i.e even and even or odd and odd) then can add, otherwise no.

struct DSU {
    vector<int> ps, ws;
    vector<unordered_map<int, bool>> store;

    DSU(int n): ps(n, 0), ws(n, 1), store(n, unordered_map<int, bool>()) {
        for (int i = 0; i < n; i++) {
            ps[i] = i;
            store[i][i] = 0;
        }
    }

    int find(int u) {
        return (ps[u] == u) ? u : ps[u] = find(ps[u]);
    };

    void join(int u, int v, bool w) {
        int pu = find(u), pv = find(v);
        if (pu == pv) return;
        int &wu = ws[pu], &wv = ws[pv];

        if (wu < wv) {
            ps[pu] = pv;
            wv += wu;

            bool par_u = store[pu][u], par_v = store[pv][v];
            for (auto [n, p] : store[pu]) {
                // no need to care about u, if we do u
                // p == par_u so p ^ par_u = 0.
                store[pv][n] = p ^ par_u ^ w ^ par_v;
            }
        } else {
            ps[pv] = pu;
            wu += wv;

            bool par_v = store[pv][v], par_u = store[pu][u];
            for (auto [n, p] : store[pv]) {
                store[pu][n] = p ^ par_v ^ w ^ par_u;
            }
        }
    }
};

class Solution {
public:
    int numberOfEdgesAdded(int n, vector<vector<int>>& edges) {
        DSU dsu(n);

        int sum = 0;
        for (auto& arr : edges) {
            int u = arr[0], v = arr[1], w = arr[2];
            
            int pu = dsu.find(u), pv = dsu.find(v);
            if (pu != pv) {
                sum++;
                dsu.join(u, v, w);
            } else {
                int par_u = dsu.store[pu][u], par_v = dsu.store[pu][v];
                if (par_u ^ par_v ^ w == 0) sum++;
            }
        }

        return sum;
    }
};

int main() {
    Solution sol;
    int n = 3;
    vector<vector<int>> edges = {{0,1,1}, {1,2,1}, {0,2,1}};
    int ans = sol.numberOfEdgesAdded(n, edges);
    cout << ans << endl;
}

