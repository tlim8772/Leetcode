#include <bits/stdc++.h>
using namespace std;

// use segment tree
// tree[p] for range [l, r] stores store mul([l,r]) % k 
// and also how many prefixes starting from l has multiplication x when mod k
// merging left node and right node is easy
// when updating index i, just update nodes whose [l,r] contain i


struct Store {
    // arr[i] stores how many prefix in range [l, r] has modulo of i
    // arr[5] stores modulo of [l, r]
    array<int, 6> arr = {0}; 
    
    static Store merge(int k, const Store& l, const Store& r) {
        Store res;
        res.arr[5] = (l.arr[5] * r.arr[5]) % k;

        for (int i = 0; i < k; i ++) {
            res.arr[i] += l.arr[i];
            res.arr[(i * l.arr[5]) % k] += r.arr[i];
        }

        return res;
    }

    static Store single(int k, int v) {
        Store res;
        res.arr[v % k] = 1;
        res.arr[5] = v % k;

        return res;
    }

    void print() {
        for (int i = 0; i < arr.size(); i ++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

struct SegTree {
    int len, k;
    vector<Store> tree;

    SegTree(const vector<int>& nums, int k): len(nums.size()), k(k), tree(4 * len, Store()) {
        build(0, 0, len - 1, nums);
    }

    void build(int p, int s, int e, const vector<int>& nums) {
        if (s == e) {
            tree[p] = Store::single(k, nums[s]);
            return;
        }

        int m = (s + e) >> 1;
        build((p << 1) + 1, s, m, nums);
        build((p << 1) + 2, m + 1, e, nums);
        tree[p] = Store::merge(k, tree[(p << 1) + 1], tree[(p << 1) + 2]);
    }

    void update(int p, int s, int e, int i, int v) {
        if (s == e) {
            tree[p] = Store::single(k, v);
            return;
        }

        int m = (s + e) >> 1;
        if (i <= m) {
            update((p << 1) + 1, s, m, i, v);
        } else {
            update((p << 1) + 2, m + 1, e, i, v);
        }
        tree[p] = Store::merge(k, tree[(p << 1) + 1], tree[(p << 1) + 2]);
    }

    Store query(int p, int s, int e, int l, int r) {
        if (s == e || (s == l && e == r)) {
            return tree[p];
        }

        int m = (s + e) >> 1;
        if (r <= m) {
            return query((p << 1) + 1, s, m, l, r);
        } else if (l > m) {
            return query((p << 1) + 2, m + 1, e, l, r);
        } else {
            Store lres = query((p << 1) + 1, s, m, l, m);
            Store rres = query((p << 1) + 2, m + 1, e, m + 1, r);
            return Store::merge(k, lres, rres);
        }
    }

};

class Solution {
public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        SegTree st(nums, k);
        vector<int> out;

        for (vector<int>& q : queries) {
            st.update(0, 0, st.len - 1, q[0], q[1]);
            Store res = st.query(0, 0, st.len - 1, q[2], st.len - 1);
            out.push_back(res.arr[q[3]]);
        }

        return out;
    }
};

int main() {
    vector<int> arr = {1,2,3,4,5};
    int k = 3;
    vector<vector<int>> queries = {{2,2,0,2},{3,3,3,0},{0,1,0,1}};
    Solution sol;

    vector<int> ans = sol.resultArray(arr, k, queries);
    for (int x : ans) cout << x << endl;



}