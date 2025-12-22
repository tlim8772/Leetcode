#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// actually quite simple.
// maintain the start value, end value and the gap.
// depending on which side we are starting from, update start, end, gap, side accordingly.
// gap is always * 2, so time complexity is O(logn).

class Solution {
public:

    ll helper(ll s, ll e, ll gap, bool side) {
        if (s == e) return s;
        
        ll x = (e - s) / gap;
        if (side) {
            ll new_e = (x % 2 == 0) ? e : e - gap;
            return helper(s, new_e, gap * 2, !side);
        } else {
            ll new_s = (x % 2 == 0) ? s : s + gap;
            return helper(new_s, e, gap * 2, !side);
        }
    }
    
    long long lastInteger(long long n) {
        return helper(1, n, 1, 1);
    }
};