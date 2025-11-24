#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// it is a tree, so do recursion
// we have to make the subtrees have equal root (root of subtree) to leaf paths
// if we want to have path to all leafs have equal length for the current node
// let say node 0 has 2 childs, 1 and 2
// for 1 cost is 10 (10 nodes need to have their cost increased), and path len is 10
// for 2, cost is 5, and path len is 5
// need to add 5 to node 2

class Solution {
public:
    vector<vector<int>> adj;
    vector<pair<int,ll>> store;;

    void processAdj(const vector<vector<int>>& edges) {
        for (const vector<int>& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
    }

    void dfs(int n, int p, const vector<int>& vals) {
        int sum = 0;
        int cnt = 0;
        ll maxlen = 0;
        for (int c : adj[n]) {
            if (c == p) continue;
            
            dfs(c, n, vals);
            sum += store[c].first;
            cnt++;
            maxlen = max(maxlen, store[c].second);
        }

        for (int c : adj[n]) {
            if (c == p) continue;
            sum += (maxlen > store[c].second);
        }

        store[n] = pair{sum, maxlen + vals[n]};
    }

    int minIncrease(int n, vector<vector<int>>& edges, vector<int>& cost) {
        adj = vector(n, vector<int>());
        store = vector(n, pair<int,ll>{});

        processAdj(edges);

        dfs(0, 0, cost);
        return store[0].first;
    }
};

int main() {
    Solution sol;

    int n = 3;
    vector<vector<int>> edges = {{0,1},{0,2}};
    vector<int> cost = {2,1,3};

    cout << sol.minIncrease(3, edges, cost);

}