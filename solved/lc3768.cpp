#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// sparse segment tree and sliding window.
// segment tree stores how many counts of elems having value x.
// when moving window 1 elem to the right, for the element to remove, 
// we remove that element first, then find how many elems are less 
// than it. 
// for new element we are adding, find how many elements greater than it.

struct Node {
    ll sum = 0;
    Node* l = nullptr, *r = nullptr;

    static Node* get_left(Node *n) {
        return (n == nullptr) ? nullptr : n->l;
    }

    static Node* get_right(Node *n) {
        return (n == nullptr) ? nullptr : n->r;
    }

    static ll get_sum(Node *n) {
        return (n == nullptr) ? 0 : n->sum;
    }
};

struct SparseSegTree {
    vector<Node> node_store;

    Node* make_node() {
        node_store.emplace_back();
        return &node_store.back();
    }

    int S = 1, E = int(1e9);
    Node *root = nullptr;

    SparseSegTree(int len, int S = 1, int E = 1000000000): S(S), E(E) {
        node_store.reserve(40 * len);
    }

    // v == -1, if we want to remove an element
    Node *insert(int i, int v = 1, Node *curr = nullptr, int s = -1, int e = -1) {
        if (s == -1) {
            curr = root;
            s = S, e = E;
        }

        if (curr == nullptr) {
            curr = make_node();
            curr->sum = v;
        } else {
            curr->sum += v;
        }

        if (s == e) return curr;

        int m = s + ((e - s) >> 1);
        if (i <= m) {
            curr->l = insert(i, v, curr->l, s, m);
        } else {
            curr->r = insert(i, v, curr->r, m + 1, e);
        }

        if (s == S && e == E) root = curr;

        return curr;
    }

    ll range_sum(int l, int r, Node *curr = nullptr, int s = -1, int e = -1) {
        if (s == -1) {
            curr = root;
            s = S, e = E;
        }

        if (s == l && e == r) return Node::get_sum(curr);

        int m = s + ((e - s) >> 1);
        if (r <= m) {
            return range_sum(l, r, Node::get_left(curr), s, m);
        } else if (l > m) {
            return range_sum(l, r, Node::get_right(curr), m + 1, e);
        } else {
            return range_sum(l, m, Node::get_left(curr), s, m) + range_sum(m + 1, r, Node::get_right(curr), m + 1, e);
        }
    }
};

class Solution {
public:
    long long minInversionCount(vector<int>& nums, int k) {
        ll best = (ll) 1e10;
        ll curr_inv = 0;

        int mi = *min_element(nums.begin(), nums.end()), ma = *max_element(nums.begin(), nums.end());
        SparseSegTree st(nums.size(), mi, ma);
        
        for (int i = 0; i < k; i++) {
            ll invs = (nums[i] == ma) ? 0 : st.range_sum(nums[i] + 1, ma);
            curr_inv += invs;
            
            st.insert(nums[i]);
        }
        //cout << curr_inv << endl;
        best = curr_inv;

        for (int i = 1; i <= nums.size() - k; i++) {
            st.insert(nums[i - 1], -1);
            curr_inv -= (nums[i - 1] == mi) ? 0 : st.range_sum(mi, nums[i - 1] - 1);
            curr_inv += (nums[i + k - 1] == ma) ? 0 : st.range_sum(nums[i + k - 1] + 1, ma);
            best = min(best, curr_inv);
            //cout << curr_inv << endl;
            st.insert(nums[i + k - 1]);
        }

        return best;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {26, 61, 89};
    int k = 1;
    cout << sol.minInversionCount(nums, k) << endl;

}