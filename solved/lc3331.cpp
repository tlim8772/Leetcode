#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> adj;
    vector<int> newParents;

    void process(vector<int>& parents) {
        adj = vector(parents.size(), vector<int>());
        newParents = vector(parents.size(), -1);
        
        for (int i = 0; i < parents.size(); i ++) {
            if (parents[i] == -1) continue;
            adj[i].push_back(parents[i]);
            adj[parents[i]].push_back(i);
        }
    }

    void dfs(int v, int p, vector<int>& charNode, string& s) {
        newParents[v] = charNode[s[v] - 'a'];
        int prev = charNode[s[v] - 'a'];
        charNode[s[v] - 'a'] = v;

        for (int c : adj[v]) {
            if (c == p) continue;
            dfs(c, v, charNode, s);
        }

        charNode[s[v] - 'a'] = prev;
    }

    void process2(vector<int>& parents) {
        for (vector<int>& arr : adj) arr.clear();
        for (int i = 0; i < newParents.size(); i ++) {
            if (newParents[i] == -1) {
                if (parents[i] == -1) continue;
                adj[i].push_back(parents[i]);
                adj[parents[i]].push_back(i);
            } else {
                adj[i].push_back(newParents[i]);
                adj[newParents[i]].push_back(i);
            }
        }
    }

    int dfs2(int v, int p, vector<int>& store) {
        int w = 1;
        for (int c : adj[v]) {
            if (c == p) continue;
            w += dfs2(c, v, store);
        }
        store[v] = w;
        return w;
    }
    
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        process(parent);

        vector<int> charNode = vector(26, -1);
        dfs(0, 0, charNode, s);

        process2(parent);

        vector<int> store(parent.size(), 0);
        dfs2(0, 0, store);
        return store;
    }
};

int main() {
    Solution sol;
    vector<int> parent = {-1,0,0,1,1,1};
    string s = "abaabc";

    vector<int>&& out = sol.findSubtreeSizes(parent, s);

}