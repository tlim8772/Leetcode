#include <bits/stdc++.h>
using namespace std;

// simple dp

class Solution {
public:
    int N, K, T; // remember to put t - 1 as it is strictly lesser
    vector<int> dp;

    vector<vector<pair<int, int>>> adj;

    inline int coor(int n, int k, int t) {
        return n * K * T + k * T + t;
    }

    void process(vector<vector<int>>& edges) {
        for (vector<int>& e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
        }
    }

    // k, t always >= 0
    int helper(int n, int k, int t) {
        int pos = coor(n, k, t);
        if (dp[pos] != -1) {
            return dp[pos];
        }

        vector<pair<int, int>>& next = adj[n];
        
        if (k == 0) {
            dp[pos] = 0;
            return dp[pos];
        } 

        int best = -999999999;
        for (pair<int, int>& c : next) {
            int tLeft = t - c.second;
            if (tLeft < 0) continue;
            
            int res = c.second + helper(c.first, k - 1, tLeft);
            best = max(res, best);
        }
        
        dp[pos] = best;
        return best;
    }

    int maxWeight(int n, vector<vector<int>>& edges, int k, int t) {
        N = n, K = k + 1, T = t;
        dp = vector(N * K * T, -1);
        adj = vector(N, vector<pair<int, int>>());

        process(edges);
        

        int best = -999999999;
        for (int i = 0; i < n; i++) {
            int ans = helper(i, k, t - 1);
            //cout << ans << endl;
            best = max(best, helper(i, k, t - 1));
        }

        return max(best, -1);
    }


};

int main() {
    Solution sol;

    int n = 2;
    vector<vector<int>> edges = {{0,1,3}};
    int k = 22;
    int t = 217;

    cout << sol.maxWeight(n, edges, k, t) << endl;
}