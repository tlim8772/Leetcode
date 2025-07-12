#include <bits/stdc++.h>
using namespace std;

// simple dijkstra, just take note of the time requirements

struct Edge {
    int v, s, e;
};

class Solution {
public:
    vector<vector<Edge>> adj;

    void processAdj(vector<vector<int>>& edges) {
        for (const vector<int>& e : edges) {
            adj[e[0]].push_back(Edge{e[1], e[2], e[3]});
        }
    }


    int dijkstra(int n) {
        vector<int> dists(n, -1);
        
        auto cmp = [](const pair<int,int>& p1, const pair<int,int>& p2) { return p1.second > p2.second; };
        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq(cmp);
        
        pq.push(pair{0, 0});
        while (!pq.empty()) {
            const auto [node, d] = pq.top(); pq.pop();
            if (dists[node] != -1) continue;
            
            dists[node] = d;
            if (node == n - 1) break;
            
            for (const Edge& e : adj[node]) {
                const auto& [next, start, end] = e;
                if (dists[next] != -1 || d > end) continue;
                
                int nextD = (d < start) ? start + 1 : d + 1;
                pq.push(pair{next, nextD});
            }

        }
        
        return dists[n - 1];
    }

    int minTime(int n, vector<vector<int>>& edges) {
        adj = vector(n, vector<Edge>());
        processAdj(edges);

        int ans = dijkstra(n);
        return ans;
    }
};

int main() {
    Solution sol;

    int n = 5;
    vector<vector<int>> edges = {{2,1,1,14},{0,2,15,16},{1,4,1,11},{1,4,4,25},{0,2,17,21},{3,0,13,22},{3,2,15,18},{2,4,3,23},{1,3,11,12}};

    int ans = sol.minTime(n, edges);
    cout << ans << endl;
}