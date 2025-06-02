#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int len;
    vector<int> tree;
    vector<int> accu;

    SegTree(const vector<int>& arr): len(arr.size()), tree(4 * len, 0), accu(4 * len, 0) {
        build(0, 0, len - 1, arr);
    }

    inline int LEFT(int p) { return (p << 1) + 1; }

    inline int RIGHT(int p) { return (p << 1) + 2; }
 
    void build(int p, int s, int e, const vector<int>& arr) {
        if (s == e) {
            tree[p] = arr[s];
            return;
        }

        int m = (s + e) >> 1;
        build(LEFT(p), s, m, arr);
        build(RIGHT(p), m + 1, e, arr);
        tree[p] = max(tree[LEFT(p)], tree[RIGHT(p)]);
    }

    int addRange(int p, int s, int e, int acc, int l, int r, int val) {
        if (s == e || (s == l && e == r)) {
            tree[p] += val;
            accu[p] += val;
            return acc + tree[p];
        }

        int m = (s + e) >> 1;
        int newAcc = acc + accu[p];
        int left = 0, right = 0;
        if (r <= m) {
            left = addRange(LEFT(p), s, m, newAcc, l, r, val);
            right = newAcc + tree[RIGHT(p)];
        } else if (l > m) {
            left = newAcc + tree[LEFT(p)];
            right = addRange(RIGHT(p), m + 1, e, newAcc, l, r, val);
        } else {
            left = addRange(LEFT(p), s, m, newAcc, l, m, val);
            right = addRange(RIGHT(p), m + 1, e, newAcc, m + 1, r, val);
        }
        int res = max(left, right);
        tree[p] = res - acc;
        return res;
    }

    int queryMax(int p, int s, int e, int acc, int l, int r) {
        if (s == e || (s == l && e == r)) {
            return tree[p] + acc;
        }

        int m = (s + e) >> 1;
        int newAcc = acc + accu[p];
        if (r <= m) {
            return queryMax(LEFT(p), s, m, newAcc, l, r);
        } else if (l > m) {
            return queryMax(RIGHT(p), m + 1, e, newAcc, l, r);
        } else {
            int left = queryMax(LEFT(p), s, m, newAcc, l, m);
            int right = queryMax(RIGHT(p), m + 1, e, newAcc, m + 1, r);
            return max(left, right);
        }
    }
};

int main() {
    vector<int> arr = {2,1,3,5,4,6,7};
    SegTree st(arr);

    cout << st.queryMax(0, 0, st.len - 1, 0, 1, 4) << endl;

    st.addRange(0, 0, st.len - 1, 0, 0, 2, 100);
    cout << st.queryMax(0, 0, st.len - 1, 0, 1, 4) << endl;

    st.addRange(0, 0, st.len - 1, 0, 0, st.len - 1, 100);
    cout << st.queryMax(0, 0, st.len - 1, 0, 1, 4) << endl;
    cout << st.queryMax(0, 0, st.len - 1, 0, 6, 6) << endl;
}