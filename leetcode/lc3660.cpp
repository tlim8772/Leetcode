#include <bits/stdc++.h>
using namespace std;

// process elems from largest to smallest
// however, if that elem already has a result, we skip
// by doing so we can get some nice properties

// algo
// if elem already has result, skip.
// if not, use segtree to get max result for all elems lesser than it.
// notice we do not need to worry if these elems are actually to the right.
// result for this elem is max(elem val, segtree query)
// then, start iterating to the right, placing result for elems to the right
// until we encounter an elem that already has a result, then we stop.
// when giving an elem a result, update the segtree too.

// invariant 1:
// if we process an elem, it is the max in [0..pos]
// otherwise, there exist an elem larger than it on the left, when processing that elem
// we would have given this elem a value too.

// invariant 2:
// if we process an elem, all elems in the segtree that are lesser than this elem are to its right
// suppose not, some elem to the right and lesser than this elem is in segtree
// that means it is processed, only way is to have a larger elem than curr elem on the left.
// contradiction, see invariant 1.

// invariant 3: the result for this elem and for all elems to the right (until we stop) is correct
// proof by induction
// no proof, gut feeling haha

struct Node {
    int ma = 0;
    Node *l = nullptr, *r = nullptr;

    ~Node() {
        delete l;
        delete r;
    }
};

struct SegTree {
    int s = 0, e = 1e5;
    Node *root = nullptr;

    Node *insert(Node *curr, int s, int e, int i, int v) {
        if (curr == nullptr) {
            curr = new Node();
        }

        if (s == e) {
            curr->ma = v;
            return curr;
        }

        int m = s + ((e - s) >> 1);
        if (i <= m) {
            curr->l = insert(curr->l, s, m, i, v);
        } else {
            curr->r = insert(curr->r, m + 1, e, i, v);
        }
        curr->ma = max(curr->l == nullptr ? 0 : curr->l->ma, curr->r == nullptr ? 0 : curr->r->ma);
        
        if (s == this->s && e == this->e) {
            root = curr;
        }

        return curr;
    }

    // s <= l <= r <= r
    int rangeMax(Node *curr, int s, int e, int l, int r) {
        if (curr == nullptr) {
            return 0;
        } else if (s == e || (s == l && e == r)) {
            return curr->ma;
        }

        int m = s + ((e - s) >> 1);
        if (r <= m) {
            return rangeMax(curr->l, s, m, l, r);
        } else if (l > m) {
            return rangeMax(curr->r, m + 1, e, l, r);
        } else {
            int left = rangeMax(curr->l, s, m, l, m);
            int right = rangeMax(curr->r, m + 1, e, m + 1, r);
            return max(left, right);
        }
    }

    ~SegTree() {
        delete root;
    }
};

class Solution {
public:
    vector<pair<int,int>> getSortedElemWithPos(const vector<int>& nums) {
        vector<pair<int,int>> out;
        for (int i = 0; i < nums.size(); i++) {
            out.push_back({nums[i], i});
        }
        sort(out.begin(), out.end(), [](const pair<int,int>& p1, const pair<int,int>& p2) { return p1.first > p2.first; });
        return out;
    }

    unordered_map<int,int> getCompress(const vector<int>& nums) {
        vector<int> temp = nums;
        sort(temp.begin(), temp.end());

        unordered_map<int,int> out;
        int p = 1;
        for (int i = 0; i < temp.size(); i++) {
            if (out.contains(temp[i])) continue;
            out[temp[i]] = p++;
        }

        return out;
    }
    
    vector<int> maxValue(vector<int>& nums) {
        vector<pair<int,int>> sortedElemWithPos = getSortedElemWithPos(nums);
        vector<int> out(nums.size(), -1);
        unordered_map<int,int> compressMap = getCompress(nums);
        SegTree st;

        for (const auto& [val, pos] : sortedElemWithPos) {
            if (out[pos] != -1) continue;

            int compressedVal = compressMap[val];

            int jump = st.rangeMax(st.root, st.s, st.e, 0, compressedVal - 1);
            int ans = out[pos] = max(val, jump);
            st.insert(st.root, st.s, st.e, compressedVal, ans);

            for (int i = pos + 1; i < out.size(); i++) {
                if (out[i] != -1) break;
                out[i] = ans;
                st.insert(st.root, st.s, st.e, compressMap[nums[i]], ans);
            }
        }

        return out;
    }
};

int main() {
    Solution sol;

    vector<int> nums = {30,21,5,35,24};

    vector<int> res = sol.maxValue(nums);

    for (int r : res) {
        cout << r << " ";
    }
    cout << endl;
}

