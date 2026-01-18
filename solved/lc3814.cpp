#include <bits/stdc++.h>
using namespace std;
// use a segment tree to get best capacity for all items with cost <= target.
// great news that 1 <= cost[i], capacity[i] <= 10^5.

// point update, range max segment tree
struct SegTree {
    int n;
    vector<int> tree;
    
    SegTree(int n): n(n), tree(4 * n, 0) {}

    void update(int i, int v, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = n - 1;
        if (s == e) {
            tree[p] = max(tree[p], v);
            return;
        }

        int m = (s + e) >> 1;
        if (i <= m) {
            update(i, v, (p << 1) + 1, s, m);
        } else {
            update(i, v, (p << 1) + 2, m + 1, e);
        }
        tree[p] = max(tree[(p << 1) + 1], tree[(p << 1) + 2]);
    }

    int query(int l, int r, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = n - 1;
        if (s == l && e == r) {
            return tree[p];
        }

        int m = (s + e) >> 1;
        if (r <= m) {
            return query(l, r, (p << 1) + 1, s, m);
        } else if (l > m) {
            return query(l, r, (p << 1) + 2, m + 1, e);
        } else {
            return max(
                query(l, m, (p << 1) + 1, s, m),
                query(m + 1, r, (p << 1) + 2, m + 1, e)
            );
        }
    }
};

class Solution {
public:
    int maxCapacity(vector<int>& costs, vector<int>& capacity, int budget) {
        SegTree st{100001};
        int best = 0;

        for (int i = costs.size() - 1; i > -1; i--) {
            int cost = costs[i], cap = capacity[i];
            if (cost >= budget) continue;

            int second = st.query(0, min(100000, budget - cost - 1));
            best = max(best, cap + second);
            //cout << cost << " " << cap << " " << second << endl;
            
            st.update(cost, cap);
        }
        //cout << best << endl;
        return best;
    }
};

int main() {
    Solution sol;
    vector<int> costs = {4,8,5,3};
    vector<int>capacity = {1,5,2,7};
    int budget = 8;

    sol.maxCapacity(costs, capacity, budget);

}