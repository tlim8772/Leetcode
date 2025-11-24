#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// we binary search on the minimum edge
// so only consider edges with cost >= m, then use dijkstra to find the shortest path
// from 0 to n - 1
// if have valid path, we know maxmimum is >= m
// else maximum is < m

class Solution {
public:
    int N;
    vector<vector<pair<int,int>>> adj;

    void processAdj(const vector<vector<int>>& edges) {
        for (const vector<int>& e : edges) {
            adj[e[0]].emplace_back(e[1], e[2]);
        }
    }

    // only consider edges with cost >= m
    // returns shortest path from 0 to n - 1
    // if cannot reach, return -1
    ll dijkstra(int m, int n, const vector<bool>& online) {
        vector<ll> dists(n, -1);

        auto cmp = [](const pair<int,ll>& p1, const pair<int,ll>& p2) {return p1.second > p2.second; };
        priority_queue<pair<int,ll>, vector<pair<int,ll>>, decltype(cmp)>pq(cmp);
        pq.emplace(0, 0);

        while (!pq.empty()) {
            const auto [node, dist] = pq.top(); pq.pop();
            if (dists[node] != -1) continue;

            dists[node] = dist;
            if (node == n - 1) return dist;

            for (const auto& [next, cost] : adj[node]) {
                if (!online[next] || dists[next] != -1 || cost < m) continue;
                pq.emplace(next, cost + dist);
            }
        }
        
        return dists[n - 1];
    }

    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        N = online.size();
        
        adj = vector(online.size(), vector<pair<int,int>>());
        processAdj(edges);

        int s = 0, e = 1e9;
        while (s < e) {
            int m = s + ((e - s + 1) >> 1);
            ll d = dijkstra(m, N, online);
            if (d == -1 || d > k) {
                e = m - 1;
            } else {
                s = m;
            }
        }

        // do a last check
        ll d = dijkstra(s, N, online);
        if (d == -1 || d > k) {
            return -1;
        } else {
            return s;
        }
    }
};