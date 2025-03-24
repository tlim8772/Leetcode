#include <bits/stdc++.h>
using namespace std;
using ll = long long;


// dp on trees dp[bool][idx] = max sum if edge parent-node is taken or not
// for a state, we could possible remove multiple edges. So which edge to remove
// we consider the diff between dp(false, child) and dp(true, child). if difference 
// is postive, then we remove. We greedily take the diff in descending order

struct Pair {
    int n, w;
};

class Solution {
public:
    ll INVALID = -1e12;
    int LEN, k;
    vector<ll> dp;
    vector<vector<Pair>> adj;

    inline int coor(int state, int node) {
        return state * LEN + node;
    }

    void process(vector<vector<int>> edges) {
        adj = vector(edges.size() + 1, vector<Pair>());
        for (vector<int>& e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
            adj[e[1]].push_back({e[0], e[2]});
        }
    }

    // state == true means parentEdge removed
    ll helper(int state, int node, int parent, int parentEdge) {
        int pos = coor(state, node);
        if (dp[pos] != -1) return dp[pos];

        int deg = (state) ? adj[node].size() - 1 : adj[node].size();
        int toRemove = max(deg - k, 0);

        ll sum = (state) ? 0 : parentEdge;
        vector<ll> diff;
        for (Pair& p : adj[node]) {
            if (p.n == parent) continue;

            ll remove = helper(true, p.n, node, p.w);
            ll noRemove = helper(false, p.n, node, p.w);
            sum += noRemove;
            diff.push_back(remove - noRemove);
        }

        sort(diff.begin(), diff.end(), greater<int>{});
        
        for (int i = 0; i < diff.size(); i ++) {
            if (toRemove > 0) {
                sum += diff[i];
                toRemove --;
            } else if (diff[i] > 0) {
                sum += diff[i];
            } else {
                break;
            }
        }

        dp[pos] = sum;
        return sum;
        
    }

    long long maximizeSumOfWeights(vector<vector<int>>& edges, int k) {
        LEN = edges.size() + 1;
        this->k = k;
        dp = vector<ll>(2 * LEN, -1);

        process(edges);

        ll ans = helper(false, 0, 0, 0);
        return ans;

    }
};

int main() {
    Solution sol;

    vector<vector<int>> edges = {{0,1,4},{0,2,2},{2,3,12},{2,4,6}};
    int k = 2;

    cout << sol.maximizeSumOfWeights(edges, k) << endl;
}