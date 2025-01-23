#include <bits/stdc++.h>
using namespace std;
using ll = long long;


// updateRange: make all elems in range[l, r] to be val
// queryRightMin(idx, val): gets the smallest index, index >= idx s.t arr[index] >= val and arr[index + 1] < val
// since min is decreasing, we can binary search the segment tree


struct Min {
    ll sum;
    ll m;

    Min() {}

    Min(ll sum, ll m): sum(sum), m(m) {}

    Min operator+(const Min& other) {
        return Min(sum + other.sum, min(m, other.m));
    }
};


struct MinTree {
    int INVALID = -1e7;
    int len;
    vector<int> layer;
    vector<Min> tree;

    MinTree(int len): len(len), layer(4 * len, INVALID), tree(4 * len, Min(0, 0)) {}

    MinTree(const vector<int>& arr): len(arr.size()), layer(4 * len, INVALID), tree(4 * len, Min()) {
        build(0, 0, len - 1, arr);
    }

    int updateAccu(int old, int next) {
        return (old == INVALID) ? next : old;
    }
    
    Min getMinUpdateAccu(int p, int s, int e, int accu) {
        int len = e - s + 1;
        if (accu != INVALID) {
            layer[p] = accu;
            return Min((ll) len * accu, accu);
        } else if (layer[p] != INVALID) {
            return Min((ll) len * layer[p], layer[p]);
        } else {
            return tree[p];
        }
    }

    Min getMin(int p, int s, int e, int accu) {
        int len = e - s + 1;
        if (accu != INVALID) {
            return Min((ll) len * accu, accu);
        } else if (layer[p] != INVALID) {
            return Min((ll) len * layer[p], layer[p]);
        } else {
            return tree[p];
        }
    }

    void build(int p, int s, int e, const vector<int>& arr) {
        if (s == e) {
            tree[p] = Min(arr[s], arr[s]);
            return;
        }

        int m = (s + e) >> 1;
        build((p << 1) + 1, s, m, arr);
        build((p << 1) + 2, m + 1, e, arr);
        tree[p] = tree[(p << 1) + 1] + tree[(p << 1) + 2];
    }

    Min updateRange(int p, int s, int e, int accu, int l, int r, int val) {
        if (s == e || (s == l && e == r)) {
            layer[p] = val;
            return Min((ll) (e - s + 1) * val, val);
        }

        int m = (s + e) >> 1;
        int newAccu = updateAccu(accu, layer[p]);
        Min left, right;
        
        if (r <= m) {
            left = updateRange((p << 1) + 1, s, m, newAccu, l, r, val);
            right = getMinUpdateAccu((p << 1) + 2, m + 1, e, newAccu);
        } else if (l > m) {
            left = getMinUpdateAccu((p << 1) + 1, s, m, newAccu);
            right = updateRange((p << 1) + 2, m + 1, e, newAccu, l, r, val);
        } else {
            left = updateRange((p << 1) + 1, s, m, newAccu, l, m, val);
            right = updateRange((p << 1) + 2, m + 1, e, newAccu, m + 1, r, val);
        }

        layer[p] = INVALID;
        tree[p] = left + right;
        return tree[p];
    }

    // gets the index >= idx s.t index is the smallest index s.t arr[index] < val
    // if there is not any such element, i.e all elems in [idx, len - 1] are >= val, return -1
    int query1stLess(int p, int s, int e, int accu, int idx, int val) {
        if (s == e) {
            return (getMin(p, s, e, accu).m < val) ? s : -1;
        }

        int m = (s + e) >> 1;
        int newAccu = updateAccu(accu, layer[p]);
        
        if (idx <= s) {
            Min left = getMin((p << 1) + 1, s, m, newAccu);
            Min right = getMin((p << 1) + 2, m + 1, e, newAccu);
            Min total = getMin(p, s, e, accu);
            
            if (total.m >= val) {
                return -1;
            } else if (left.m < val) {
                return query1stLess((p << 1) + 1, s, m, newAccu, idx, val);
            } else {
                return query1stLess((p << 1) + 2, m + 1, e, newAccu, idx, val);
            }
        } else if (idx > m) {
            return query1stLess((p << 1) + 2, m + 1, e, newAccu, idx, val);
        } else {
            int leftRes = query1stLess((p << 1) + 1, s, m, newAccu, idx, val);
            return (leftRes != -1) ? leftRes : query1stLess((p << 1) + 2, m + 1, e, newAccu, idx, val);
        }
        
    }

    ll querySum(int p, int s, int e, int accu, int l, int r) {
        if (s == e || (s == l && e == r)) {
            return getMin(p, s, e, accu).sum;
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
    MinTree mt(10);

    mt.updateRange(0, 0, mt.len - 1, mt.INVALID, 0, 9, 1);
    mt.updateRange(0, 0, mt.len - 1, mt.INVALID, 5, 9, 2);
    assert(mt.querySum(0, 0, mt.len - 1, mt.INVALID, 0, 9) == 15);
     
}

void test2() {
    MinTree mt(100);
    mt.updateRange(0, 0, mt.len - 1, mt.INVALID, 40, 80, 1);
    mt.updateRange(0, 0, mt.len - 1, mt.INVALID, 50, 70, 2);
    assert(mt.querySum(0, 0, mt.len - 1, mt.INVALID, 40, 80) == 62);
}

void test3() {
    MinTree mt(100);
    mt.updateRange(0, 0, mt.len - 1, mt.INVALID, 0, 20, 10);
    mt.updateRange(0, 0, mt.len - 1, mt.INVALID, 21, 40, 8);
    assert(mt.query1stLess(0, 0, mt.len - 1, mt.INVALID, 10, 9) == 21);
}

void test4() {
    MinTree mt(100000);
    for (int i = 0; i < 80000; i ++) {
        mt.updateRange(0, 0, mt.len - 1, mt.INVALID, i, i + 10, 1);
    }
    assert(mt.querySum(0, 0, mt.len - 1, mt.INVALID, 100, 200) == 101);
}

void test5() {
    MinTree mt({20,18,15,11,9,5,2,0});
    assert(mt.query1stLess(0, 0, mt.len - 1, mt.INVALID, 0, 10) == 4);
    
    mt.updateRange(0, 0, mt.len - 1, mt.INVALID, 4, 7, 10);
    assert(mt.query1stLess(0, 0, mt.len - 1, mt.INVALID, 0, 9) == -1);

    mt.updateRange(0, 0, mt.len - 1, mt.INVALID, 0, 5, 12);
    assert(mt.query1stLess(0, 0, mt.len - 1, mt.INVALID, 2, 13) == 2);
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();

   
}