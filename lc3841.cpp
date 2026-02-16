#include <bits/stdc++.h>
using namespace std;

// use tarjan offline lca and heavy light decomposition.

struct UnionFind {
    vector<int> parents, weights, assigned;

    UnionFind(int n): parents(n, 0), weights(n, 1), assigned(n, -1) {
        for (int i = 0; i < n; i++) parents[i] = i;
    }

    int find_root(int v) {
        return parents[v] == v ? v : parents[v] = find_root(parents[v]);
    }

    int find_assigned(int v) {
        return assigned[find_root(v)];
    }

    void assign_to_root(int v, int val) {
        assigned[find_root(v)] = val;
    }

    void join(int u, int v) {
        int pu = find_root(u), pv = find_root(v);
        if (pu == pv) return;
        int& wu = weights[pu], &wv = weights[pv];
        if (wu < wv) return join(v, u);
        parents[pv] = pu;
        wu += wv;
    }
};

struct PairHash {
    size_t operator()(const std::pair<int,int>& p) const noexcept {
        size_t h1 = p.first, h2 = p.second;
        return (h1 << 32) + h2;
    }
};

struct TarjanLca {
    static vector<int> get_lca(int n, const vector<vector<int>>& adj, const vector<vector<int>>& queries) {
        vector<bool> visited(n, false);
        vector<vector<int>> my_queries(n, vector<int>());
        UnionFind uf(n);
        unordered_map<pair<int, int>, int, PairHash> store;
        

        for (auto& q : queries) {
            my_queries[q[0]].push_back(q[1]);
            my_queries[q[1]].push_back(q[0]);
        }

        dfs(0, -1, visited, adj, my_queries, uf, store);

        vector<int> out(queries.size(), 0);
        for (int i = 0; i < queries.size(); i++) {
            auto& q = queries[i];
            out[i] = store[{min(q[0], q[1]), max(q[0], q[1])}];
        }

        return out;
    }
   
    static void dfs(
        int v, 
        int p, 
        vector<bool>& visited,
        const vector<vector<int>>& adj, 
        const vector<vector<int>>& my_queries, 
        UnionFind& uf, 
        unordered_map<pair<int,int>, int, PairHash>& store
    ) {
        visited[v] = true;
        uf.assign_to_root(v, v);
        for (int c : adj[v]) {
            if (c == p) continue;
            dfs(c, v, visited, adj, my_queries, uf, store);
            uf.join(c, v);
            uf.assign_to_root(v, v);
        }
        for (int u : my_queries[v]) {
            if (!visited[u]) continue;
            int lca = uf.find_assigned(u);
            store[{min(u, v), max(u, v)}] = lca;
        }
    } 
};

void test_lca() {
    int n = 7;
    vector<vector<int>> adj = {{1,4}, {0,2,3}, {1}, {1}, {0,5}, {4}, {4}};
    vector<vector<int>> queries = {{2, 0}, {2,5}, {3,5}, {2,3}};
    vector<int> out = TarjanLca::get_lca(n, adj, queries);
    assert(out == vector<int>({0, 0, 0, 1}));

    n = 8;
    adj = {{1,5}, {2,3,4}, {1}, {1}, {1}, {0,6,7}, {5}, {5}};
    queries = {{2,3}, {4,7}, {6,5}, {7,6}};
    out = TarjanLca::get_lca(n, adj, queries);
    assert(out == vector<int>({1,0,5,5}));
}

template <typename T, typename Reducer>
struct SegTree {
    int len;
    vector<T> tree;
    Reducer reducer;

    SegTree(int len): len(len), tree(4 * len, T()) {}

    SegTree(const vector<T>& arr): SegTree(arr, Reducer()) {}

    SegTree(const vector<T>& arr, Reducer reducer): len(arr.size()), tree(4 * len, T()), reducer(reducer) {
        build(arr);
    }

    int left(int p) {
        return (p << 1) + 1;
    }

    int right(int p) {
        return (p << 1) + 2;
    }

    void build(const vector<T>& arr, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;
        if (s == e) {
            tree[p] = arr[s];
            return;
        }
        int m = (s + e) >> 1;
        build(arr, left(p), s, m);
        build(arr, right(p), m + 1, e);
        tree[p] = reducer(tree[left(p)], tree[right(p)]);
    }

    void point_update(int i, T val, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;
        if (s == e) {
            tree[p] = val;
            return;
        }
        int m = (s + e) >> 1;
        if (i <= m) {
            point_update(i, val, left(p), s, m);
        } else {
            point_update(i, val, right(p), m + 1, e);
        }
        tree[p] = reducer(tree[left(p)], tree[right(p)]);
    }

    T range_query(int l, int r, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;
        if (s == l && e == r) {
            return tree[p];
        }
        int m = (s + e) >> 1;
        if (r <= m) {
            return range_query(l, r, left(p), s, m);
        } else if (l > m) {
            return range_query(l, r, right(p), m + 1, e);
        } else {
            T lres = range_query(l, m, left(p), s, m);
            T rres = range_query(m + 1, r, right(p), m + 1, e);
            return reducer(lres, rres);
        }
    }
};

void test_seg_tree() {
    vector<int> arr = {0,1,2,3,4};
    SegTree<int, function<int(int,int)>> st(arr, [](int x, int y) -> int { return x + y; });
    assert(st.range_query(1, 3) == 6);
    
    st.point_update(2, 10);
    assert(st.range_query(1, 3) == 14);
    assert(st.range_query(0, 4) == 18);

    st.point_update(1, 20);
    assert(st.range_query(1, 1) == 20);
    assert(st.range_query(0, 2) == 30);
}

int main() {
    //test_lca();
    test_seg_tree();
}