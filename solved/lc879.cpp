#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// simple take notake dp.

class Solution {
public:
    ll MOD = 1e9 + 7;

    int N, P, I;
    vector<int> group, profit;
    
    vector<ll> store;
    

    int to_pos(int n, int p, int i) {
        return n * P * I + p * I + i;
    }

    // p >= 0
    ll dp(int n, int p, int i) {
        if (i == group.size()) return (p == 0) ? 1 : 0;

        int pos = to_pos(n, p, i);
        if (store[pos] != -1) return store[pos];

        ll notake = dp(n, p, i + 1);
        ll take = 0;
        if (n >= group[i]) {
            take = dp(n - group[i], max(p - profit[i], 0), i + 1);
        }

        return store[pos] = (notake + take) % MOD;
    }

    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        N = n + 1;
        P = minProfit + 1;
        I = group.size();
        this->group = group;
        this->profit = profit;

        store = vector<ll>(N * P * I, -1);

        return dp(n, minProfit, 0);
    }
};

int main() {
    Solution sol;
    int n = 10, minProfit = 5;
    vector<int> group = {2,3,5}, profit = {6,7,8};
    cout << sol.profitableSchemes(n, minProfit, group, profit) << endl;
}