#include <bits/stdc++.h>
using namespace std;

// use sieve to compute once, all primes in [0, 500000].
// just sum the primes from 2, 3, 5 ... until we exceed n.

vector<bool> sieve(int n) {
    vector<bool> out(n + 1, true);
    for (int i = 2; i * i <= n; i++) {
        if (!out[i]) continue;
        for (int j = i * i; j <= n; j += i) {
            out[j] = false;
        }
    }
    return out;
}

vector<bool> is_prime = sieve(500000);

class Solution {
public:
    int largestPrime(int n) {
        if (n < 2) return 0;
        int sum = 2, best = 2;
        for (int i = 3; i <= n; i++) {
            if (!is_prime[i]) continue;
            if (sum + i > n) break;
            sum += i;
            if (is_prime[sum]) best = sum;
        }
        return best;
    }
};



int main() {
    Solution sol;
    cout << sol.largestPrime(15) << endl;
}