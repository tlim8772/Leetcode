#include <bits/stdc++.h>
using namespace std;

// use a seg tree.
// segtree stores for [l, r], result for {aa, ab, ba, bb}.
// i.e the min num of deletetions to make s[l, r] alternating, and starting with a and ending with b (for ab)
// starting with a and ending with a (for aa)

// to merge left and right, see Store::merge

struct Store {
    static const int INV = 100001;
    int len = 0;
    int aa = 0, ab = 0, ba = 0, bb = 0;

    static Store merge(const Store& s1, const Store& s2) {
        // must remember that we can actually delete everything in s1 or s2
        int aa = min({s1.aa + s2.ba, s1.ab + s2.aa, s1.aa + s2.len, s1.len + s2.aa});
        int ab = min({s1.aa + s2.bb, s1.ab + s2.ab, s1.ab + s2.len, s1.len + s2.ab});
        int ba = min({s1.ba + s2.ba, s1.bb + s2.aa, s1.ba + s2.len, s1.len + s2.ba});
        int bb = min({s1.ba + s2.bb, s1.bb + s2.ab, s1.bb + s2.len, s1.len + s2.bb});
        return Store{s1.len + s2.len, aa, ab, ba, bb};
    }

    static Store make_single(char c) {
        return (c == 'A') ? Store{1, 0, INV, INV, INV} : Store{1, INV, INV, INV, 0};
    }

    int get_res() {
        return min({aa, ab, ba, bb});
    }

    string to_string() {
        return std::format("{} {} {} {}", aa, ab, ba, bb);
    }
};

struct SegTree {
    int len;
    vector<Store> tree;

    SegTree(const string& s): len(s.size()), tree(4 * len, Store{}) {
        build(0, 0, len - 1, s);
    }

    void build(int p, int s, int e, const string& str) {
        if (s == e) {
            tree[p] = Store::make_single(str[s]);
            return;
        }

        int m = (s + e) >> 1;
        build((p << 1) + 1, s, m, str);
        build((p << 1) + 2, m + 1, e, str);
        tree[p] = Store::merge(tree[(p << 1) + 1], tree[(p << 1) + 2]);
    }

    void update_point(int i, char c, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;

        if (s == e) {
            tree[p] = Store::make_single(c);
            return;
        }

        int m = (s + e) >> 1;
        if (i <= m) {
            update_point(i, c, (p << 1) + 1, s, m);
        } else {
            update_point(i, c, (p << 1) + 2, m + 1, e);
        }
        tree[p] = Store::merge(tree[(p << 1) + 1], tree[(p << 1) + 2]);
    }

    Store range_query(int l, int r, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;

        if (s == l && e == r) {
            return tree[p];
        }

        int m = (s + e) >> 1;
        if (r <= m) {
            return range_query(l, r, (p << 1) + 1, s, m);
        } else if (l > m) {
            return range_query(l, r, (p << 1) + 2, m + 1, e);
        } else {
            Store lres = range_query(l, m, (p << 1) + 1, s, m); 
            Store rres = range_query(m + 1, r, (p << 1) + 2, m + 1, e);
            return Store::merge(lres, rres);
        }
    }
};

class Solution {
public:
    vector<int> minDeletions(string s, vector<vector<int>>& queries) {
        SegTree st(s);
        vector<int> out;

        for (auto& q : queries) {
            if (q[0] == 1) {
                s[q[1]] = (s[q[1]] == 'A') ? 'B' : 'A';
                st.update_point(q[1], s[q[1]]);
            } else {
                Store ans = st.range_query(q[1], q[2]);
                out.push_back(ans.get_res());
            }
        }

        return out;
    }
};

int main() {
    SegTree st("AAA");
    cout << st.tree[1].to_string() << endl;
    cout << st.tree[2].to_string() << endl;
    cout << st.tree[0].get_res() << endl;
}