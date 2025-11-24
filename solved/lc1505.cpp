#include <bits/stdc++.h>
using namespace std;

// basically, we have a greedy solution, k = num of swaps left
// start from idx 0, find a window of size k + 1, then find min elem in that windows, then move that elem
// to idx 0, through swaps. Then decrease k. elems before min elem need to be shifted to the right
// repeat for idx 1, 2 ... size - 1, or until k = 0
// 
// notice that once an elem is moved, it does not matter
// only matters is in range [l, r] of original string, how many valid elems left
// so if window is size k + 1, we only need to consider among the 1st k + 1 valid elems left, what is the min elem


struct Pair {
    int val;
    int idx;
    int size;

    Pair(int val, int idx, int size): val(val), idx(idx), size(size) {}

    void print() {
        printf("val: %d, idx: %d, size: %d\n", val, idx, size);
    }
};

// tree[p] stores: val of smallest remaining digit, idx of that val in ORIGINAL string, number of remaining elements
// in [l, r] of original string
class SegTree {
public:
    int MAX = 999999;
    int sz;
    vector<Pair> tree;


    SegTree(string& arr): sz(arr.size()), tree(sz << 2, Pair(0, 0, 0)) {
        build(0, 0, sz - 1, arr);
    }

    void build(int p, int s, int e, string& arr) {
        if (s == e) {
            tree[p] = Pair(arr[s] - '0', s, 1);
        } else {
            int m = (s + e) >> 1;
            int left = (p << 1) + 1; 
            int right = (p << 1) + 2;
            
            build(left, s, m, arr);
            build(right, m + 1, e, arr);
            int size = tree[left].size + tree[right].size;
            if (tree[left].val <= tree[right].val) {
                tree[p] = Pair(tree[left].val, tree[left].idx, size);
            } else {
                tree[p] = Pair(tree[right].val, tree[right].idx, size);
            }
        }
    }


    // pair.size is invalid.
    Pair findMin(int p, int s, int e, int size) {
        if (s == e) return tree[p];

        int m = (s + e) >> 1;
        if (size <= tree[(p << 1) + 1].size) return findMin((p << 1) + 1, s, m, size);
        else {
            Pair leftRes = tree[(p << 1) + 1];
            Pair rightRes = findMin((p << 1) + 2, m + 1, e, size - leftRes.size);
            if (leftRes.val <= rightRes.val) return leftRes;
            else return rightRes;
        }
    }

    void remove(int p, int s, int e, int idx) {
        if (s == e) {
            tree[p].val = MAX;
            tree[p].size = 0;
        } else {
            int m = (s + e) >> 1;
            if (idx <= m) remove((p << 1) + 1, s, m, idx);
            else remove((p << 1) + 2, m + 1, e, idx);

            int left = (p << 1) + 1; 
            int right = (p << 1) + 2;
            if (tree[left].val <= tree[right].val) {
                tree[p].val = tree[left].val;
                tree[p].idx = tree[left].idx;
                tree[p].size = tree[left].size + tree[right].size;
            } else {
                tree[p].val = tree[right].val;
                tree[p].idx = tree[right].idx;
                tree[p].size = tree[left].size + tree[right].size;
            }
        }
    }

    int findNumOfElemsToIdx(int p, int s, int e, int idx) {
        if (s == e || e == idx) return tree[p].size;
        
        int m = (s + e) >> 1;
        if (idx <= m) return findNumOfElemsToIdx((p << 1) + 1, s, m, idx);
        else return tree[(p << 1) + 1].size + findNumOfElemsToIdx((p << 1) + 2, m + 1, e, idx);
    }

    void collectRemaining(int p, int s, int e, string& store) {
        if (s == e) {
            if (tree[p].size) store += (char) (tree[p].val + '0');
        } else {
            int m = (s + e) >> 1;
            collectRemaining((p << 1) + 1, s, m, store);
            collectRemaining((p << 1) + 2, m + 1, e, store);
        }
    }
};

class Solution {
public:
    string minInteger(string num, int k) {
        SegTree st(num);
        string out = "";
        int numRemoved = 0;
        
        for (int i = 0; i < num.size() && k > 0; i ++) {
            int size = min(k + 1, (int) num.size() - numRemoved);
            
            Pair&& p = st.findMin(0, 0, st.sz - 1, size);
            int swaps = st.findNumOfElemsToIdx(0, 0, st.sz - 1, p.idx) - 1;
            st.remove(0, 0, st.sz - 1, p.idx);
            
            out += (char) (p.val + '0');
            k -= swaps;
            numRemoved ++;
        }

        st.collectRemaining(0, 0, st.sz - 1, out);
        return out;
        
        
    }
};


int main() {
    string str = "100";
    int k = 2;
    Solution sol;
    cout << sol.minInteger(str, k);
}

/*int main() {
    string str = "98716271";
    SegTree st(str);
    st.findMin(0, 0, st.sz - 1, 5).print();
    st.remove(0, 0, st.sz -1, 3);
    
    st.findMin(0, 0, st.sz - 1, 5).print();
    st.remove(0, 0, st.sz -1, 0);
    st.remove(0, 0, st.sz -1, 1);
    st.findMin(0, 0, st.sz - 1, 5).print();
    
    cout << st.findNumOfElemsToIdx(0, 0, st.sz - 1, 2);
}*/