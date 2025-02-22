#include <bits/stdc++.h>
using namespace std;
using ll = long long;


// we have to support 2 updates. 
// update idx to be a val
// update(l, r, val): for all idx i, l <= i <= r value of idx i is val - arr[i]
// 1 query(l, r): sum of all idxs in [l, r]
// invariant: tree[p] contains sum of results from [s,e] if there is no layer at that node or above
// layer[p]: means we layer layer[p] over all idxs in [s,e]. Clearly, only the highest node layer matter
// i.e layer[p] = 5 and left child layer[(p << 1) + 1] is 10, the left child layer does not matter

struct SpecialSegTree {
    int n;
    vector<ll> sumtree;
    vector<ll> tree;
    vector<ll> layer; // layer[p] == -1 if the range [s,e] is not layered 

    SpecialSegTree(vector<int>& arr): n(arr.size()), sumtree(4 * n, 0), tree(4 * n, 0), layer(4 * n, -1) {
        build(0, 0, n - 1, arr);
    }
    

    void build(int p, int s, int e, vector<int>& arr) {
        if (s == e) {
            sumtree[p] = arr[s];
            return;
        }

        int m = (s + e) >> 1;
        build((p << 1) + 1, s, m, arr);
        build((p << 1) + 2, m + 1, e, arr);
        sumtree[p] = sumtree[(p << 1) + 1] + sumtree[(p << 1) + 2];
    }

    // gets the sum and also update layer[p] with the correct value if necessary
    ll getSumAndUpdate(int p, int s, int e, int accu) {
        if (accu != -1) {
            layer[p] = accu;
            return accu * (e - s + 1) - sumtree[p];
        } else if (layer[p] != -1) {
            return layer[p] * (e - s + 1) - sumtree[p];
        } else {
            return tree[p];
        }
    }

    ll getSum(int p, int s, int e, int accu) {
        if (accu != -1) {
            return accu * (e - s + 1) - sumtree[p];
        } else if (layer[p] != -1) {
            return layer[p] * (e - s + 1) - sumtree[p];
        } else {
            return tree[p];
        }
    }

    ll updateAccu(int oldAccu, int newAccu) {
        return (oldAccu == -1) ? newAccu : oldAccu;
    }

    // returns the sum of [s, e] after updating
    // all ranges that do not strictly contain the range updated, and nothing else, has their layer invalidated
    // accu is the layer val of the top most ancestor (if any), not including the curr node
    ll updatePoint(int p, int s, int e, int accu, int idx, int val) {
        if (s == e) {
            tree[p] = val;
            layer[p] = -1;
            return val;
        }
        int m = (s + e) >> 1;
        ll lsum, rsum;
        if (idx <= m) {
            lsum = updatePoint((p << 1) + 1, s, m, updateAccu(accu, layer[p]), idx, val);
            rsum = getSumAndUpdate((p << 1) + 2, m + 1, e, updateAccu(accu, layer[p]));
        } else if (idx > m) {
            lsum = getSumAndUpdate((p << 1) + 1, s, m, updateAccu(accu, layer[p]));
            rsum  = updatePoint((p << 1) + 2, m + 1, e, updateAccu(accu, layer[p]), idx, val);
        }
        layer[p] = -1;
        tree[p] = lsum + rsum;
        return tree[p];
    }


    // all ranges that do not strictly contain the range updated, and nothing else, has their layer invalidated
    ll updateRange(int p, int s, int e, int accu, int l, int r, int val) {
        if (s == e || (s == l && e == r)) {
            layer[p] = val;
            return val * (e - s + 1) - sumtree[p];
        }
        int m = (s + e) >> 1;
        ll lsum, rsum;
        if (r <= m) {
            lsum = updateRange((p << 1) + 1, s, m, updateAccu(accu, layer[p]), l, r, val);
            rsum = getSumAndUpdate((p << 1) + 2, m + 1, e, accu);
        } else if (l > m) {
            lsum = getSumAndUpdate((p << 1) + 1, s, m, updateAccu(accu, layer[p]));
            rsum = updateRange((p << 1) + 2, m + 1, e, updateAccu(accu, layer[p]), l, r, val);
        } else {
            lsum = updateRange((p << 1) + 1, s, m, updateAccu(accu, layer[p]), l, m, val);
            rsum = updateRange((p << 1) + 2, m + 1, e, updateAccu(accu, layer[p]), m + 1, r, val);
        }
        layer[p] = -1;
        tree[p] = lsum + rsum;
        return tree[p];

    }


    // fo this we know that s <= l <= r <= e
    // if layer exists, we can and must return the sum value immediately, to ensure the topmost layer val
    // is used
    ll query(int p, int s, int e, int accu, int l, int r) {
        if (s == e || (s == l && e == r)) {
            return getSum(p, s, e, accu);
        }

        int m = (s + e) >> 1;
        if (r <= m) {
            return query((p << 1) + 1, s, m, updateAccu(accu, layer[p]), l, r);
        } else if (l > m) {
            return query((p << 1) + 2, m + 1, e, updateAccu(accu, layer[p]), l, r);
        } else {
            return query((p << 1) + 1, s, m, updateAccu(accu, layer[p]), l, m) + 
                query((p << 1) + 2, m + 1, e, updateAccu(accu, layer[p]), m + 1, r);
        }
    }
};

void test1() {
    vector<int> arr  = {0,0,0,0,0};
    SpecialSegTree st(arr);
    st.updateRange(0, 0, st.n - 1, -1, 0, 4, 10);
    st.updateRange(0, 0, st.n - 1, -1, 3, 4, 5);
    assert(st.query(0, 0, st.n - 1, -1, 0, 3) == 35);

}

void test2() {
    vector<int> arr = {0,0,0,0,0};
    SpecialSegTree st(arr);
    st.updateRange(0, 0, st.n - 1, -1, 0, 3, 10);
    st.updatePoint(0, 0, st.n - 1, -1, 1, 100);
    assert(st.query(0, 0, st.n - 1, -1, 0, 3) == 130);
}

void test3() {
    vector<int> arr = vector(1e5, 0);
    SpecialSegTree st(arr);
    for (int i = 0; i < 1e5; i ++) {
        st.updateRange(0, 0, st.n - 1, -1, i, i + 1e5 - 1, 10);
    }
    assert(st.query(0, 0, st.n - 1, -1, 0, 10) == 110);
}



int main() {
    test1();
    test2();
    test3();
    
}