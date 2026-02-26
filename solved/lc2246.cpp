#include <bits/stdc++.h>
using namespace std;

// we dfs from root = node 0.
// for each node i, we return {longest route from node to leaf, longest route within subtree rooted at that node}
// for parent p, longest route from p to leaf is easy to find, take 1st result from children with different chars.
// for 2nd result, take the top 2 longest route from child to leaf for children with different char.

class Solution {
public:
    vector<vector<int>> adj;
    string s;

    vector<vector<int>> make_adj(const vector<int>& parents) {
        vector<vector<int>> adj(parents.size(), vector<int>());
        for (int i = 0; i < parents.size(); i++) {
            if (parents[i] == -1) continue;
            adj[i].push_back(parents[i]);
            adj[parents[i]].push_back(i);
        }
        return adj;
    }

    // returns {longest route from node to leaf, longest route within subtree rooted at that node}
    pair<int, int> dfs(int v, int p) {
        multiset<int> store;
        int subtree_best = 0;
        for (int c : adj[v]) {
            if (c == p) continue;
            
            auto [longest, subtree] = dfs(c, v);
            subtree_best = max(subtree_best, subtree);
            if (s[c] != s[v]) {
                store.insert(longest);
                if (store.size() > 2) store.erase(store.begin());
            }
        }

        while (store.size() < 2) store.insert(0);
       
        int my_longest = 1 + *--store.end();
        int through_me = 1 + *store.begin() + *++store.begin();
       
        subtree_best = max(subtree_best, through_me);

        return {my_longest, subtree_best};
        
    }


    int longestPath(vector<int>& parent, string s) {
        adj = make_adj(parent);
        this->s = s;
        return dfs(0, -1).second;
    }
};

int main() {
    Solution sol;
    vector<int> parent = {-1,0,0,1,1,2};
    string s = "abacbe";

    int ans = sol.longestPath(parent, s);
    cout << ans << endl;
}