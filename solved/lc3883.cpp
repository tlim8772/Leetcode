#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1e9 + 7;

// simple dp.
// let dp(i, prev_num) be # of ways to build an array starting from index i onwards with prev_num at 
// index i - 1.
// so at index i, ans is (1 or 0 if digit_sum(prev_num) is valid) + dp(i, prev_num + 1)

int d_sum(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

class Solution {
public:
    int LEN;
    vector<ll> store;

    int coor(int i, int prev_num) {
        return i * 5001 + prev_num;
    }

    ll dp(int i, int prev_num, const vector<int>& digitSum) {
        if (i == digitSum.size()) return 1;
        if (prev_num >= 5001) return 0;
        
        ll &ans = store[coor(i, prev_num)];
        if (ans != -1) return ans;

        int dsum = d_sum(prev_num);
        ll take = 0, notake = 0;

        if (d_sum(prev_num) == digitSum[i]) {
            take = dp(i + 1, prev_num, digitSum);
        }

        notake = dp(i, prev_num + 1, digitSum);

        return ans = (take + notake) % MOD;
    }


    int countArrays(vector<int>& digitSum) {
        LEN = digitSum.size();
        store = vector<ll>(LEN * 5001, -1);
        ll ans = dp(0, 0, digitSum);
        return (int) ans;
    }
};

int main() {
    Solution sol;
    vector<int> digitSum = {1, 49, 30};
    int ans = sol.countArrays(digitSum);
    println("{}", ans);
}