#include <bits/stdc++.h>
using namespace std;

// no matter how we split, the total cost is the same.
// for n, cost is n(n - 1) / 2.
// use induction to prove.
// proof.
// a + b = c, cost for c is a(a - 1) / 2 + b(b - 1) / 2 + ab
// continue yourself.

class Solution {
public:
    int minCost(int n) {
        return n * (n - 1) / 2;
    }
};
