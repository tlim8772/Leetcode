#include <bits/stdc++.h>
using namespace std;

// hidden shortest path problem, cost is simply the max edge in a path
// minimise the cost for all paths 0 to n (reverse the edges), then take the maximum
// in this shortest path DAG, each node has 1 (can be more but just need 1) outgoing edge
// to the node that provides the best (smallest) dist

// largest shortest path == smallest max edge value in the graph so that every node still can reach 0

struct Pair {
    int v, d;
};

struct Cmp {
    bool operator()(const Pair p1, const Pair p2) {
        return p1.d > p2.d;
    }
};

class Solution {
public:
    int LEN;
    vector<vector<pair<int, int>>> adj;

    void process(vector<vector<int>>& edges) {
        for (vector<int>& e : edges) {
            adj[e[1]].push_back({e[0], e[2]});
        }
    }

    int dijkstra() {
        vector<int> dist = vector(LEN, -1);
        priority_queue<Pair, vector<Pair>, Cmp> pq;
        
        pq.push({0, 0});

        while (!pq.empty()) {
            Pair next = pq.top(); pq.pop();
            if (dist[next.v] != -1) continue;
            dist[next.v] = next.d;

            for (pair<int, int>& c : adj[next.v]) {
                if (dist[c.first] != -1) continue;
                pq.push({c.first, max(next.d, c.second)});
            }

        }

        int best = 0;
        for (int i = 0; i < LEN; i++) {
            if (dist[i] == -1) return -1;
            best = max(best, dist[i]);
        }
        return best;

    }

    int minMaxWeight(int n, vector<vector<int>>& edges, int threshold) {
        LEN = n;
        adj = vector(n, vector<pair<int, int>>());
        process(edges);

        int ans = dijkstra();
        return ans;
    }
};