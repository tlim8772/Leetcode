#include <bits/stdc++.h>
using namespace std;

// for each node, we want to find the dist to the furthest node.
// do 2-phase dfs.
// when merging 2 trees at node x for t1 and y for t2, the new diameter is
// max(diam T1, diam T2, furthest node from x + furthest node from y + 1).
// i.e diamter is either contained in T1 only, or in T2 only or crosses T1 to T2.
// so join the tree at the nodes where the furthest node distance is the smallest.

struct StoreBest2 {
    vector<pair<int,int>> store;

    void insert(int node, int res) {
        store.emplace_back(node, res);
        sort(store.begin(), store.end(), [] (const auto& p1, const auto& p2) { return p1.second > p2.second; });
        if (store.size() > 2) store.pop_back();
    }

    // node == -1 if you want the furthest node distance.
    int get_best(int node) {
        if (store.empty() || store.size() == 1 && store[0].first == node) return 0;
        return (store[0].first == node) ? store[1].second : store[0].second;
    }
};

struct TreeInfo {
    int n;
    vector<vector<int>> adj;
    int diameter;
    vector<int> maxDist;
    vector<StoreBest2> stores;

    TreeInfo(int n, const vector<vector<int>>& edges): n(n) {
        maxDist = vector(n, 0);
        stores = vector(n, StoreBest2{});
        makeAdj(n, edges);

        dfs1(0, 0);
        dfs2(0, 0);

        for (int i = 0; i < n; i++) maxDist[i] = stores[i].get_best(-1);
        diameter = *max_element(maxDist.begin(), maxDist.end());
    }

    void makeAdj(int n, const vector<vector<int>>& edges) {
        adj = vector(n, vector<int>());
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
    }

    int dfs1(int v, int p) {
        StoreBest2& my_store = stores[v];
        for (int c : adj[v]) {
            if (c == p) continue;
            my_store.insert(c, 1 + dfs1(c, v));
        }
        return my_store.get_best(-1);
    }

    void dfs2(int v, int p) {
        if (v != p) {
            stores[v].insert(p, 1 + stores[p].get_best(v));
        }

        for (int c : adj[v]) {
            if (c == p) continue;
            dfs2(c, v);
        }
    }
};

class Solution {
public:
    int minimumDiameterAfterMerge(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        TreeInfo t1(edges1.size() + 1, edges1), t2(edges2.size() + 1, edges2);
        int d1 = t1.diameter, d2 = t2.diameter;
        int min1 = *min_element(t1.maxDist.begin(), t1.maxDist.end()), 
            min2 = *min_element(t2.maxDist.begin(), t2.maxDist.end());

        return max({d1, d2, min1 + min2 + 1});

    }
};

int main() {
    int n = 8;
    vector<vector<int>> edges = {{0,1},{0,2},{0,3},{2,4},{2,5},{3,6},{2,7}};
    TreeInfo tree_info{n, edges};

    for (int x : tree_info.maxDist) cout << x << " ";
    cout << endl;
}