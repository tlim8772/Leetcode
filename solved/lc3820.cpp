#include <bits/stdc++.h>
using namespace std;

// lets use lca and binary lifting for fun.
// I mean use lca and binary lifting to find dist between node u, v.


// create an LCA rooted at 0.
struct LCA {
    int MAX;
    vector<vector<int>> adj;
    vector<int> depths;
    vector<vector<int>> lifts;

    LCA(int n, const vector<vector<int>>& edges): 
        MAX((int) floor(log2(n)) + 1), 
        adj(n, vector<int>()), 
        depths(n, 0), 
        lifts(n, vector<int>()) 
    {
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        process_depths();
        binary_lift();
    }

    void process_depths(int v = 0, int p = -1, int d = 0) {
        depths[v] = d;
        for (int c : adj[v]) {
            if (c == p) continue;
            process_depths(c, v, d + 1);
        }
    }

    void binary_lift(int v = 0, int p = -1) {
        if (p != -1) {
            auto& my_lift = lifts[v];
            my_lift.push_back(p);
            for (int i = 1; i < MAX; i++) {
                auto& par_lift = lifts[my_lift.back()];
                if (par_lift.size() < i) break;
                my_lift.push_back(par_lift[i - 1]);
            }
        }

        for (int c : adj[v]) {
            if (c == p) continue;
            binary_lift(c, v);
        }
    }

    int get_lca(int u, int v) {
        if (depths[u] < depths[v]) swap(u, v);
        
        for (int j = MAX - 1; j > -1; j--) {
            if (depths[u] - (1 << j) < depths[v]) continue;
            u = lifts[u][j];
        }

        if (u == v) return u;

        for (int j = MAX - 1; j > -1; j--) {
            auto &lift_u = lifts[u], &lift_v = lifts[v];
            if (lift_u.size() <= j || lift_u[j] == lift_v[j]) continue;
            u = lift_u[j], v = lift_v[j];
        }
        return lifts[u][0];
    }

    int get_dist(int u, int v) {
        int lca = get_lca(u, v);
        return depths[u] + depths[v] - 2 * depths[lca];
    }

    void print_depths() {
        for (int i = 0; i < depths.size(); i++) {
            cout << i << ": " << depths[i] << endl;
        }
    }

    void print_lifts() {
        for (int i = 0; i < lifts.size(); i++) {
            cout << i << ": ";
            for (int x : lifts[i]) {
                cout << x << " ";
            }
            cout << endl;
        }
    }
};

class Solution {
public:
    int specialNodes(int n, vector<vector<int>>& edges, int x, int y, int z) {
        LCA lca{n, edges};
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            int dx = lca.get_dist(i, x), dy = lca.get_dist(i, y), dz = lca.get_dist(i, z);
            array<int, 3> arr = {dx, dy, dz};
            sort(arr.begin(), arr.end());
            auto [a, b, c] = arr;

            using ll = long long;
            if ((ll) c * c - (ll) b * b - (ll) a * a == 0) cnt++;
        }
        return cnt;
    }
};

int main() {
    int n = 7;
    vector<vector<int>> edges = {{0,1},{0,2},{1,3},{1,4},{2,5},{2,6}};
    LCA lca{n, edges};

    lca.print_lifts();
    cout << lca.get_lca(3, 6) << endl;
}

