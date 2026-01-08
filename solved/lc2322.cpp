#include <bits/stdc++.h>
using namespace std;

// 2 cases
// case 1: the edges chosen lie on a single path from root (at node 0) to a leaf.
// for this we can just do O(n^2) dfs.
// i.e dfs(v, p, cutsLeft).
// at each child, we can cut or dont cur

// case 2: the edges do not lie on a single path from root to a leaf.
// for this we do subtree merging.
// each dfs returns the vector of the subtree when we cut.
// when merging child a to the cumulative result (e.g child b, c, d), we just test all possibilities.
// e.g take edge_i of child a with edge_j of child c/

class Solution {
public:
    vector<vector<int>> adj;
    vector<int> treeXOR;
    vector<int> store1;
    int best = 999999999;

    void makeAdj(int n, vector<vector<int>>& edges) {
        adj = vector(n, vector<int>());
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
    }

    int dfsXOR(int v, int p, const vector<int>& nums) {
        int res = nums[v];
        for (int c : adj[v]) {
            if (c == p) continue;
            res ^= dfsXOR(c, v, nums);
        }
        treeXOR[v] = res;
        return res;
    }

    int helper1(const vector<int>& store) {
        if (store.size() < 3) throw invalid_argument("store needs to have 3 elems");

        int a = store[0] ^ store[1], b = store[1] ^ store[2], c = store[2];
        return max({a, b, c}) - min({a, b, c});
    }

    void dfs1(int v, int p, int cuts, const vector<int>& nums) {
        if (v == p) store1.push_back(treeXOR[v]);

        for (int c : adj[v]) {
            if (c == p) continue;
            
            dfs1(c, v, cuts, nums);

            store1.push_back(treeXOR[c]);
            if (cuts - 1 == 0) {
                int res = helper1(store1);
                best = min(best, res);
            } else {
                dfs1(c, v, cuts - 1, nums);
            }
            store1.pop_back();
        }

        if (v == p) store1.pop_back();
    }

    vector<int> dfs2(int v, int p, const vector<int>& nums) {
        vector<int> cuts;

        for (int c : adj[v]) {
            if (c == p) continue;
            vector<int> res = dfs2(c, v, nums);
            res.push_back(treeXOR[c]);

            for (int x : res) {
                for (int cut : cuts) {
                    int a = treeXOR[0] ^ cut ^ x;
                    int ans = max({a, cut, x}) - min({a, cut, x});
                    best = min(best, ans);
                }
            }

            for (int x : res) cuts.push_back(x);
        }

        return cuts;
    }


    int minimumScore(vector<int>& nums, vector<vector<int>>& edges) {
        makeAdj(nums.size(), edges);
        treeXOR = vector(nums.size(), 0);

        dfsXOR(0, 0, nums);
        //for (int x : treeXOR) cout << x << " ";
        //cout << endl;
        dfs1(0, 0, 2, nums);
        //cout << best << endl;
        dfs2(0, 0, nums);

        return best;
    }
};

int main() {
    Solution sol;

    vector<int> nums = {5,5,2,4,4,2};
    vector<vector<int>> edges = {{0,1},{1,2},{5,2},{4,3},{1,3}};

    int ans = sol.minimumScore(nums, edges);
    cout << ans << endl;
}