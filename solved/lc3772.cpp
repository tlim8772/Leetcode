#include <bits/stdc++.h>
using namespace std;

// 2-phase dfs on tree.
// root the tree on node 0.
// phase 1 is to find the best result for the subtree rooted at node i.
// for c in children(i), only take subtree rooted at c if score(c) > 0.
// for phase 2, find the best score if the tree is rooted at node i
// if i is not 0, then consider p, parent of i. If best score for p includes i, we need to substract
// then if the new result of p (without taking subtree i) is > 0, we add it to score(i).

class Solution {
public:
    vector<int> good;
    vector<vector<int>> adj;
    vector<unordered_set<int>> my_sets;
    vector<int> my_sums;

    void make_adj(int n, vector<vector<int>>& edges) {
        adj = vector(n, vector<int>());
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
    }

    int dfs1(int v, int p) {
        int& sum = my_sums[v];
        for (int c :  adj[v]) {
            if (c == p) continue;
            int res = dfs1(c, v);
            if (res > 0) {
                sum += res;
                my_sets[v].insert(c);
            }
        }
        
        sum += (good[v] == 1) ? 1 : -1;
        return sum;
    }

    void dfs2(int v, int p) {
        if (v != p) {
            int p_res = my_sums[p];
            
            if (my_sets[p].contains(v)) {
                p_res -= my_sums[v];
            }
            
            if (p_res > 0) {
                my_sums[v] += p_res;
            }
        }

        for (int c : adj[v]) {
            if (c == p) continue;
            dfs2(c, v);
        }
    }
   
    vector<int> maxSubgraphScore(int n, vector<vector<int>>& edges, vector<int>& good) {
        this->good = good;
        make_adj(n, edges);
        my_sets = vector(n, unordered_set<int>());
        my_sums = vector(n, 0);

        dfs1(0, 0);
        dfs2(0, 0);

        return my_sums;
    }
};

int main() {
    Solution sol;
    int n = 5;
    vector<vector<int>> edges = {{1,0},{1,2},{1,3},{3,4}};
    vector<int> good = {0,1,0,1,1};

    vector<int> ans = sol.maxSubgraphScore(n, edges, good);
    for (int x : ans) cout << x << " ";
    cout << endl;
}