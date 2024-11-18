#include <bits/stdc++.h>
using namespace std;

// use segment to just decrement a range
// return first index such that every element is <= 0, i.e get max of [0, len(nums) - 1] make sure <= 0

class SegTree {
public:
    vector<int> tree;
    vector<int> accu;
    int sz;

    SegTree(vector<int>& nums): tree(4 * nums.size(), 0), accu(4 * nums.size(), 0), sz(nums.size()) {
        build(0, 0, sz - 1, nums);
    }

    void build(int p, int s, int e, vector<int>& nums) {
        if (s == e) {
            tree[p] = nums[s];
            return;
        }

        int m = (s + e) >> 1;
        build((p << 1) + 1, s, m, nums);
        build((p << 1) + 2, m + 1, e, nums);
        tree[p] = max(tree[(p << 1) + 1], tree[(p << 1) + 2]);
    }

    // returns the min value in [l, r]
    int addRange(int p, int s, int e, int l, int r, int acc, int val) {
        if (s == e || (s == l && e == r)) {
            int res = acc + tree[p] + val;
            tree[p] = res - acc;
            accu[p] += val;
            return res;
        }

        int m = (s + e) >> 1;
        int acc_next = acc + accu[p];
        int lres, rres;
        if (r <= m) {
            lres = addRange((p << 1) + 1, s, m, l, r, acc_next, val);
            rres = acc_next + tree[(p << 1) + 2];
        } else if (l > m) {
            lres = acc_next + tree[(p << 1) + 1];
            rres = addRange((p << 1) + 2, m + 1, e, l, r, acc_next, val);
        } else {
            lres = addRange((p << 1) + 1, s, m, l, m, acc_next, val);
            rres = addRange((p << 1) + 2, m + 1, e, m + 1, r, acc_next, val);
        }
        
        int lmin = acc_next + tree[(p << 1) + 1];
        int rmin = acc_next + tree[(p << 1) + 2];
        int ans = max(lmin, rmin);
        tree[p] = ans - acc;
        
        return max(lres, rres);
    }

    int queryMaxRange(int p, int s, int e, int l, int r, int acc) {
        if (s == e || (s == l && e == r)) {
            return acc + tree[p];
        }

        int m = (s + e) >> 1;
        if (r <= m) {
            return queryMaxRange((p << 1) + 1, s, m, l, r, acc + accu[p]);
        } else if (l > m) {
            return queryMaxRange((p << 1) + 2, m + 1, e, l, r, acc + accu[p]);
        } else {
            return max(queryMaxRange((p << 1) + 1, s, m, l, m, acc + accu[p]), queryMaxRange((p << 1) + 2, m + 1, e, m + 1, r, acc + accu[p]));
        }
    }
};

class Solution {
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        SegTree st(nums);

        if (st.queryMaxRange(0, 0, st.sz - 1, 0, st.sz - 1, 0) <= 0) return 0;
        
        for (int i = 0; i < queries.size(); i ++) {
            vector<int>& q = queries[i];
            st.addRange(0, 0, st.sz - 1, q[0], q[1], 0, -q[2]);
            
            int ans = st.queryMaxRange(0, 0, st.sz - 1, 0, st.sz - 1, 0);
            if (ans <= 0) return i + 1;
        }
        return -1;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {2,0,2};
    vector<vector<int>> queries = {{0,2,1}, {0,2,1}, {1,1,3}};
    cout << sol.minZeroArray(nums, queries);


}