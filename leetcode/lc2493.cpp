#include <bits/stdc++.h>
using namespace std;

// consider a connected component
// if it is possible to partition into groups, then we can start from any node
// if we start from a root, and it fails, then no matter what other root we choose from this CC, it will still fail

// we partition nodes into group i, where i is the dist from root, so root is in group 0, root's neighbours in group 1...

class Solution {
public:
    vector<vector<int>> adj;
    
    vector<int> myCC;
    unordered_map<int, int> store;
    
    void getAdj(int n, vector<vector<int>>& edges) {
        adj = vector(n + 1, vector<int>());
        for (vector<int>& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
    }

    // bfs from all nodes (any of the node can be a root), also mark nodes visited
    // with the CC they are in
    int bfs(int n, int root, int cc) {
        vector<int> dists(n + 1, -1);
        dists[root] = 0;
        if (myCC[root] == -1) myCC[root] = cc;
        
        queue<int> q;
        q.push(root); 

        int currlvl = 0;
        while (!q.empty()) {
            int l = q.size();
            for (int i = 0; i < l; i ++) {
                int v = q.front(); q.pop();
                
                for (int c : adj[v]) {
                    if (dists[c] == currlvl) {
                        store[myCC[root]] = -1;
                        return -1;
                    } else if (dists[c] == -1) {
                        dists[c] = currlvl + 1;
                        if (myCC[c] == -1)  myCC[c] = cc;
                        
                        q.push(c);
                    }
                }
            }
            
            currlvl += 1;
        }

        store[myCC[root]] = max(store[myCC[root]], currlvl);
        return currlvl;
    }

    int magnificentSets(int n, vector<vector<int>>& edges) {
        myCC = vector(n + 1, -1);
        getAdj(n, edges);

        for (int i = 1; i <= n; i ++) {
            int ans = bfs(n, i, i);
        }

        int sum = 0;
        for (auto& p : store) {
            if (p.second == -1) return -1; // if any CC fail, then cannot partition into groups already
            sum += p.second;
        }
        
        return sum;

    }
};

int main() {
    int n = 6;
    vector<vector<int>> edges = {{1,2},{1,4},{1,5},{2,6},{2,3},{4,6}};

    Solution sol;
    cout << sol.magnificentSets(n, edges);
}

