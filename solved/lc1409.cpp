#include <bits/stdc++.h>
using namespace std;

// use segtree to solve in nlogn instead of n^2
// suppose we have 5 4 3 2 1, here right means 1st. I f we query 3 for example, we add 3 the front
// 5 4 3 2 1 3, now we have the prev pos of 3, at index 2, we add a range of -1 to range [3,4]
// so now the segtree arr is [4,3,2,1,0]
// when we query 3, it becomes [4,3,3,2,1,0], and now for number 3, we look at index 5, not 1

struct SegTree {
    int len;
    vector<int> tree;

    SegTree(int n): len(n), tree(4 * n, 0) {}

    void addRange(int p, int s, int e, int l, int r, int v) {
        if (s == e || (s == l && e == r)) {
            tree[p] += v;
            return;
        }

        int m = (s + e) >> 1;
        if (r <= m)  {
            addRange((p << 1) + 1, s, m, l, r, v);
        } else if (l > m) {
            addRange((p << 1) + 2, m + 1, e, l, r, v);
        } else {
            addRange((p << 1) + 1, s, m, l, m, v);
            addRange((p << 1) + 2, m + 1, e, m + 1, r, v);
        }
    }

    int query(int p, int s, int e, int i) {
        if (s == e) {
            return tree[p];
        }

        int m = (s + e) >> 1;
        if (i <= m) {
            return tree[p] + query((p << 1) + 1, s, m, i);
        } else {
            return tree[p] + query((p << 1) + 2, m + 1, e, i);
        }
    }
};

class Solution {
public:
    vector<int> processQueries(vector<int>& queries, int m) {
        
        SegTree st(m + queries.size());
        vector<int> myPos(m + 1, 0);
        vector<int> out;

        for (int i = m; i >= 1; i --) {
            myPos[i] = m - i;
            st.addRange(0, 0, st.len - 1, m - i, m - i, i - 1);
        }

        int newPos = m;
        for (int q : queries) {
            int pos = st.query(0, 0, st.len - 1, myPos[q]);
            out.push_back(pos);

            if (pos == 0) continue;
            st.addRange(0, 0, st.len - 1, myPos[q] + 1, newPos - 1, 1);
            
            myPos[q] = newPos;
            newPos ++;

        }

        return out;
    }
};

int main() {
    Solution sol;
    vector<int> query = {7,5,5,8,3};
    int m = 8;

    vector<int> ans = sol.processQueries(query, m);
    for (int x : ans) cout << x << endl;
}