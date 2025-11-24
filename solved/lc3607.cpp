#include <bits/stdc++.h>
using namespace std;

// simple, just dfs each connected component, store the ids in a set

class Solution {
public:
    vector<set<int>> sets;
    vector<vector<int>> adj;
    vector<int> myId;

    void processAdj(const vector<vector<int>>& connections) {
        for (const vector<int> e : connections) {
            adj[e[0] - 1].push_back(e[1] - 1);
            adj[e[1] - 1].push_back(e[0] - 1);
        }
    }

    void dfs(int v) {
        myId[v] = sets.size() - 1;
        sets.back().insert(v);

        for (int next : adj[v]) {
            if (myId[next] != -1) continue;
            dfs(next);
        }
    }

    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {
        adj = vector(c, vector<int>());
        myId = vector(c, -1);

        processAdj(connections);

        for (int i = 0; i < c; i++) {
            if (myId[i] != -1) continue;
            sets.emplace_back();
            dfs(i);
        }

        vector<int> ans;
        for (const vector<int> q : queries) {
            int v = q[1] - 1;
            int id = myId[v];
            set<int>& mySet = sets[id];
            
            if (q[0] == 1) {
                if (mySet.contains(v)) {
                    ans.push_back(q[1]);
                } else if (mySet.size() == 0) {
                    ans.push_back(-1);
                } else {
                    ans.push_back(*mySet.begin() + 1);
                }
            } else {
                mySet.erase(v);
            }
        }

        return ans;
    }
};

int main() {
    Solution sol;

    int c = 5;
    vector<vector<int>> connections = {{1,2},{2,3},{3,4},{4,5}};
    vector<vector<int>> queries = {{1,3},{2,1},{1,1},{2,2},{1,2}};

    vector<int> ans = sol.processQueries(c, connections, queries);
    for (int x : ans) {
        cout << x << " ";

    }
    cout << endl;
}