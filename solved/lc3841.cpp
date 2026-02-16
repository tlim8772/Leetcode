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

vector<string> split(const string& s) {
    vector<string> out;
    for (auto token : ranges::views::split(s, ' ')) {
        out.push_back(string(token.begin(), token.end()));
    }
    return out;
}

void test_split() {
    string s = "update 2 a";
    vector<string> out = split(s);
    assert(out == vector<string>({"update", "2", "a"}));

    s = "query 1 3";
    out = split(s);
    assert(out == vector<string>({"query", "1", "3"}));
}

template <typename T, typename R> 
struct Hld {
    R reducer;
    vector<int> depths, weights;

    vector<int> node_to_segtree_id;
    vector<int> segtree_next_nodes;
    vector<int> segtree_root_nodes;
    vector<SegTree<T, R>> segtrees;

    Hld(int n, const vector<vector<int>>& adj, const vector<T>& vals): Hld(n, adj, vals, R()) {}

    Hld(int n, const vector<vector<int>>& adj, const vector<T>& vals, R reducer): 
        reducer(reducer),
        depths(n, 0), 
        weights(n, 0) ,
        node_to_segtree_id(n, 0) 
        {
            dfs_depth(0, -1, adj);
            dfs_weights(0, -1, adj);
            
            vector<int> nodes;
            decompose(0, -1, -1, nodes, adj, vals);
        }

    void dfs_depth(int v, int p, const vector<vector<int>>& adj, int depth = 0) {
        depths[v] = depth;
        for (int c : adj[v]) {
            if (c == p) continue;
            dfs_depth(c, v, adj, depth + 1);
        }
    }

    void dfs_weights(int v, int p, const vector<vector<int>>& adj) {
        int sum = 1;
        for (int c : adj[v]) {
            if (c == p) continue;
            dfs_weights(c, v, adj);
            sum += weights[c];
        }
        weights[v] = sum;
    }

    void build_segtree(const vector<int>& nodes, int next_node, const vector<T>& vals) {
        int segtree_id = segtrees.size();
        for (int v : nodes) {
            node_to_segtree_id[v] = segtree_id;
        }
        
        segtree_next_nodes.push_back(next_node);

        segtree_root_nodes.push_back(nodes[0]);
        
        vector<T> node_vals;
        for (int v : nodes) node_vals.push_back(vals[v]);
        
        segtrees.emplace_back(node_vals, reducer);
    }

    void decompose(
        int v, 
        int p, 
        int next_node, 
        vector<int>& nodes, 
        const vector<vector<int>>& adj, 
        const vector<T>& vals) 
    {
        nodes.push_back(v);

        int child_cnt = 0;
        for (int c : adj[v]) child_cnt += (c != p);
        if (child_cnt == 0) {
            build_segtree(nodes, next_node, vals);
            return;
        }

        int heaviest_node = -1, weight = 0;
        for (int c : adj[v]) {
            if (c == p) continue;
            if (weights[c] > weight) {
                heaviest_node = c, weight = weights[c];
            }
        }
        
        decompose(heaviest_node, v, next_node, nodes, adj, vals);

        for (int c : adj[v]) {
            if (c == p || c == heaviest_node) continue;
            vector<int> new_nodes;
            decompose(c, v, v, new_nodes, adj, vals);
        }
    }

    void update_node(int node, T val) {
        int segtree_id = node_to_segtree_id[node];
        auto& st = segtrees[segtree_id];
        int root_node = segtree_root_nodes[segtree_id];
        int idx = depths[node] - depths[root_node];
        st.point_update(idx, val);
    }

    // top and bottom must lie in the path from root to bottom.
    // top and bottom can be equal.
    T range_query(int top, int bottom) {
        T accu = T();
        while (1) {
            int top_seg_id = node_to_segtree_id[top];
            int top_root_node = segtree_root_nodes[top_seg_id];

            int bottom_seg_id = node_to_segtree_id[bottom];
            int bottom_root_node = segtree_root_nodes[bottom_seg_id];

            if (top_seg_id == bottom_seg_id) {
                auto& segtree = segtrees[top_seg_id];
                int left_idx = depths[top] - depths[top_root_node];
                int right_idx = depths[bottom] - depths[bottom_root_node];
                T res = segtree.range_query(left_idx, right_idx);
                accu = reducer(accu, res);
                break;
            } else {
                auto& segtree = segtrees[bottom_seg_id];
                int right_idx = depths[bottom] - depths[bottom_root_node];
                T res = segtree.range_query(0, right_idx);
                accu = reducer(accu, res);
                bottom = segtree_next_nodes[bottom_seg_id];
            }
        }
        return accu;
    }
};

void test_hld() {
    struct Sum {
        int operator()(int x, int y) {
            return x + y;
        }
    };

    int n = 7;
    vector<vector<int>> adj = {{1,2}, {0,3,4}, {0,5,6}, {1}, {1}, {2}, {2}};
    vector<int> vals = {0,1,2,3,4,5,6};
    Hld<int, Sum> hld(n, adj, vals);
    assert(hld.range_query(0, 3) == 4);
    assert(hld.range_query(2, 5) == 7);
    hld.update_node(5, 10);
    assert(hld.range_query(5, 5) == 10);
    assert(hld.range_query(0, 5) == 12);

    n = 8;
    adj = {{1,6,7}, {0,2,5}, {1,3,4}, {2}, {2}, {1}, {0}, {7}};
    vals = {0,1,2,3,4,5,6,7};
    Hld<int, Sum> hld2(n, adj, vals);
    assert(hld2.range_query(1, 5) == 6);
    assert(hld2.range_query(1, 3) == 6);
    hld2.update_node(2, 10);
    assert(hld2.range_query(1, 3) == 14);
}

void test_hld_2() {
    struct Xor {
        bitset<3> operator()(bitset<3> b1, bitset<3> b2) {
            return b1 ^ b2;
        }
    };
    int n = 7;
    vector<vector<int>> adj = {{1,2}, {0,3,4}, {0,5,6}, {1}, {1}, {2}, {2}};
    vector<bitset<3>> vals;
    for (int i = 0; i < n; i++) vals.emplace_back(i);
    Hld<bitset<3>, Xor> hld(n, adj, vals);
    assert(hld.range_query(0, 0) == bitset<3>());
    assert(hld.range_query(0, 3) == bitset<3>(0 ^ 1 ^ 3));
    hld.update_node(2, 7);
    assert(hld.range_query(0, 6) == bitset<3>(0 ^ 7 ^ 6));
}

class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        vector<vector<int>> adj(n, vector<int>());
        vector<bitset<26>> vals;

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        for (char c : s) {
            bitset<26> val;
            val[c - 'a'] = 1;
            vals.push_back(val);
        }

        struct Xor {
            bitset<26> operator()(const bitset<26>& b1,const bitset<26>& b2) const {
                return b1 ^ b2;
            }
        };

        Hld<bitset<26>, Xor> hld(n, adj, vals);

        vector<vector<int>> node_pairs;
        int node_pair_lcas_idx = 0;
        vector<int> node_pair_lcas;

        for (string q : queries) {
            vector<string> splitted = split(q);
            if (splitted[0] == "query") {
                int u = stoi(splitted[1]), v = stoi(splitted[2]);
                node_pairs.push_back({u, v});
            }
        }
        node_pair_lcas = TarjanLca::get_lca(n, adj, node_pairs);

        vector<bool> out;
        for (string q : queries) {
            vector<string> splitted = split(q);
            if (splitted[0] == "update") {
                int u = stoi(splitted[1]);
                char c = splitted[2][0];
                bitset<26> val;
                val[c - 'a'] = 1;
                hld.update_node(u, val);
            } else {
                int lca = node_pair_lcas[node_pair_lcas_idx++];
                int u = stoi(splitted[1]);
                int v = stoi(splitted[2]);

                bitset<26> lca_val = hld.range_query(lca, lca);
                
                bitset<26> left = hld.range_query(lca, u);
                
                bitset<26> right = hld.range_query(lca, v);
                
                bitset<26> res = left ^ right ^ lca_val;
                
                bool ans = res.count() <= 1;
                out.push_back(ans);
            }
        }

        return out;
    }
};
 
int main() {
    //test_lca();
    //test_seg_tree();
    //test_split();
    //test_hld();
    //test_hld_2();

    Solution sol;
    int n = 3;
    vector<vector<int>> edges = {{0,1}, {1,2}};
    string s = "aac";
    vector<string> queries = {"query 0 2", "update 1 b", "query 0 2"};
    vector<bool> out = sol.palindromePath(n, edges, s, queries);

    for (bool a : out) cout << a << " ";
    cout << endl;
}