#include <bits/stdc++.h>
using namespace std;

// split elems into odd or even groups.
// if want nums2 to be odd, each even element must have an odd elem that is lesser than it.
// if want nums2 to be even, each odd element must have an odd elem that is lesser than it.

class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        set<int> odd, even;
        for (int x : nums1) {
            (x % 2 == 1) ? odd.insert(x) : even.insert(x);
        }

        // nums2 to be odd
        bool res1 = true;
        for (int x : even) {
            auto it = odd.lower_bound(x);
            if (it == odd.begin()) {
                res1 = false;
                break;
            }
        }

        if (res1) return true;

        bool res2 = true;
        for (int x : odd) {
            auto it = odd.lower_bound(x);
            if (it == odd.begin()) {
                res2 = false;
                break;
            }
        }

        return res2;
    }
};