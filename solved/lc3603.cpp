#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// simple dp;

class Solution {
public:
    int M, N;
    vector<ll> store;

    inline int coor(int side, int m, int n) {
        return side * M * N + m * N + n;
    }

    inline bool isValid(int m, int n) {
        return m >= 0 && m < M && n >= 0 && n < N;
    }

    // side == 1 for odd seconds, side == 0 for even seconds
    ll dp(int side, int m, int n, const vector<vector<int>>& waitCost) {
        int pos = coor(side, m, n);
        if (m == M - 1 && n == N - 1) {
            return 0;
        } else if (store[pos] != -1) {
            return store[pos];
        }

        int cost = (m == 0 && n == 0) ? 1 : 0; // handle case when we are at (0, 0)
        ll ans = 1e15;
        if (side == 0) {
            ans = cost + waitCost[m][n] + dp(1, m, n, waitCost);
        } else {
            int m1 = m + 1, n1 = n;
            if (isValid(m1, n1)) {
                ans = cost + (m1 + 1) * (n1 + 1) + dp(0, m1, n1, waitCost);
            }

            int m2 = m, n2 = n + 1;
            if (isValid(m2, n2)) {
                ans = min(ans, cost + (m2 + 1) * (n2 + 1) + dp(0, m2, n2, waitCost));
            }
        }
        store[pos] = ans;
        return ans;

    }

    long long minCost(int m, int n, vector<vector<int>>& waitCost) {
        M = m, N = n;
        store = vector<ll>(2 * M * N, -1L);

        ll ans = dp(1, 0, 0, waitCost);
        return ans;

    }
};

int main() {
    Solution sol;

    int m = 1, n = 2;
    vector<vector<int>> waitCost = {{1,2}};

    int ans = sol.minCost(m, n, waitCost);
    cout << ans << endl;
}