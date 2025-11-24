#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// find at each index i the ops needed to make every elem in [i, i + x - 1] equal
// optimal value is to make all elems = median
// then do dp
// lemma: we never have to take >k subarrays

struct Node {
    int l = 0, r = 0, cnt = 0;
    ll sum = 0;

    Node() {}

    Node(int cnt): cnt(cnt) {}
};

struct SegTree {
    int S, E;
    int root = 0;
    vector<Node> tree;

    SegTree(int S, int E, int len): S(S), E(E), tree(1, Node()) {
        tree.reserve(30 * len);
    }

    // add a val (1 or -1) at index i
    int add(int p, int s, int e, int i, int v) {
        if (p == 0) {
            p = tree.size();
            tree.emplace_back();
            if (s == S && e == E) root = p;
        }
        
        Node& node = tree[p];
        
        
        if (s == e) {
            node.cnt += v;
            node.sum = (ll) node.cnt * s;
            return p;
        }

        int m = (s + e) >> 1;
        if (i <= m) {
            node.l = add(node.l, s, m, i, v);
        } else {
            node.r = add(node.r, m + 1, e, i, v);
        }
        node.cnt = tree[node.l].cnt + tree[node.r].cnt;
        node.sum = tree[node.l].sum + tree[node.r].sum;

        return p;
    }

    int getElem(int p, int s, int e, int i) {
        if (s == e) {
            return s;
        }

        int m = (s + e) >> 1;
        Node& node = tree[p];
        if (i <= tree[node.l].cnt) {
            return getElem(node.l, s, m, i);
        } else {
            return getElem(node.r, m + 1, e, i - tree[node.l].cnt);
        }
    }  

    // l, r are 1 indexed
    ll getSum(int p, int s, int e, int l, int r) {
        Node& node = tree[p];
        int rangeCnt = r - l + 1;
        
        if (s == e) {
            return (ll) s * rangeCnt;
        } else if (rangeCnt == node.cnt) {
            return node.sum;
        }

        int m = (s + e) >> 1;
        if (r <= tree[node.l].cnt) {
            return getSum(node.l, s, m, l, r);
        } else if (l > tree[node.l].cnt) {
            return getSum(node.r, m + 1, e, l - tree[node.l].cnt, r - tree[node.l].cnt);
        } else {
            return getSum(node.l, s, m, l, tree[node.l].cnt) + getSum(node.r, m + 1, e, 1, r - tree[node.l].cnt);
        }
    }
};

class Solution {
public:
    int LEN, X;
    int K; // k ranges from 0 to K
    vector<ll> opsNeeded;
    vector<ll> dp;

    inline int coor(int idx, int k) {
        return idx * (K + 1) + k;
    }

    void processOpsNeeded(vector<int>& nums, int x) {
        SegTree st(-1000000, 1000000, nums.size());
        opsNeeded = vector<ll>(nums.size() - x + 1, 0);
        
        // for index 0
        for (int i = 0; i < x; i ++) {
            st.add(st.root, st.S, st.E, nums[i], 1);
        }

        for (int i = 0; i < nums.size() - x + 1; i ++) {
            if (i != 0) {
                st.add(st.root, st.S, st.E, nums[i - 1], -1);
                st.add(st.root, st.S, st.E, nums[i + x - 1], 1);
            }

            int idxBelow = x >> 1;
            int idxAbove = (x % 2 == 0) ? idxBelow + 1 : idxBelow + 2;
            ll sumBelow = st.getSum(st.root, st.S, st.E, 1, idxBelow);
            ll sumAbove = st.getSum(st.root, st.S, st.E, idxAbove, x);
            opsNeeded[i] = sumAbove - sumBelow;
        }
    }

    ll helper(int i, int k) {
        int pos = coor(i, k);
        if (k == 0) {
            return 0;
        } else if (i + X - 1 >= LEN) {
            return 1e12;
        } else if (dp[pos] != -1) {
            return dp[pos];
        } else {
            ll take = opsNeeded[i] + helper(i + X, k - 1);
            ll notake = helper(i + 1, k);
            ll ans = min(take, notake);
            dp[pos] = ans;
            return ans;
        }

    }
    
    
    
    
    
    long long minOperations(vector<int>& nums, int x, int k) {
        LEN = nums.size(); X = x; K = k;
        dp = vector<ll>(nums.size() * (k + 1), -1);
        processOpsNeeded(nums, x);

        for (int x : opsNeeded) cout << x << endl;

        ll ans = helper(0, k);
        return ans;
    }
};
