#include <bits/stdc++.h>
using namespace std;

// use bfs.
// the vertices are the buses. For src, tgt, we find the buses they are in.
// we can switch to another bus if the 2 bus stop sets have a stop in common.
// this adds 1 to the # of buses we need to use.

template <typename T>
bool is_intersect(unordered_set<T>& s0, unordered_set<T>& s1) {
    if (s0.size() > s1.size()) return is_intersect(s1, s0);
    for (const T& t : s0) {
        if (s1.contains(t)) return true;
    }
    return false;
}

class Solution {
public:
    vector<unordered_set<int>> bus_stop_sets;
    vector<vector<int>> adj;
    unordered_set<int> source_buses, target_buses;

    int bfs() {
        int lvl = 1;
        queue<int> q;
        vector<bool> visited(bus_stop_sets.size(), false);
        
        for (int b : source_buses) {
            q.push(b);
        }

        while (!q.empty()) {
            for (int len = q.size(); len > 0; len--) {
                int b = q.front(); q.pop();
                visited[b] = true;
                
                if (target_buses.contains(b)) {
                    //cout << b << " " << lvl << endl;
                    return lvl;
                }
                
                for (int next : adj[b]) {
                    if (visited[next]) continue;
                    q.push(next);
                }
            }
            lvl++;
        }

        return -1;

    }

    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        if (source == target) return 0;

        for (vector<int>& r : routes) {
            bus_stop_sets.emplace_back(r.begin(), r.end());
        }
 
        for (int i = 0; i < bus_stop_sets.size(); i++) {
            if (bus_stop_sets[i].contains(source)) {
                //cout << i << endl;
                source_buses.insert(i);
            }

            if (bus_stop_sets[i].contains(target)) {
                target_buses.insert(i);
            }
        }

        adj = vector(routes.size(), vector<int>());
        for (int i = 0; i < routes.size(); i++) {
            for (int j = i + 1; j < routes.size(); j++) {
                bool res = is_intersect(bus_stop_sets[i], bus_stop_sets[j]);
                if (res) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }

        int ans = bfs();
        return ans;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> routes = {{1,2,7},{3,6,7}};
    int src = 1, tgt = 6;
    cout << sol.numBusesToDestination(routes, src, tgt) << endl;
}