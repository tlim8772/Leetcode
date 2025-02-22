#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int MOD = 1e9 + 7;

// PnC question.
// we need to find all permuations of length n, consisting of elems in [1...m], and with exactly k indices
// s.t arr[i] == arr[i + 1]
// e.g n = 5, k = 2
// if the indices are 0 1, we have [0,1,2],3,4 [i...j]  means that for all indices in this range, they have the same elem
// so it becomes length 3 arr, and no adjacent elems are the same. Ans is m * (m - 1) * (m - 1)
// lets say now the k indices are [0,1], 2, [3,4], still the same, length 3 arr with no adjacent equal elems

// so for n, m, k ans is (n - 1)Ck * #ways of length (n - k) array with no 2 adjacent equal elems


ll fact(int n, int MOD) {
    ll res = 1;
    while (n > 0) {
        res *= n;
        res %= MOD;
        n --;
    }
    return res;
}

ll gcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

ll modInverse(ll a, ll m) {
    ll x, y;
    ll g = gcd(a, m, x, y);
    return (x < 0) ? (x % m) + m : x % m;
}


ll combi(int n, int k) {
    ll resN = fact(n, MOD);
    ll resK = modInverse(fact(k, MOD), MOD);
    ll resNK = modInverse(fact(n - k, MOD), MOD);

    ll res = (resN * resK) % MOD;
    res = (res * resNK) % MOD;
    
    return res;
}

class Solution {
public:
    int countGoodArrays(int n, int m, int k) {
        ll temp = m;
        for (int i = 0; i < n - k - 1; i ++) {
            temp *= (m - 1);
            temp %= MOD;
        }

        ll ans = (combi(n - 1, k) * temp) % MOD;

        return ans;
    }
};



int main() {
    cout << Solution().countGoodArrays(5, 2, 0) << endl;
}