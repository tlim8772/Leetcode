#include <bits/stdc++.h>
using namespace std;

// bitmask dp

class Solution {
public:
    int LEN;
    vector<int> dp;
    
    vector<vector<int>> adj;
    vector<int> inDeg;

    void process(vector<vector<int>>& edges) {
        for (vector<int>& e : edges) {
            adj[e[0]].push_back(e[1]);
            inDeg[e[1]]++;
        }
    }

    int helper(int bm, int pos, const vector<int>& score) {
        if (dp[bm] != -1) {
            return dp[bm];
        } else if (bm == (1 << LEN) - 1) {
            dp[bm] = 0;
            return 0;
        }

        int best = 0;
        for (int i = 0; i < LEN; i++) {
            if ((bm >> i) & 1 || inDeg[i] != 0) continue;

            for (int next : adj[i]) {
                inDeg[next]--;
            }
            
            int res = score[i] * (pos + 1) + helper(bm + (1 << i), pos + 1, score);
            best = max(best, res);

            for (int next : adj[i]) {
                inDeg[next]++;
            }
        }

        dp[bm] = best;
        return best;
    }

    int maxProfit(int n, vector<vector<int>>& edges, vector<int>& score) {
        LEN = n;
        dp = vector(1 << n, -1);
        
        adj = vector(n, vector<int>());
        inDeg = vector(n, 0);

        process(edges);

        int ans = helper(0, 0, score);

        return ans;
    }
};

int main() {
    Solution sol;

    int n = 3;
    vector<vector<int>> edges = {{0,1},{0,3}};
    vector<int> score = {1,6,3};

    int ans = sol.maxProfit(n, edges, score);
    cout << ans << endl;
}