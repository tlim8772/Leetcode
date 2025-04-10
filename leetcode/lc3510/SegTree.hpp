#include <bits/stdc++.h>
using ll = long long;
using namespace std;

// if i == -1, means it is invalid, i.e index is removed
// an invalid Pair is always {-1, any value}
struct Pair {
    static const ll MAX = 1e14 + 1;
    int i = -1;
    ll v = MAX; // 
 
    static Pair mergeAdj(const Pair& pl, const Pair& pr) {
        if (pl.i == -1 || pr.i == -1) {
            return Pair{-1, MAX};
        } else {
            ll res = pl.v + pr.v;
            //cout << pl.i << " " << pl.v << " " << pr.i << " " << pr.v << " " << res << endl;
            return Pair{pl.i, res};
        }
    }

    static Pair getBest(const array<Pair, 3>& lst) {
        int i = -1;
        ll v = MAX;
        for (const Pair& p : lst) {
            if (p.i == -1) continue;
            if (p.v < v) {
                i = p.i;
                v = p.v;
            } else if (p.v == v && p.i < i) {
                i = p.i;
            }
        }
        return Pair{i, v};
    }

    void setVal(int i, ll v) {
        this->i = i;
        this->v = v;
    }

    void del() {
        i = -1;
        v = MAX;
    }
};

struct Store {
    Pair left, right, best;
    int wrongOrderCnt = 0;

    static void merge(Store& myStore, const Store& sl, const Store& sr) {
        myStore.left = (sl.left.i == -1) ? sr.left : sl.left;
        myStore.right = (sr.right.i == -1) ? sl.right : sr.right;

        Pair mid = Pair::mergeAdj(sl.right, sr.left);
        myStore.best = Pair::getBest(array<Pair, 3>{sl.best, mid, sr.best});

        int addWrongCnt = (sl.right.i == -1 || sr.left.i == -1) ? 0 : sl.right.v > sr.left.v;
        myStore.wrongOrderCnt = sl.wrongOrderCnt + sr.wrongOrderCnt + addWrongCnt;
    }

    void setVal(int i, ll v) {
        left.setVal(i, v);
        right.setVal(i, v);
    }

    void del() {
        left.del();
        right.del();
    }
};



struct SegTree {
    int len;
    vector<Store> tree;

    SegTree() {}

    SegTree(int len): len(len), tree(4 * len, Store()) {}

    SegTree(const vector<int>& arr): len(arr.size()), tree(4 * len, Store()) {
        build(0, 0, len - 1, arr);
    }

    void build(int p, int s, int e, const vector<int>& arr) {
        if (s == e) {
            tree[p].setVal(s, arr[s]);
            return;
        }

        int m = (s + e) >> 1;
        build((p << 1) + 1, s, m, arr);
        build((p << 1) + 2, m + 1, e, arr);
        Store::merge(tree[p], tree[(p << 1) + 1], tree[(p << 1) + 2]);
    }

    void insert(int p, int s, int e, int i, ll v) {
        if (s == e) {
            tree[p].setVal(i, v);
            return;
        }

        int m = (s + e) >> 1;
        if (i <= m) {
            insert((p << 1) + 1, s, m, i, v);
        } else {
            insert((p << 1) + 2, m + 1, e, i, v);
        }
        Store::merge(tree[p], tree[(p << 1) + 1], tree[(p << 1) + 2]);
    }

    void del(int p, int s, int e, int i) {
        if (s == e) {
            tree[p].del();
            return;
        }

        int m = (s + e) >> 1;
        if (i <= m) {
            del((p << 1) + 1, s, m, i);
        } else {
            del((p << 1) + 2, m + 1, e, i);
        }
        Store::merge(tree[p], tree[(p << 1) + 1], tree[(p << 1) + 2]);
    }

    // find the next index after i. May not be i + 1, as that index may be deleted
    // return -1 if dont have
    // means we are searching from i + 1 onwards
    int findNext(int p, int s, int e, int i) {
        if (i < s) {
            return tree[p].left.i;
        } else if (s == e) {
            return -1;
        }

        int m = (s + e) >> 1;
        if (i >= m) {
            return findNext((p << 1) + 2, m + 1, e, i);
        } else {
            int lres = findNext((p << 1) + 1, s, m, i);
            return (lres != -1) ? lres : tree[(p << 1) + 2].left.i;
        }
    }
};


