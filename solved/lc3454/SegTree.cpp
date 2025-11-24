#include <bits/stdc++.h>
using namespace std;


struct Node {
    int l = 0, r = 0, sum = 0, rangeCnt = 0;
};

// update: add or remove a range
// query: return length of union of ranges, overlapping ranges counted once only
// Node sum returns length of union of ranges that are contained in [s, e] only
// NOTE: only can remove ranges we added before
struct SegTree {
    int S, E, root = 0;
    vector<Node> tree; // as again tree[0] is the null node

    SegTree(int S, int E): S(S), E(E), tree(1, Node()) {
        tree.reserve(5000000);
    }

    void reset() {
        root = 0;
        tree.clear();
        tree.push_back(Node());
    }
    
    inline int getMid(int s, int e) {
        return s + ((e - s) >> 1);
    }

    // insert a ra
    int updateRange(int n, int s, int e, int l, int r, int val) {
        // update n if curr node is null
        if (n == 0) {
            tree.push_back(Node());
            n = tree.size() - 1;
        }

        Node& curr = tree[n];
        
        if (s == l && e == r) {
            curr.rangeCnt += val;
            curr.sum = (curr.rangeCnt > 0) ? (e - s + 1) : tree[curr.l].sum + tree[curr.r].sum;
            return n;
        } else if (s == e) {
            curr.rangeCnt += val;
            curr.sum = (curr.rangeCnt > 0) ? 1 : 0;
            return n;
        } 
        
        int m = getMid(s, e);
        if (r <= m) {
            curr.l = updateRange(curr.l, s, m, l, r, val);
        } else if (l > m) {
            curr.r = updateRange(curr.r, m + 1, e, l, r, val);
        } else {
            curr.l = updateRange(curr.l, s, m, l, m, val);
            curr.r = updateRange(curr.r, m + 1, e, m + 1, r, val);
        }
        
        curr.sum = (curr.rangeCnt > 0) ? (e - s + 1) : tree[curr.l].sum + tree[curr.r].sum;
        return n;
    }

    // val is either 1 to add a range, -1 to remove a range, no other value
    void insert(int l, int r) {
        root = updateRange(root, S, E, l, r, 1);
    }

    void remove(int l, int r) {
        root = updateRange(root, S, E, l, r, -1);
    }

    inline int queryUnion() {
        return tree[root].sum;
    }
};

void test1() {
    SegTree st(0, 3 * 1e5 - 1);

    for (int i = 100000; i < 200000; i ++) {
        st.insert(i, i);
    }
    cout << st.queryUnion() << endl;

    for (int i = 100000; i < 200000; i ++) {
        st.remove(i, i);
    }
    cout << st.queryUnion() << endl;
}

void test2() {
    SegTree st(0, 9);

    st.insert(1, 5);
    st.insert(4, 7);
    cout << st.queryUnion() << endl;

    st.remove(4, 7);
    cout << st.queryUnion() << endl;

    st.insert(4, 7);
    st.insert(3, 6);
    cout << st.queryUnion() << endl;

    st.remove(4, 7);
    cout << st.queryUnion() << endl;
}

void test3() {
    SegTree st(0, 10);

    st.insert(1, 5);
    st.insert(3, 8);
    st.insert(2, 5);
    cout << st.queryUnion() << endl;

    st.remove(2, 5);
    cout << st.queryUnion() << endl;

    st.remove(1, 5);
    cout << st.queryUnion() << endl;
}

int main() {
    test1();

}