#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1e9 + 7;

// let dp(i, r, c) be the state, i == 1 means we can make 1 move that remains in the same row,
// i == 0 means we have to move to the next row
// just use prefix sum to make range sum queries faster

// dp(0, r, c) can go to dp(1, r, left) ... dp(1, r, rright)
// and also dp(0, r - 1, left2) ... dp(0, r - 1, right2)
// must be careful, should not double count if we decide to stay here, i.e go to dp(1, r, c)

// when r == 0, then dp(1, r, c) is simply sum dp(0, 0, left) ... dp(0, 0, right)

vector<ll> makePrefixSum(const vector<ll>& arr) {
    vector<ll> out(arr.size(), 0);
    out[0] = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        out[i] = (out[i - 1] + arr[i]) % MOD;
    }
    return out;
}

ll query(const vector<ll>& prefix, int l, int r, ll toMinus) {
    if (l == 0) {
        return (prefix[r] - toMinus + MOD) % MOD;
    } else {
        return (prefix[r] - prefix[l - 1] - toMinus + MOD + MOD) % MOD;
    }
}

class Solution {
public:
    int R, C;
    int stayLen, upLen;
    vector<vector<vector<ll>>> store;

    void to_print() {
        for (auto mat : store) {
            for (auto arr : mat) {
                for (auto ans : arr) {
                    cout << ans << " ";
                }
                cout << '\n';
            }
            cout << '\n';
        }
    }


    int numberOfRoutes(vector<string>& grid, int d) {
        R = grid.size(), C = grid[0].size();
        stayLen = d, upLen = sqrt(d*d - 1);
        store = vector(2, vector(R, vector<ll>(C, 0)));

        // r = 0, i = 0
        for (int c = 0; c < C; c++) {
            if (grid[0][c] == '#') continue;
            store[0][0][c] = 1;
        }

        // r = 0, i = 1
        vector<ll> prefix = makePrefixSum(store[0][0]);
        for (int c = 0; c < C; c++) {
            if (grid[0][c] == '#') continue; // default value already 0

            int l = max(c - d, 0), r = min(c + d, C - 1);
            store[1][0][c] = query(prefix, l, r, 0);
        }

        for (int r = 1; r < R; r++) {
            vector<ll> prefix1 = makePrefixSum(store[1][r - 1]);
            for (int c = 0; c < C; c++) {
                if (grid[r][c] == '#') continue;

                int l1 = max(c - upLen, 0), r1 = min(c + upLen, C - 1);
                store[0][r][c] = query(prefix1, l1, r1, 0);
            }

            vector<ll> prefix2 = makePrefixSum(store[0][r]);
            for (int c = 0; c < C; c++) {
                if (grid[r][c] == '#') continue;

                int l2 = max(c - d, 0), r2 = min(c + d, C - 1);
                int l1 = max(c - upLen, 0), r1 = min(c + upLen, C - 1);
                store[1][r][c] = (query(prefix2, l2, r2, store[0][r][c]) + query(prefix1, l1, r1, 0)) % MOD;
            }
        }

        //to_print();

        ll sum = 0;
        for (ll res : store[1][R - 1]) {
            sum = (sum + res) % MOD;
        }
        return (int) sum;
    }
};

int main() {
    vector<string> grid = {"..", ".."};
    int d = 1;

    Solution sol;
    cout << sol.numberOfRoutes(grid, d) << endl;

}