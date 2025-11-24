#include <bits/stdc++.h>
using namespace std;

// segment tree, find leftmost index s.t arr[idx] >= val, and set arr[idx] to 0

struct SegTree {
    int len;
    vector<int> tree;

    SegTree(const vector<int>& arr): len(arr.size()), tree(4 * len, 0) {
        build(0, 0, len - 1, arr);
    }


    void build(int p, int s, int e, const vector<int>& arr) {
        if (s == e) {
            tree[p] = arr[s];
            return;
        }

        int m = (s + e) >> 1;
        build((p << 1) + 1, s, m, arr);
        build((p << 1) + 2, m + 1, e, arr);
        tree[p] = max(tree[(p << 1) + 1], tree[(p << 1) + 2]);
    }

    // set arr[idx] to 0
    void updatePoint(int p, int s, int e, int idx) {
        if (s == e) {
            tree[p] = 0;
            return;
        }

        int m = (s + e) >> 1;
        
        if (idx <= m) updatePoint((p << 1) + 1, s, m, idx);
        else updatePoint((p << 1) + 2, m + 1, e, idx);
        
        tree[p] = max(tree[(p << 1) + 1], tree[(p << 1) + 2]);
    }

    // get leftmost i, s <= i <= e, such that arr[i] >= val
    // if don't have, return -1
    int getLeftmostIdx(int p, int s, int e, int val) {
        if (tree[p] < val) {
            return -1;
        } else if (s == e) {
            return s;
        }

        int m = (s + e) >> 1;
        
        if (tree[(p << 1) + 1] >= val) {
            return getLeftmostIdx((p << 1) + 1, s, m, val);
        } else {
            return getLeftmostIdx((p << 1) + 2, m + 1, e, val);
        }
    }
};

class Solution {
public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        int cnt = 0;
        SegTree st(baskets);

        for (int x : fruits) {
            int idx = st.getLeftmostIdx(0, 0, st.len - 1, x);
            
            if (idx == -1) continue;

            cnt++;
            st.updatePoint(0, 0, st.len - 1, idx);
        }

        return fruits.size() - cnt;
    }
};

int main() {
   Solution sol;

   vector<int> fruits = {4,2,5};
   vector<int> baskets = {3,5,4};

   cout << sol.numOfUnplacedFruits(fruits, baskets) << endl;
}