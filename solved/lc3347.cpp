#include <bits/stdc++.h>
using namespace std;

// segment tree of range [val - k, val + k]
// then we find the value which intersects the most ranges. We minus the elems with the same value, then
// add min(k, #ranges - #elems with same value)
// we only need to consider val, val - k and val + k
// because the optimal value, it lies betweem [v - k, v + k] for all elems taken, we take the smallest v + k and
// biggest v - k, notice it is either a end point, or the value of the elem itself


struct SparseSegTree {
    struct Node {
        int l = 0, r = 0;
        int sum = 0;
    };
    
    int start, end;
    int root = 0;
    vector<Node> tree; // tree[0] is the null node, and its l/r points back to itself

    SparseSegTree(int start, int end): start(start), end(end), tree(1, {0, 0, 0}) {
        tree.reserve(1e6);
    }

    // returns index of the node created, or the curr node if no node is created
    int insert(int idx, int s, int e, int l, int r) {
        // if it is a null node, make a new one
        if (idx == 0) {
            tree.push_back({0, 0, 0});
            idx = tree.size() - 1;

            if (s == start && e == end) root = idx;
        }

        if (s == e || (s == l && e == r)) {
            tree[idx].sum ++;
            return idx;
        }

        int m = (s + e) >> 1;
        if (r <= m) {
            tree[idx].l = insert(tree[idx].l, s, m, l, r);
        } else if (l > m) {
            tree[idx].r = insert(tree[idx].r, m + 1, e, l, r);
        } else {
            tree[idx].l = insert(tree[idx].l, s, m, l, m);
            tree[idx].r = insert(tree[idx].r, m + 1, e, m + 1, r);
        }

        return idx;
    }

    int getNumRange(int idx, int s, int e, int val) {
        if (idx == 0) {
            return 0;
        }
        
        if (s == e) {
            return tree[idx].sum;
        }

        int m = (s + e) >> 1;
        if (val <= m) {
            return tree[idx].sum + getNumRange(tree[idx].l, s, m, val);
        } else {
            return tree[idx].sum + getNumRange(tree[idx].r, m + 1, e, val);
        }

    }
};

class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        SparseSegTree st(-1e9 + 1, 1e9 + 1e5);
        unordered_set<int> values;
        unordered_map<int, int> freq;
        
        for (int x : nums) {
            freq[x] ++;
            values.insert(x);
            values.insert(x - k);
            values.insert(x + k);

            st.insert(st.root, st.start, st.end, x - k, x + k);
        }

        int best = 0;
        for (int x : values) {
            int cnt = st.getNumRange(st.root, st.start, st.end, x);
            int res = freq[x] + min(numOperations, cnt - freq[x]);
            best = max(best, res);
        }

        return best;

    }
};

/*int main() {
    SparseSegTree st(-1e9, 1e9);

    st.insert(st.root, st.start, st.end, 10, 20);
    st.insert(st.root, st.start, st.end, 5, 15);
    
    cout << st.getNumRange(st.root, st.start, st.end, 10) << endl;
    cout << st.getNumRange(st.root, st.start, st.end, 17) << endl;

    st.insert(st.root, st.start, st.end, 10, 1e7);
    st.insert(st.root, st.start, st.end, 1e5, 1e8);

    cout << st.getNumRange(st.root, st.start, st.end, 12) << endl;
    cout << st.getNumRange(st.root, st.start, st.end, 1e8) << endl;

}*/

int main() {
    vector<int> arr = {5,11,20,20};
    int k = 5;
    int numOps = 1;
    Solution sol;
    cout << sol.maxFrequency(arr, k, numOps) << endl;
}