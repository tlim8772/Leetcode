#include <bits/stdc++.h>
using namespace std;

// dp(node, t): min fee to reach node 0 with t time left
// then do normal dynamic programming

struct Pair {
    int n, t;
};

struct State {
    int n, t, d, num;
};

class Solution {
public:
    int N;
    int maxTime; // i.e if time <= maxTime, it is valid, so range is [0, maxTime]
    vector<int> dp; // the dist here is the fee you are paying
    vector<vector<Pair>> adj;
    //vector<int> fees;

    inline int coor(int n, int t) {
        return n * (maxTime + 1) + t;
    }

    void makeAdj(int n, vector<vector<int>>& edges) {
        adj = vector(n, vector<Pair>());
        for (vector<int> e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
            adj[e[1]].push_back({e[0], e[2]});
        }
    }

    // dp(node, t): min fee to reach node 0 with t time left
    int helper(int n, int t, vector<int>& fees) {
        int pos = coor(n, t);
        
        if (dp[pos] != -1) {
            return dp[pos];
        } else if (n == 0) {
            dp[pos] = fees[0];
            return fees[0];
        } else {
            int best = 999999999;
            for (Pair& p : adj[n]) {
                int newT = t - p.t;
                if (newT < 0) continue;
                
                int res = fees[n] + helper(p.n, newT, fees);
                best = min(best, res);
            }
            dp[pos] = best;
            return best;
        }
    }

    

    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        N = passingFees.size();
        this->maxTime = maxTime;
        dp = vector(N * (maxTime + 1), -1);
        makeAdj(N, edges);

        int best = 999999999;
        for (int t = 1; t <= maxTime; t ++) {
            int res = helper(N - 1, t, passingFees);
            best = min(best, res);
        }

        return (best > 1000000) ? -1 : best;
        
    }
};

int main() {
    Solution sol;
    int maxTime = 29;
    vector<vector<int>> edges = {{0,1,10},{1,2,10},{2,5,10},{0,3,1},{3,4,10},{4,5,15}};
    vector<int> fees = {5,1,2,20,20,3};

    cout << sol.minCost(maxTime, edges, fees) << endl;
}