#include <bits/stdc++.h>
using namespace std;


struct MaxSegTree {
    int n;
    vector<int> tree;

    MaxSegTree() {}
    
    MaxSegTree(vector<int>& arr): n(arr.size()), tree(4 * n, 0) {
        build(0, 0, n - 1, arr);
    }

    void build(int p, int s, int e, vector<int>& arr) {
        if (s == e) {
            tree[p] = arr[s];
            return;
        }

        int m = (s + e) >> 1;
        build((p << 1) + 1, s, m, arr);
        build((p << 1) + 2, m + 1, e, arr);
        tree[p] = max(tree[(p << 1) + 1], tree[(p << 1) + 2]);
    }

    int query(int p, int s, int e, int l, int r) {
        if (s == e || (s == l && e == r)) return tree[p];

        int m = (s + e) >> 1;
        if (r <= m) return query((p << 1) + 1, s, m, l, r);
        else if (l > m) return query((p << 1) + 2, m + 1, e, l, r);
        else return max(query((p << 1) + 1, s, m, l, m), query((p << 1) + 2, m + 1, e, m + 1, r));
    }
};

int main() {
    vector<int> arr = {3,1,2,5,2,8,4,2};
    MaxSegTree st(arr);
    cout << st.query(0, 0, st.n - 1, 0,4) << endl;
}