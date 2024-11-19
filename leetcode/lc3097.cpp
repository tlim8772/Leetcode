#include <bits/stdc++.h>
using namespace std;

// use binary search seg tree

struct Pair {
    int idx;
    int res;
    

    Pair(int idx, int res): idx(idx), res(res){}
};

class SegTree {
public:
    int sz;
    vector<int> tree;

    SegTree(vector<int>& nums): sz(nums.size()), tree(4 * sz, 0) {
        build(0, 0, sz - 1, nums);
    }

    void build(int p, int s, int e, vector<int>& nums) {
        if (s == e) {
            tree[p] = nums[s];
            return;
        }

        int m = (s + e) >> 1;
        build((p << 1) + 1, s, m, nums);
        build((p << 1) + 2, m + 1, e, nums);
        tree[p] = tree[(p << 1) + 1] | tree[(p << 1) + 2];
    }

    // find the leftmost index s.t OR [idx ... resIdx] >= k
    // acc: accumulated answer from the left
    // only call this function if acc < k;

    // invariant: acc contains OR [idx .. s - 1] if idx < s, otherwise acc is 0
    Pair findLeftMost(int p, int s, int e, int idx, int k, int acc) {
        if (s == e) {
            // here idx >= s, cannot have s < idx
            int ans = acc | tree[p];
            return Pair(s, ans);
        }

        int m = (s + e) >> 1;
        if (idx > m) {
            return findLeftMost((p << 1) + 2, m + 1, e, idx, k, acc);
        } else if (idx <= s) {
            if ((acc | tree[p]) < k) {
                // case 1: [s, e] still not enough
                return Pair(e, acc | tree[p]);
            } else if ((acc | tree[(p << 1) + 1]) >= k) {
                // case 2a: [s, m] is more than enough
                return findLeftMost((p << 1) + 1, s, m, idx, k, acc);
            } else {
                // case 2b: [s, m] not enough
                return findLeftMost((p << 1) + 2, m + 1, e, idx, k, acc | tree[(p << 1) + 1]);
            }
        } else {
            Pair left = findLeftMost((p << 1) + 1, s, m, idx, k, acc);
            return (left.res >= k) ? left : findLeftMost((p << 1) + 2, m + 1, e, idx, k, left.res);

        }

    }
    
};


class Solution {
public:
    int minimumSubarrayLength(vector<int>& nums, int k) {
        SegTree st(nums);
        int best = 999999999;
        for (int i = 0; i < nums.size(); i ++) {
            Pair p = st.findLeftMost(0, 0, st.sz - 1, i, k, 0);
            if (p.res < k) continue;
            best = min(best, p.idx - i + 1);
        }
        return (best > 200000) ? -1 : best;
    }
};

int main() {
    vector<int> nums = {3,1,2,5,3,6,7};
    SegTree st(nums);
    cout << st.findLeftMost(0, 0, st.sz - 1, 4, 7, 0).idx;
}