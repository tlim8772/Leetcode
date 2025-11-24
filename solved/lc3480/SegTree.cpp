#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
public:
    map<int, int> rs;

    inline void removeVal(int v) {
        rs[v] --;
        if (rs[v] == 0) rs.erase(v);
    }

    inline void addVal(int val) {
        rs[val] ++;
    }

    int getMin(int dval) {
        return (rs.empty()) ? dval : rs.begin()->first;
    }
};

struct SegTree {
    int len;
    int dval;
    vector<Node> tree;

    // defaultVal: the MAXIMUM limit
    SegTree(int n, int defaultVal): len(n), dval(defaultVal), tree(4 * n, Node()) {
        insertRange(0, 0, n - 1, 0, n - 1, defaultVal);
    }


    void insertRange(int p, int s, int e, int l, int r, int val) {
        if (s == e || (s == l && e == r)) {
            tree[p].addVal(val);
            return;
        }

        int m = (s + e) >> 1;
        if (r <= m) {
            insertRange((p << 1) + 1, s, m, l, r, val);
        } else if (l > m) {
            insertRange((p << 1) + 2, m + 1, e, l, r, val);
        } else {
            insertRange((p << 1) + 1, s, m, l, m, val);
            insertRange((p << 1) + 2, m + 1, e, m + 1, r, val);
        }
    }

    // can only remove a range you previously added before, up to user to maintain this invariant
    void removeRange(int p, int s, int e, int l, int r, int val) {
        if (s == e || (s == l && e == r)) {
            tree[p].removeVal(val);
            return;
        }

        int m = (s + e) >> 1;
        if (r <= m) {
            removeRange((p << 1) + 1, s, m, l, r, val);
        } else if (l > m) {
            removeRange((p << 1) + 2, m + 1, e, l, r, val);
        } else {
            removeRange((p << 1) + 1, s, m, l, m, val);
            removeRange((p << 1) + 2, m + 1, e, m + 1, r, val);
        }
    }

    int getMin(int p, int s, int e, int accu, int i) {
        if (s == e) {
            return min(accu, tree[p].getMin(dval));
        }

        int m = (s + e) >> 1;
        int myMin = tree[p].getMin(dval);
        int nAccu = min(accu, myMin);
        if (i <= m) {
            return getMin((p << 1) + 1, s, m, nAccu, i);
        } else {
            return getMin((p << 1) + 2, m + 1, e, nAccu, i);
        }
    }


};

void test1() {
    SegTree st(10, 100);
    
    st.insertRange(0, 0, st.len - 1, 1, 5, 10);
    st.insertRange(0, 0, st.len - 1, 3, 6, 4);
    cout << st.getMin(0, 0, st.len - 1, st.dval, 4) << endl;
    cout << st.getMin(0, 0, st.len - 1, st.dval, 1) << endl;
    cout << st.getMin(0, 0, st.len - 1, st.dval, 7) << endl;

    st.removeRange(0, 0, st.len - 1, 1, 5, 10);
    cout << st.getMin(0, 0, st.len - 1, st.dval, 1) << endl;
}

void test2() {
    SegTree st(100000, 100000);

    for (int i = 0; i < 100000; i ++) {
        st.insertRange(0, 0, st.len - 1, 0, i, i);
    }

    cout << st.getMin(0, 0, st.len - 1, st.dval, 99) << endl;

    

    for (int i = 0; i < 100000; i ++) {
        st.removeRange(0, 0, st.len - 1, 0, i, i);
    }

    cout << st.getMin(0, 0, st.len - 1, st.dval, 99) << endl;
}

int main() {
    test2();
}