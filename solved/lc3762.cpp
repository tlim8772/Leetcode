#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
1st, we can make subarray equal iff each element in [l:r] is equal mod k.
use segment tree that stores [min, max] on arr[i] % k.
if min == max, then can make them all equal.
need to find median for arr[l:r], use persistent segment tree

actually a better way is to pre compute first_different.
first_different[i] = j, if j is the first index to the right s.t arr[j] % k is different.
so lets remove the segment tree.
can solve for [l, r] if first_different[l] > r.

for mininum num of op to make elems in [l,r] all equal, the best way is to make them
all equal to the median of the subarray.
eg 1 3 5 7 9, k = 2
make all elems 5, for all elems <= median, num ops is (5 * 3 - sum(1,3,5)) / 2 = 3

some tricks needed to get past MLE.
use vector<Node>, reserve size of len * 50 to ensure no re sizing, HENCE NO REALLOCATION 
WHICH WILL INVALIDATE POINTERS.
then we just pass aroung &vector<Node>[i].

perhaps, we should not use new T() in the future.
*/

struct Node {
    //static vector<unique_ptr<Node>> node_store;
    
    int cnt = 0;
    ll sum = 0;
    Node *l = nullptr, *r = nullptr;

    static Node* make_node() {
        return new Node();
        //node_store.emplace_back(new Node());
        //return node_store.back().get();
    }

    static int get_count(Node *n) {
        return (n != nullptr) ? n->cnt : 0;
    }

    static ll get_sum(Node* n) {
        return (n != nullptr) ? n->sum : 0;
    }

    static Node* get_left(Node* n) {
        return (n != nullptr) ? n->l : nullptr;
    }

    static Node* get_right(Node* n) {
        return (n != nullptr) ? n->r : nullptr;
    }
};

struct PST {
    vector<Node> node_store;

    Node* make_node() {
        node_store.emplace_back();
        return &node_store.back();
    }

    int S = 1, E = 1000000000;
    vector<Node*> trees;

    PST(int S, int E, int len): S(S), E(E) {
        node_store.reserve(len * 50);
    }

    Node* insert(int v, Node* curr, int s = -1, int e = -1) {
        if (s == -1) {
            s = S, e = E;
        }

        Node* new_curr = make_node();
        new_curr->cnt = Node::get_count(curr) + 1;
        new_curr->sum = Node::get_sum(curr) + v;

        if (s == e) {
            return new_curr;
        }

        int m = s + (e - s) / 2;
        if (v <= m) {
            new_curr->l = insert(v, Node::get_left(curr), s, m);
            new_curr->r = Node::get_right(curr);
        } else {
            new_curr->l = Node::get_left(curr);
            new_curr->r = insert(v, Node::get_right(curr), m + 1, e);
        }
        return new_curr;
    }

    void insert(int v) {
        Node* prev = (trees.size() == 0) ? nullptr : trees.back();
        trees.push_back(insert(v, prev));
    }

    // rank is 1 index
    int get_val_at_rank(int r, Node* left, Node* right, int s = -1, int e = -1) {
        if (s == -1) {
            s = S, e = E;
        }
        
        if (s == e) return s;

        int m = s + (e - s) / 2;
        Node* ll = Node::get_left(left), *lr = Node::get_right(left);
        Node* rl = Node::get_left(right), *rr = Node::get_right(right);
        int lcnt = Node::get_count(rl) - Node::get_count(ll), rcnt = Node::get_count(rr) - Node::get_count(lr);

        if (r <= lcnt) {
            return get_val_at_rank(r, ll, rl, s, m);
        } else {
            return get_val_at_rank(r - lcnt, lr, rr, m + 1, e);
        }
    }

    int get_val_at_rank(int r, int le, int ri) {
        Node *left = (le == 0) ? nullptr : trees[le - 1];
        Node *right = trees[ri];
        return get_val_at_rank(r, left, right);
    }
    
    ll get_sum_by_rank(int l, int r, Node* left, Node* right, int s = -1, int e = -1) {
        if (s == -1) {
            s = S, e = E;
        }

        int cnt = Node::get_count(right) - Node::get_count(left);

        if (s == e) {
            return (ll) s * (r - l + 1);
        }

        if (l == 1 && r == cnt) {
            return Node::get_sum(right) - Node::get_sum(left);
        }

        int m = s + (e - s) / 2;
        Node* ll = Node::get_left(left), *lr = Node::get_right(left);
        Node* rl = Node::get_left(right), *rr = Node::get_right(right);
        int lcnt = Node::get_count(rl) - Node::get_count(ll), rcnt = Node::get_count(rr) - Node::get_count(lr);
        if (r <= lcnt) {
            return get_sum_by_rank(l, r, ll, rl, s, m);
        } else if (l > lcnt) {
            return get_sum_by_rank(l - lcnt, r - lcnt, lr, rr, m + 1, e);
        } else {
            return get_sum_by_rank(l, lcnt, ll, rl, s, m) + get_sum_by_rank(1, r - lcnt, lr, rr, m + 1, e);
        }
    }

    ll get_sum_by_rank(int l, int r, int lpos, int rpos) {
        Node *left = (lpos == 0) ? nullptr : trees[lpos - 1];
        Node *right = trees[rpos];
        return get_sum_by_rank(l, r, left, right);
    }

    int get_count(int l, int r) {
        Node* left = (l == 0) ? nullptr : trees[l - 1];
        Node* right = trees[r];
        return Node::get_count(right) - Node::get_count(left);
    }
};

//vector<unique_ptr<Node>> Node::node_store{};

class Solution {
public:
    vector<long long> minOperations(vector<int>& nums, int k, vector<vector<int>>& queries) {
        vector<ll> prefix_sums(nums.size(), 0);
        for (int i = 0; i < nums.size(); i++) {
            prefix_sums[i] = (i == 0) ? nums[i] : nums[i] + prefix_sums[i - 1];
        }
        
        vector<int> first_different(nums.size(), 0);
        int curr = nums[0] % k;
        int start = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] % k == curr) continue;
            
            for (int j = start; j < i; j++) {
                first_different[j] = i;
            }

            curr = nums[i] % k;
            start = i;
        }
        for (int j = start; j < nums.size(); j++) first_different[j] = nums.size();

        int s = *min_element(nums.begin(), nums.end());
        int e = *max_element(nums.begin(), nums.end());
        
        PST pst{s, e, (int) nums.size()};
        for (int x : nums) {
            pst.insert(x);
        }

        vector<ll> results;
        for (auto& q : queries) {
            int l = q[0], r = q[1];
            
            if (first_different[l] <= r) {
                results.push_back(-1);
                continue;
            }
            
            int total_cnt = pst.get_count(l, r);
            int median_rank = (total_cnt + 1) / 2;
            ll median = pst.get_val_at_rank(median_rank, l, r);

            ll lsum = pst.get_sum_by_rank(1, median_rank, l, r);
            ll l_op_cnts = ((median * median_rank) - lsum) / k;

            ll rsum = (median_rank == total_cnt) ? 0 : pst.get_sum_by_rank(median_rank + 1, total_cnt, l, r);
            ll r_op_cnts = (median_rank == total_cnt) ? 0 : (rsum - median * (r - l + 1 - median_rank)) / k;
            
            //cout << median_rank << endl;
            //cout << lsum << " " << rsum << endl;
            //cout << l_op_cnts << " " << r_op_cnts << endl;

            results.push_back(l_op_cnts + r_op_cnts);
        }

        return results;

    }
};

void testPersistentSegTree() {
}

int main() {
    //testPersistentSegTree();

    Solution sol;
    vector<int> nums = {1,2,3};
    int k = 1;
    vector<vector<int>> queries = {{0,0},{0,2}};

    vector<ll> ans = sol.minOperations(nums, k, queries);
    for (int a : ans) cout << a << " ";
    cout << endl;

}