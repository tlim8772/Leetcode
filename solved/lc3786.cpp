#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// idea is subtree merging. we process the tree rooted at 0.
// for each subtree we get {ll sum, vector<pair<int,ll>> store}
// sum: sum of all interaction cost within that subtree.
// store: in that subtree, {count of nodes with group i, sum of path length from subtree root to node with group i}

// suppose we are at node i.
// 1st, store[group of node i] = {1, 0}, because have 1 node of that group and path sum is 0.
// now to merge result of child j,
// let [a_cnt, a_path_sum] = store_j[v]
// a_path_sum += a_cnt, to account for the additional edge now (to i)

// now we merge store_j into store_i.
// see code for the formula

class Solution {
public:
    vector<vector<int>> adj;
    vector<int> group;

    void make_adj(int n, vector<vector<int>>& edges) {
        adj = vector(n, vector<int>());
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
    }

    pair<ll, vector<pair<int, ll>>> dfs(int v, int p) {
        ll sum = 0;
        vector<pair<int,ll>> store(21, {0, 0});
        
        store[group[v]] = {1, 0};

        for (int c : adj[v]) {
            if (c == p) continue;

            auto [child_sum, child_store] = dfs(c, v);
            sum += child_sum;

            for (int g = 1; g <= 20; g++) {
                auto [a_cnt, a_path_sum] = child_store[g];
                a_path_sum += a_cnt;
                auto& [b_cnt, b_path_sum] = store[g];

                sum += a_path_sum * b_cnt + b_path_sum * a_cnt;

                b_cnt += a_cnt;
                b_path_sum += a_path_sum;
            }
        }

        return {sum, store};
    }
    
    long long interactionCosts(int n, vector<vector<int>>& edges, vector<int>& group) {
        make_adj(n, edges);
        this->group = group;

        auto [sum, store] = dfs(0, 0);
        return sum;
    }
};

int main() {
    Solution sol;
    
    int n = 3;
    vector<vector<int>> edges = {{0,1},{1,2}};
    vector<int> group = {3,2,3};

    cout << sol.interactionCosts(n, edges, group) << endl;

}