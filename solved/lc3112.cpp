#include <bits/stdc++.h>
using namespace std;

/*
simple dijkstra, just take not of when nodes disappear
*/

class Solution {
public:
    int n;
    vector<vector<pair<int,int>>> adj;
    vector<int> disappear;

    void make_adj(int n, vector<vector<int>>& edges) {
        adj = vector(n, vector<pair<int,int>>());
        for (auto& e : edges) {
            adj[e[0]].emplace_back(e[1], e[2]);
            adj[e[1]].emplace_back(e[0], e[2]);
        }
    }

    vector<int> dijkstra() {
        auto cmp = [] (const pair<int,int> p1, const pair<int,int> p2) { return p1.second > p2.second; };
        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq(cmp);
        vector<int> results(n, -1);

        pq.emplace(0, 0);
        while (!pq.empty()) {
            auto [node, t] = pq.top(); pq.pop();
            if (results[node] != -1) continue;
            results[node] = t;
            for (auto [next, time] : adj[node]) {
                if (results[next] != -1) continue;
                if (t + time < disappear[next]) {
                    pq.emplace(next, t + time);
                }
            }
        }
        return results;
    }
    
    vector<int> minimumTime(int n, vector<vector<int>>& edges, vector<int>& disappear) {
        this->n = n;
        make_adj(n, edges);
        this->disappear = disappear;
        return dijkstra();
    }

};

int main() {
    Solution sol;
    
    int n = 3;
    vector<vector<int>> edges = {{0,1,2},{1,2,1},{0,2,4}};
    vector<int> disappear = {1,1,5};

    vector<int> ans = sol.minimumTime(n, edges, disappear);
    for (int x : ans) cout << x << " ";
    cout << endl;
}