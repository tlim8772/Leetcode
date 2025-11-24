#include <bits/stdc++.h>
using namespace std;
using ll = long long;


// euler tour and segment tree. Since addition has an inverse, we can put -weight to negate the sum of euler path
// over subtrees we do not need. 
// If no negation, have to use heavy light decomposition

struct SegTree {
    int len;
    vector<int> tree;

    SegTree() {}

    SegTree(int len): len(len), tree(4 * len, 0) {}

    void insert(int p, int s, int e, int i, int v) {
        if (s == e) {
            tree[p] = v;
            return;
        }

        int m = (s + e) >> 1;
        if (i <= m) {
            insert((p << 1) + 1, s, m, i, v);
        } else {
            insert((p << 1) + 2, m + 1, e, i, v);
        }
        tree[p] = tree[(p << 1) + 1] + tree[(p << 1) + 2];
    }

    int query(int p, int s, int e, int l, int r) {
        if (s == e || (s == l) && (e == r)) {
            return tree[p];
        }

        int m = (s + e) >> 1;
        if (r <= m) {
            return query((p << 1) + 1, s, m, l, r);
        } else if (l > m) {
            return query((p << 1) + 2, m + 1, e, l, r);
        } else {
            return query((p << 1) + 1, s, m, l, m) + query((p << 1) + 2, m + 1, e, m + 1, r);
        }
    }
};



class Solution {
public:
    int N;
    vector<vector<pair<int, int>>> adj;
    
    vector<int> startPos;
    unordered_map<ll, pair<int, int>> positions;
    
    SegTree st;
    int curr = 0;

    ll coor(int u, int v) {
        if (u > v) swap(u, v);
        return (ll) u * N + v;
    }
    void getAdj(int n, vector<vector<int>>& edges) {
        adj = vector(n, vector<pair<int, int>>());
        for (vector<int>& e : edges) {
            adj[e[0] - 1].push_back({e[1] - 1, e[2]});
            adj[e[1] - 1].push_back({e[0] - 1, e[2]});
        }
    }

    // everything here is 0 indexed
    void eulerTour(int v, int p) {
        startPos[v] = curr - 1;
        for (pair<int, int>& c : adj[v]) {
            if (c.first == p) continue;
            
            ll pos = coor(v, c.first);
            int start = curr++;
            
            st.insert(0, 0, st.len - 1, start, c.second);
            eulerTour(c.first, v);

            int end = curr++;
            st.insert(0, 0, st.len - 1, end, -c.second);

            positions[pos] = {start, end};
        }
    }

    int queryDist(int v) {
        if (v == 0) return 0;
        int pos = startPos[v];
        
        int d = st.query(0, 0, st.len - 1, 0, pos);
        return d;
    }

    void modifyEdge(int u, int v, int val) {
        if (u > v) swap(u, v);
        
        pair<int, int> startEnd = positions[coor(u, v)];
        st.insert(0, 0, st.len - 1, startEnd.first, val);
        st.insert(0, 0, st.len - 1, startEnd.second, -val);
    }

    vector<int> treeQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        N = n;
        getAdj(n, edges);

        st = SegTree(2 * n);
        startPos = vector(n, -1);
        eulerTour(0, 0);

        vector<int> out;
        for (vector<int>& q : queries) {
            if (q[0] == 1) {
                modifyEdge(q[1] - 1, q[2] - 1, q[3]);
            } else {
                int ans = queryDist(q[1] - 1);
                out.push_back(ans);
            }
        }

        return out;
    }
};

int main() {
    Solution sol;

    int n = 3;
    vector<vector<int>> edges = {{1,2,2},{1,3,4}};
    vector<vector<int>> queries = {{2,1},{2,3},{1,1,3,7},{2,2},{2,3}};

    vector<int> ans = sol.treeQueries(n, edges, queries);
    for (int a : ans) cout << a << endl;
}
