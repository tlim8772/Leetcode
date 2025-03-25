#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// problem: for each node, find the longest path starting from that node
// 2 phase dfs. Store best 2 results

struct Pair {
    int n;
    ll l;
};

class Solution {
public:
    int LEN;
    vector<vector<int>> adj;
    vector<int> weights;
    vector<vector<Pair>> best2Arr;

    void insert(vector<Pair>& best2, Pair p) {
        best2.push_back(p);
        sort(best2.begin(), best2.end(), [] (Pair& p1, Pair& p2) { return p1.l > p2.l; });
        if (best2.size() > 2) best2.pop_back();
    }

    ll dfs1(int node, int parent) {
        vector<Pair>& best2 = best2Arr[node];
        for (int c : adj[node]) {
            if (c == parent) continue;
            ll len = weights[node] + dfs1(c, node);
            insert(best2, {c, len});
        }

        

        if (best2.size() == 0) {
            return weights[node];
        } else {
            return best2[0].l;
        }
    }

    void dfs2(int node, int parent) {
        if (node == 0) {
            for (int c : adj[node]) {
                dfs2(c, node);
            }
            return;
        }

        vector<Pair>& best2P = best2Arr[parent]; // size cannot be 0, as we have >= 1 child
        vector<Pair>& best2 = best2Arr[node];
        
        // no need to handle case when node is a leaf (best2 is empty, adding weight of parent will get better score)
        if (best2P.size() == 1) {
            insert(best2, {parent, weights[node] + weights[parent]});
        } else if (best2P[0].n != node) {
            insert(best2, {parent, weights[node] + best2P[0].l});
        } else {
            insert(best2, {parent, weights[node] + best2P[1].l});
        }

        for (int c : adj[node]) {
            if (c == parent) continue;
            dfs2(c, node);
        }

    }

    ll getAns() {
        ll best = 0;
        for (int i = 0; i < LEN; i ++) {
            ll res = (best2Arr[i].size() == 0) ? 0 : best2Arr[i][0].l - weights[i];
            best = max(best, res);
        }
        return best;
    }

    void process(vector<vector<int>>& edges) {
        adj = vector(LEN, vector<int>());
        for (vector<int>& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
    }

    long long maxOutput(int n, vector<vector<int>>& edges, vector<int>& price) {
        LEN = n;
        process(edges);
        weights = price;
        best2Arr = vector(n, vector<Pair>());

        dfs1(0, 0);
        dfs2(0, 0);
        ll ans = getAns();

        return ans;
    }



};

int main() {
    Solution sol;

    int n = 1;
    vector<vector<int>> edges = {};
    vector<int> price = {1};

    cout << sol.maxOutput(n, edges, price) << endl;
}