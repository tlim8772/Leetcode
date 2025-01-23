#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Max {
    ll sum;
    ll m;

    Max() {}

    Max(ll sum, ll m): sum(sum), m(m) {}

    Max operator+(const Max& other) {
        return Max(sum + other.sum, max(m, other.m));
    }
};

struct MaxTree {
    int INVALID = -1e7;
    int len;
    vector<int> layer;
    vector<Max> tree;

    MaxTree(int len): len(len), layer(4 * len, INVALID), tree(4 * len, Max(0, 0)) {}

    MaxTree(const vector<int>& arr): len(arr.size()), layer(4 * len, INVALID), tree(4 * len, Max()) {
        build(0, 0, len - 1, arr);
    }

    int updateAccu(int old, int next) {
        return (old == INVALID) ? next : old;
    }
    
    Max getMaxUpdateAccu(int p, int s, int e, int accu) {
        int len = e - s + 1;
        if (accu != INVALID) {
            layer[p] = accu;
            return Max((ll) len * accu, accu);
        } else if (layer[p] != INVALID) {
            return Max((ll) len * layer[p], layer[p]);
        } else {
            return tree[p];
        }
    }

    Max getMax(int p, int s, int e, int accu) {
        int len = e - s + 1;
        if (accu != INVALID) {
            return Max((ll) len * accu, accu);
        } else if (layer[p] != INVALID) {
            return Max((ll) len * layer[p], layer[p]);
        } else {
            return tree[p];
        }
    }

    void build(int p, int s, int e, const vector<int>& arr) {
        if (s == e) {
            tree[p] = Max(arr[s], arr[s]);
            return;
        }

        int m = (s + e) >> 1;
        build((p << 1) + 1, s, m, arr);
        build((p << 1) + 2, m + 1, e, arr);
        tree[p] = tree[(p << 1) + 1] + tree[(p << 1) + 2];
    }

    Max updateRange(int p, int s, int e, int accu, int l, int r, int val) {
        if (s == e || (s == l && e == r)) {
            layer[p] = val;
            return Max((ll) (e - s + 1) * val, val);
        }

        int m = (s + e) >> 1;
        int newAccu = updateAccu(accu, layer[p]);
        Max left, right;
        
        if (r <= m) {
            left = updateRange((p << 1) + 1, s, m, newAccu, l, r, val);
            right = getMaxUpdateAccu((p << 1) + 2, m + 1, e, newAccu);
        } else if (l > m) {
            left = getMaxUpdateAccu((p << 1) + 1, s, m, newAccu);
            right = updateRange((p << 1) + 2, m + 1, e, newAccu, l, r, val);
        } else {
            left = updateRange((p << 1) + 1, s, m, newAccu, l, m, val);
            right = updateRange((p << 1) + 2, m + 1, e, newAccu, m + 1, r, val);
        }

        layer[p] = INVALID;
        tree[p] = left + right;
        return tree[p];
    }

    // gets the index >= idx s.t index is the smallest index s.t arr[index] > val
    int query1stMore(int p, int s, int e, int accu, int idx, int val) {
        if (s == e) {
            return (getMax(p, s, e, accu).m > val) ? s : -1;
        }

        int m = (s + e) >> 1;
        int newAccu = updateAccu(accu, layer[p]);
        
        if (idx <= s) {
            Max left = getMax((p << 1) + 1, s, m, newAccu);
            Max right = getMax((p << 1) + 2, m + 1, e, newAccu);
            Max total = getMax(p, s, e, accu);
            
            if (total.m < val) {
                return -1;
            } else if (left.m > val) {
                return query1stMore((p << 1) + 1, s, m, newAccu, idx, val);
            } else {
                return query1stMore((p << 1) + 2, m + 1, e, newAccu, idx, val);
            }
        } else if (idx > m) {
            return query1stMore((p << 1) + 2, m + 1, e, newAccu, idx, val);
        } else {
            int leftRes = query1stMore((p << 1) + 1, s, m, newAccu, idx, val);
            return (leftRes != -1) ? leftRes : query1stMore((p << 1) + 2, m + 1, e, newAccu, idx, val);
        }
        
    }

    ll querySum(int p, int s, int e, int accu, int l, int r) {
        if (s == e || (s == l && e == r)) {
            return getMax(p, s, e, accu).sum;
        }

        int m = (s + e) >> 1;
        int newAccu = updateAccu(accu, layer[p]);
        if (r <= m) {
            return querySum((p << 1) + 1, s, m, newAccu, l, r);
        } else if (l > m) {
            return querySum((p << 1) + 2, m + 1, e, newAccu, l, r);
        } else {
            return querySum((p << 1) + 1, s, m, newAccu, l, m) + querySum((p << 1) + 2, m + 1, e, newAccu, m + 1, r);
        }
    }
};

void test1() {
    MaxTree mt(10);
    mt.updateRange(0, 0, mt.len - 1, mt.INVALID, 0, 9, 1);
    mt.updateRange(0, 0, mt.len - 1, mt.INVALID, 5, 9, 2);
    assert(mt.querySum(0, 0, mt.len - 1, mt.INVALID, 0, 9) == 15);

    mt.updateRange(0, 0, mt.len - 1, mt.INVALID, 5, 5, 100);
    assert(mt.querySum(0, 0, mt.len - 1, mt.INVALID, 0, 9) == 113);
}

void test2() {
    MaxTree mt({0,2,3,5,7,13,15,19,25});
    assert(mt.query1stMore(0, 0, mt.len - 1, mt.INVALID, 3, 14) == 6);

    mt.updateRange(0, 0, mt.len - 1, mt.INVALID, 4, 8, 15);
    assert(mt.query1stMore(0, 0, mt.len - 1, mt.INVALID, 3, 14) == 4);

    mt.updateRange(0, 0, mt.len - 1, mt.INVALID, 2, 8, 16);
    assert(mt.query1stMore(0, 0, mt.len - 1, mt.INVALID, 1, 17) == -1);
}

void test3() {
    MaxTree mt(100000);
    for (int i = 0; i < 80000; i ++) {
        mt.updateRange(0, 0, mt.len - 1, mt.INVALID, i, i + 10, 2);
    }
    assert(mt.querySum(0, 0, mt.len - 1, mt.INVALID, 100, 200) == 202);

    for (int i = 0; i < 80000; i ++) {
        assert(mt.query1stMore(0, 0, mt.len - 1, mt.INVALID, i, 1) == i);
    }

}

int main() {
    test1();
    test2();
    test3();
}