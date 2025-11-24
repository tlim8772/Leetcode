#include <bits/stdc++.h>
using namespace std;

// starting from node k, dfs, add such nodes into a set
// now we can remove all these nodes iff no other nodes not in this set can reach any of the nodes in this set
class Solution {
public:
    vector<bool> isBugged;
    vector<bool> isDependedOn;
    vector<vector<int>> adj;

    void markBug(int v, vector<bool>& visited) {
        visited[v] = true;
        isBugged[v] = true;
        for (int next : adj[v]) {
            if (visited[next]) continue;
            markBug(next, visited);
        }
    }

    bool canVisitBugged(int v, vector<bool>& visited) {
        //cout << v << endl;
        visited[v] = true;
        if (isBugged[v]) return true;
        
        for (int next : adj[v]) {
            if (visited[next]) continue;
            bool ans = canVisitBugged(next, visited);
            if (ans) return ans;
        }

        return false;
    }

    vector<vector<int>> getAdj(int n, vector<vector<int>>& dedges) {
        vector<vector<int>> out(n, vector<int>());
        for (vector<int>& dedge : dedges) {
            out[dedge[0]].push_back(dedge[1]);
        }   
        return out;
    }
    
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        isBugged = isDependedOn = vector(n, false);
        adj = getAdj(n, invocations);
        
        vector<bool> v1(n, false);
        markBug(k, v1);

        vector<bool> v2(n, false);
        bool canReachBug = false;
        for (int i = 0; i < n; i++) {
            if (isBugged[i] || v2[i]) continue;
            canReachBug = canReachBug || canVisitBugged(i, v2);
        }

        //cout << canReachBug << endl;

        vector<int> out;
        for (int i = 0; i < n; i++) {
            if (!canReachBug && isBugged[i]) continue;
            out.push_back(i);
        }

        return out;
    }
};

int main() {
    int n = 3, k = 2;
    vector<vector<int>> edges = {{1,0},{2,0}};
    vector<int> out = Solution().remainingMethods(n, k, edges);
    for (int x : out) cout << x << " "; cout << endl;
}