#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// here all values are 0 indexed, so -1 for each elem in a pair
// basically consider each conflicting pair [x,y] x < y as cover range [0,x] with y
// because for any starting index i <= x, we cannot end at index j, j >= y
// insert all ranges into a segtree, now query(i) is the min value among all ranges covering i
// num of good subarras starting at index i is query(i) - i

// now to find max subarrays after removing 1 conflicting pair
// we sort the pairs in decreasing y, then decreasing x
// we iterate from left to right, for sorted ranges
// when considering pair p, we maintain lim, the max of all p.x we have seen previously
// we remove the current range [0,x,y] here [0,x] are the start points, y is the covering val
// if p.x <= lim, no need to do anything, as removing this is useless, it is covered by other ranges with lower (or equal)
// levels
// or if p.x <= next p.x and p.y = next p.y can also skip
// else for (idx = lim + 1; idx <= p[0]; idx ++) we minus p.y (the covering value), add in new covering val which is query(i)

// then find the new num of valid subarrays

struct Pair {
    int l1, c1;

    bool operator<(const Pair& p2) {
        return l1 < p2.l1;
    }
};

struct Node {
public:
    vector<Pair> twoBest; // an optimisation is to onnly store the 2 best values
                          // this only works if we only execute: remove 1 range, do queries, add removed range back

    inline void removeVal(int v) {
        for (int i = 0; i < twoBest.size(); i ++) {
            if (twoBest[i].l1 == v) {
                twoBest[i].c1 --;
                if (twoBest[i].c1 == 0) twoBest.erase(twoBest.begin() + i);
                sort(twoBest.begin(), twoBest.end());
            }
        }
    }

    inline void addVal(int v) {
        for (int i = 0; i < twoBest.size(); i ++) {
            if (twoBest[i].l1 == v) {
                twoBest[i].c1 ++;
                return;
            }
        }

        twoBest.push_back({v, 1});
        sort(twoBest.begin(), twoBest.end());
        if (twoBest.size() > 2) twoBest.pop_back();
    }

    inline int getMin(int dval) {
        return (twoBest.empty()) ? dval : twoBest[0].l1;
    }
};

struct SegTree {
    int len;
    int dval;
    vector<Node> tree;

    SegTree() {}

    // defaultVal: the MAXIMUM limit
    SegTree(int n, int defaultVal): len(n), dval(defaultVal), tree(4 * n, Node()) {
        insertRange(0, 0, n - 1, 0, n - 1, defaultVal);
    }


    void insertRange(int p, int s, int e, int l, int r, int val) {
        if (s == e || (s == l && e == r)) {
            tree[p].addVal(val);
            return;
        }

        int m = (s + e) >> 1;
        if (r <= m) {
            insertRange((p << 1) + 1, s, m, l, r, val);
        } else if (l > m) {
            insertRange((p << 1) + 2, m + 1, e, l, r, val);
        } else {
            insertRange((p << 1) + 1, s, m, l, m, val);
            insertRange((p << 1) + 2, m + 1, e, m + 1, r, val);
        }
    }

    // can only remove a range you previously added before, up to user to maintain this invariant
    void removeRange(int p, int s, int e, int l, int r, int val) {
        if (s == e || (s == l && e == r)) {
            tree[p].removeVal(val);
            return;
        }

        int m = (s + e) >> 1;
        if (r <= m) {
            removeRange((p << 1) + 1, s, m, l, r, val);
        } else if (l > m) {
            removeRange((p << 1) + 2, m + 1, e, l, r, val);
        } else {
            removeRange((p << 1) + 1, s, m, l, m, val);
            removeRange((p << 1) + 2, m + 1, e, m + 1, r, val);
        }
    }

    int getMin(int p, int s, int e, int accu, int i) {
        if (s == e) {
            return min(accu, tree[p].getMin(dval));
        }

        int m = (s + e) >> 1;
        int myMin = tree[p].getMin(dval);
        int nAccu = min(accu, myMin);
        if (i <= m) {
            return getMin((p << 1) + 1, s, m, nAccu, i);
        } else {
            return getMin((p << 1) + 2, m + 1, e, nAccu, i);
        }
    }


};

class Solution {
public:
    vector<vector<int>> arr;
    SegTree st;

    void process(int n, vector<vector<int>>& ranges) {
        st = SegTree(n, n);
        arr = vector(n, vector<int>());
        
        for (vector<int>& v : ranges) {
            v[0] --; v[1] --;
            if (v[0] > v[1]) swap(v[0], v[1]);
        }
        
        sort(ranges.begin(), ranges.end(), [] (const vector<int>& v1, const vector<int>& v2) -> bool {
            return (v1[1] == v2[1]) ? v1[0] < v2[0] : v1[1] < v2[1];
        });

        for (vector<int>& v : ranges) st.insertRange(0, 0, st.len - 1, 0, v[0], v[1]);

        for (vector<int>& v : ranges) {
            int s = min(v[0], v[1]), e = max(v[0], v[1]);
            arr[s].push_back(e);
        }

        for (vector<int>& v : arr) sort(v.begin(), v.end());
    }

    long long maxSubarrays(int n, vector<vector<int>>& conflictingPairs) {
        process(n, conflictingPairs);

        ll toMinus = (ll) (n - 1) * n / 2;
        ll best = 0;

        ll sum = 0;
        int lim1 = -1;
        for (vector<int>& p : conflictingPairs) {
            if (p[0] <= lim1) continue;
            
            for (int i = lim1 + 1; i <= p[0]; i ++) {
                sum += p[1];
            }
            lim1 = p[0];
        }
        sum += (ll) (n - (lim1 + 1)) * n;
        
        cout << sum - toMinus << endl;

        int lim2 = -1;
        for (int idx = 0; idx < conflictingPairs.size(); idx ++) {
            vector<int>& p = conflictingPairs[idx];
            // that means already covered by a lower range
            if (p[0] <= lim2) continue;

            // that means already covered by a range at the same level, but is to the right
            // removing this range does not do anything. e.g [1,10] [5,10], removing [1,10] is useless
            if (idx != conflictingPairs.size() - 1 && conflictingPairs[idx + 1][1] == conflictingPairs[idx][1]) continue;
            
            ll temp = sum - (ll) (p[0] - lim2) * p[1];
            st.removeRange(0, 0, st.len - 1, 0, p[0], p[1]);
            
            for (int i = lim2 + 1; i <= p[0]; i ++) {
                int nlim = (arr[p[0]].size() == 1) ? n : arr[p[0]][1]; 
                nlim = min(nlim, st.getMin(0, 0, st.len - 1, st.dval, i));
                
                temp += st.getMin(0, 0, st.len - 1, st.dval, i);
            }

            st.insertRange(0, 0, st.len - 1, 0, p[0], p[1]);
            best = max(best, temp - toMinus);

            lim2 = p[0];
        }

        return best;


    }
    
};


int main() {
    Solution sol;

    int n = 10;
    vector<vector<int>> pairs = {{10,5},{3,8}};

    cout << sol.maxSubarrays(n, pairs) << endl;
}