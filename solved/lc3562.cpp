#include <bits/stdc++.h>
using namespace std;

// the graph is a tree, not just a DAG (i.e no cycles even when considering edges as undirected)
// dp(n, i, m, b)
// n: vertex we are considering
// i: the index of children 
// m: budget for this dp state
// b: depends on i. If i is 0 means whether we can get the half price discount, if i > 0
// means whether we buy stock for vertex n or not

// it may seem the TC is O(n^4), but since it is a tree, the index i is amortised (sum to n)
// so the TC is O(n^3), n <= 160


class Solution {
public:
    int N, I, M, B = 2;
    int L1, L2, L3;
    vector<int> dp;

    vector<vector<int>> adj;
    vector<int> present;
    vector<int> future;

    inline int coor(int n, int i, int m, int b) {
        return n * L1 + i * L2 + m * L3 + b;
    }

    void process(vector<vector<int>>& edges) {
        for (vector<int>& e : edges) {
            adj[e[0] - 1].push_back(e[1] - 1);
        }
    }

    int helper(int n, int i, int m, int b) {
        int pos = coor(n, i, m, b);
        if (dp[pos] != -1) {
            return dp[pos];
        } 

        vector<int>& next = adj[n];
        if (i == next.size()) {
            if (next.size() == 0) {
                int price = b ? present[n] / 2 : present[n];
                int profit = future[n] - price;
                
                int res = price <= m ? profit : 0;
                res = max(0, res);
                dp[pos] = res;
                return res;
            } else {
                return 0;
            }
        }

        if (i == 0) {
            int price = b ? present[n] / 2 : present[n];
            int profit = future[n] - price;

            int nobuy = 0;
            for (int s = 0; s <= m; s++) {
                int res = helper(next[0], 0, s, 0) + helper(n, 1, m - s, 0);
                nobuy = max(nobuy, res);
            }

            int buy = 0;
            if (price <= m) {
                int mLeft = m - price;
                for (int s = 0; s <= mLeft; s++) {
                    int res = profit + helper(next[0], 0, s, 1) + helper(n, 1, mLeft - s, 1);
                    buy = max(buy, res);
                }
            }

            int ans = max(nobuy, buy);
            dp[pos] = ans;
            return ans;
        } else {
            int best = 0;
            for (int s = 0; s <= m; s++) {
                int res = helper(next[i], 0, s, b) + helper(n, i + 1, m - s, b);
                best = max(best, res);
            }
            
            dp[pos] = best;
            return best;
        }

    }

    int maxProfit(int n, vector<int>& present, vector<int>& future, vector<vector<int>>& hierarchy, int budget) {
        N = n;
        I = n;
        M = budget + 1;
        L1 = I * M * B, L2 = M * B, L3 = B;
        dp = vector(N * I * M * 2, -1);

        adj = vector(N, vector<int>());
        this->present = present;
        this->future = future;
        
        process(hierarchy);

        int ans = helper(0, 0, budget, 0);
        return ans;

    }
};

int main() {
    Solution sol;

    int n = 2;
    vector<int> present = {17,43};
    vector<int> future = {22,14};
    vector<vector<int>> hierachy = {{1,2}};
    int budget = 6;

    int ans = sol.maxProfit(n, present, future, hierachy, budget);
    cout << ans << endl;
}