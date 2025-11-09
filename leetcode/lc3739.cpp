#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
use segment tree + a clever trick.
for nums, if nums[i] == target, make it 1, else make it -1.
problem is now find # of subarrays whose sum is > 0.

we use a segment tree, on arr, where arr[i] = #num of subarrays whose sum is i (here i can be neg).
the segtree stores the zero index, s.t arr[zero_idx] = #num of subarrays whose sum is 0.
the zero index can be shifted left or right.

starting from right to left, 
if nums[i] = 1, we 'shift' the sum to the left, i.e -1->0, 0->1, 1->2.
then arr[1]++, then find # of subarrays whose sum is > 0.

example nums = [-1,1,1]
top is arr, bottom is the identifier array, i.e if arr[i] = x, and identifier[i] = y, # of subarrays whose 
sum is y is x.

 0  0 0 0 0 
-2 -1 0 1 2

idx = 2
 0  0 1 0 0
-1  0 1 2 3

idx = 1
 0  1 1 0 0
 0  1 2 3 4

idx = 0

  1 1 1 1 1
 -1 0 1 2 3
*/
struct SegTree {
    int zero_idx = -1, len = -1;
    vector<ll> tree;

    SegTree(int n): zero_idx(n), len(2 * n + 1), tree(8 * n + 4, 0) {}

    ll find_greater_than_zero() {
        return query(zero_idx + 1, len - 1);
    }
 
    ll query(int l, int r, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;
        
        if (s == e || s == l && e == r) {
            return tree[p];
        }

        int m = (s + e) >> 1;
        if (r <= m) {
            return query(l, r, (p << 1) + 1, s, m);
        } else if (l > m) {
            return query(l, r, (p << 1) + 2, m + 1, e);
        } else {
            return query(l, m, (p << 1) + 1, s, m) + query(m + 1, r, (p << 1) + 2, m + 1, e);
        }
    }

    void update_point(int i, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;
        
        if (s == e) {
            tree[p] += 1;
            return;
        }

        int m = (s + e) >> 1;
        if (i <= m) {
            update_point(i, (p << 1) + 1, s, m);
        } else if (i > m) {
            update_point(i, (p << 1) + 2, m + 1, e);
        }
        tree[p] = tree[(p << 1) + 1] + tree[(p << 1) + 2];
    }
};

class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        for (int& x : nums) {
            if (x == target) x = 1;
            else x = -1;
        }

        SegTree st(nums.size());
        ll sum = 0;

        for (int i = nums.size() - 1; i > -1; i--) {
            if (nums[i] == 1) {
                st.zero_idx--;
                st.update_point(st.zero_idx + 1);
                int res = st.find_greater_than_zero();
                sum += res;
            } else {
                st.zero_idx++;
                st.update_point(st.zero_idx - 1);
                int res = st.find_greater_than_zero();
                sum += res;
            }
        }

        return sum;
    }
};

int main() {
    /*SegTree st(2);

    st.zero_idx--;
    st.update_point(st.zero_idx + 1);
    cout << st.find_greater_than_zero() << endl;

    st.zero_idx--;
    st.update_point(st.zero_idx + 1);
    cout << st.find_greater_than_zero() << endl;

    st.zero_idx++;
    st.update_point(st.zero_idx - 1);
    cout << st.find_greater_than_zero() << endl;*/

    Solution sol;

    vector<int> nums = {1,1,1,1};
    int target = 1;

    cout << sol.countMajoritySubarrays(nums, target) << endl;


}