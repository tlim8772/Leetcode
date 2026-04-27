#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// segtree dp, similar to segtree solution for longest increasing subsequence.
// at index i, use segtree to query the best result from arr[i + k:].
// check both cases i.e go up first or go down first.
// we go from left to right.

template <typename T, typename Reducer>
struct SegTree {
    int len;
    vector<T> tree;
    Reducer red;

    SegTree() {}

    SegTree(int len): len(len), tree(4 * len, T()) {}

    inline int left(int p) { return (p << 1) + 1; }

    inline int right(int p) { return (p << 1) + 2; }

    inline int mid(int s, int e) { return (s + e) >> 1; }

    void clear() { fill(tree.begin(), tree.end(), T()); }

    void update(int i, T val, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;
        
        if (s == e) {
            tree[p] = red(tree[p], val);
            return;
        }
        
        int m = mid(s, e);
        (i <= m) ? update(i, val, left(p), s, m) : update(i, val, right(p), m + 1, e);
        tree[p] = red(tree[left(p)], tree[right(p)]);
    }

    T query(int l, int r, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;

        if (s == l && e == r) return tree[p];

        int m = mid(s, e);
        if (r <= m) {
            return query(l, r, left(p), s, m);
        } else if (l > m) {
            return query(l, r, right(p), m + 1, e);
        } else {
            T lres = query(l, m, left(p), s, m), rres = query(m + 1, r, right(p), m + 1, e);
            return red(lres, rres);
        }
    }
};

void test_seg_tree() {
    struct SumReducer {
        int operator()(int a, int b) const {
            return a + b;
        }
    };

    int n = 5;
    SegTree<int, SumReducer> st;
    st.len = n;
    st.tree.assign(4 * n, 0); // Important: Initialize tree size

    // Update indices: [0, 1, 2, 3, 4] with values [1, 2, 3, 4, 5]
    for(int i = 0; i < n; ++i) st.update(i, i + 1);

    // Query sum of [0, 2] -> 1 + 2 + 3 = 6
    assert(st.query(0, 2) == 6);
    // Query sum of [0, 4] -> 15
    assert(st.query(0, 4) == 15);
}

class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums, int k) {
        struct Max {
            ll operator()(ll a, ll b) { return max(a, b); }
        };
        using ST = SegTree<ll,Max>;
        
        static const int START = 1, LEN = 1e5;
        static ST st_up(LEN + 1), st_down(LEN + 1); 
        st_up.clear(); st_down.clear();

        vector<ll> res_up(nums.size(), 0), res_down(nums.size(), 0);

        for (int i = 0; i < nums.size(); i++) {
            if (i - k < 0) {
                res_up[i] = res_down[i] = nums[i];
                continue;
            }

            st_up.update(nums[i - k], res_up[i - k]);
            st_down.update(nums[i - k], res_down[i - k]);

            ll best_up = (nums[i] - 1 < START) ? 0 : st_up.query(START, nums[i] - 1);
            ll best_down = (nums[i] + 1 > LEN) ? 0 : st_down.query(nums[i] + 1, LEN);

            res_down[i] = nums[i] + best_up;
            res_up[i] = nums[i] + best_down;
        }

        ll best = 0;
        for (int i = 0; i < nums.size(); i++) {
            best = max({best, res_up[i], res_down[i]});
        }
        return best;


    }
};

int main() {
    //test_seg_tree();
    //cout << ll() << endl;

    Solution sol;

    vector<int> nums = {5, 1};
    int k = 1;

    ll ans = sol.maxAlternatingSum(nums, k);
    cout << ans << endl;
}