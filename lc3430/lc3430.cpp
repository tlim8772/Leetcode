#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// consider doing the sum for minimum first
// we process elements from right to left.
// let say we are done with idx i + 1, so for x = i + 1, i + 2 ... len - 1, we know the minimum element in arr[i + 1, x]
// now the min value is decreasing
// for index i, we only need to update for min value of arr[i + 1, x] that is > arr[i]
// then we take the sum for the result of i, i + 1 ... i + k - 1
// we have to update the result for range [i, j], where j is such that min value of arr[i + 1, j] > arr[i] and 
// min value of arr[i + 1, j + 1] <= arr[i]
// use segment tree to do all of the above in O(logn)

struct Max {
    ll sum;
    ll m;

    Max() {}

    Max(ll sum, ll m): sum(sum), m(m) {}

    Max operator+(const Max& other) {
        return Max(sum + other.sum, max(m, other.m));
    }
};

struct MaxTree {
    int INVALID = -1e7;
    int len;
    vector<int> layer;
    vector<Max> tree;

    MaxTree(int len): len(len), layer(4 * len, INVALID), tree(4 * len, Max(0, 0)) {}

    MaxTree(const vector<int>& arr): len(arr.size()), layer(4 * len, INVALID), tree(4 * len, Max()) {
        build(0, 0, len - 1, arr);
    }

    int updateAccu(int old, int next) {
        return (old == INVALID) ? next : old;
    }
    
    Max getMaxUpdateAccu(int p, int s, int e, int accu) {
        int len = e - s + 1;
        if (accu != INVALID) {
            layer[p] = accu;
            return Max((ll) len * accu, accu);
        } else if (layer[p] != INVALID) {
            return Max((ll) len * layer[p], layer[p]);
        } else {
            return tree[p];
        }
    }

    Max getMax(int p, int s, int e, int accu) {
        int len = e - s + 1;
        if (accu != INVALID) {
            return Max((ll) len * accu, accu);
        } else if (layer[p] != INVALID) {
            return Max((ll) len * layer[p], layer[p]);
        } else {
            return tree[p];
        }
    }

    void build(int p, int s, int e, const vector<int>& arr) {
        if (s == e) {
            tree[p] = Max(arr[s], arr[s]);
            return;
        }

        int m = (s + e) >> 1;
        build((p << 1) + 1, s, m, arr);
        build((p << 1) + 2, m + 1, e, arr);
        tree[p] = tree[(p << 1) + 1] + tree[(p << 1) + 2];
    }

    Max updateRange(int p, int s, int e, int accu, int l, int r, int val) {
        if (s == e || (s == l && e == r)) {
            layer[p] = val;
            return Max((ll) (e - s + 1) * val, val);
        }

        int m = (s + e) >> 1;
        int newAccu = updateAccu(accu, layer[p]);
        Max left, right;
        
        if (r <= m) {
            left = updateRange((p << 1) + 1, s, m, newAccu, l, r, val);
            right = getMaxUpdateAccu((p << 1) + 2, m + 1, e, newAccu);
        } else if (l > m) {
            left = getMaxUpdateAccu((p << 1) + 1, s, m, newAccu);
            right = updateRange((p << 1) + 2, m + 1, e, newAccu, l, r, val);
        } else {
            left = updateRange((p << 1) + 1, s, m, newAccu, l, m, val);
            right = updateRange((p << 1) + 2, m + 1, e, newAccu, m + 1, r, val);
        }

        layer[p] = INVALID;
        tree[p] = left + right;
        return tree[p];
    }

    // gets the index >= idx s.t index is the smallest index s.t arr[index] > val
    int query1stMore(int p, int s, int e, int accu, int idx, int val) {
        if (s == e) {
            return (getMax(p, s, e, accu).m > val) ? s : -1;
        }

        int m = (s + e) >> 1;
        int newAccu = updateAccu(accu, layer[p]);
        
        if (idx <= s) {
            Max left = getMax((p << 1) + 1, s, m, newAccu);
            Max right = getMax((p << 1) + 2, m + 1, e, newAccu);
            Max total = getMax(p, s, e, accu);
            
            if (total.m < val) {
                return -1;
            } else if (left.m > val) {
                return query1stMore((p << 1) + 1, s, m, newAccu, idx, val);
            } else {
                return query1stMore((p << 1) + 2, m + 1, e, newAccu, idx, val);
            }
        } else if (idx > m) {
            return query1stMore((p << 1) + 2, m + 1, e, newAccu, idx, val);
        } else {
            int leftRes = query1stMore((p << 1) + 1, s, m, newAccu, idx, val);
            return (leftRes != -1) ? leftRes : query1stMore((p << 1) + 2, m + 1, e, newAccu, idx, val);
        }
        
    }

    ll querySum(int p, int s, int e, int accu, int l, int r) {
        if (s == e || (s == l && e == r)) {
            return getMax(p, s, e, accu).sum;
        }

        int m = (s + e) >> 1;
        int newAccu = updateAccu(accu, layer[p]);
        if (r <= m) {
            return querySum((p << 1) + 1, s, m, newAccu, l, r);
        } else if (l > m) {
            return querySum((p << 1) + 2, m + 1, e, newAccu, l, r);
        } else {
            return querySum((p << 1) + 1, s, m, newAccu, l, m) + querySum((p << 1) + 2, m + 1, e, newAccu, m + 1, r);
        }
    }
};

struct Min {
    ll sum;
    ll m;

    Min() {}

    Min(ll sum, ll m): sum(sum), m(m) {}

    Min operator+(const Min& other) {
        return Min(sum + other.sum, min(m, other.m));
    }
};


struct MinTree {
    int INVALID = -1e7;
    int len;
    vector<int> layer;
    vector<Min> tree;

    MinTree(int len): len(len), layer(4 * len, INVALID), tree(4 * len, Min(0, 0)) {}

    MinTree(const vector<int>& arr): len(arr.size()), layer(4 * len, INVALID), tree(4 * len, Min()) {
        build(0, 0, len - 1, arr);
    }

    int updateAccu(int old, int next) {
        return (old == INVALID) ? next : old;
    }
    
    Min getMinUpdateAccu(int p, int s, int e, int accu) {
        int len = e - s + 1;
        if (accu != INVALID) {
            layer[p] = accu;
            return Min((ll) len * accu, accu);
        } else if (layer[p] != INVALID) {
            return Min((ll) len * layer[p], layer[p]);
        } else {
            return tree[p];
        }
    }

    Min getMin(int p, int s, int e, int accu) {
        int len = e - s + 1;
        if (accu != INVALID) {
            return Min((ll) len * accu, accu);
        } else if (layer[p] != INVALID) {
            return Min((ll) len * layer[p], layer[p]);
        } else {
            return tree[p];
        }
    }

    void build(int p, int s, int e, const vector<int>& arr) {
        if (s == e) {
            tree[p] = Min(arr[s], arr[s]);
            return;
        }

        int m = (s + e) >> 1;
        build((p << 1) + 1, s, m, arr);
        build((p << 1) + 2, m + 1, e, arr);
        tree[p] = tree[(p << 1) + 1] + tree[(p << 1) + 2];
    }

    Min updateRange(int p, int s, int e, int accu, int l, int r, int val) {
        if (s == e || (s == l && e == r)) {
            layer[p] = val;
            return Min((ll) (e - s + 1) * val, val);
        }

        int m = (s + e) >> 1;
        int newAccu = updateAccu(accu, layer[p]);
        Min left, right;
        
        if (r <= m) {
            left = updateRange((p << 1) + 1, s, m, newAccu, l, r, val);
            right = getMinUpdateAccu((p << 1) + 2, m + 1, e, newAccu);
        } else if (l > m) {
            left = getMinUpdateAccu((p << 1) + 1, s, m, newAccu);
            right = updateRange((p << 1) + 2, m + 1, e, newAccu, l, r, val);
        } else {
            left = updateRange((p << 1) + 1, s, m, newAccu, l, m, val);
            right = updateRange((p << 1) + 2, m + 1, e, newAccu, m + 1, r, val);
        }

        layer[p] = INVALID;
        tree[p] = left + right;
        return tree[p];
    }

    // gets the index >= idx s.t index is the smallest index s.t arr[index] < val
    int query1stLess(int p, int s, int e, int accu, int idx, int val) {
        if (s == e) {
            return (getMin(p, s, e, accu).m < val) ? s : -1;
        }

        int m = (s + e) >> 1;
        int newAccu = updateAccu(accu, layer[p]);
        
        if (idx <= s) {
            Min left = getMin((p << 1) + 1, s, m, newAccu);
            Min right = getMin((p << 1) + 2, m + 1, e, newAccu);
            Min total = getMin(p, s, e, accu);
            
            if (total.m >= val) {
                return -1;
            } else if (left.m < val) {
                return query1stLess((p << 1) + 1, s, m, newAccu, idx, val);
            } else {
                return query1stLess((p << 1) + 2, m + 1, e, newAccu, idx, val);
            }
        } else if (idx > m) {
            return query1stLess((p << 1) + 2, m + 1, e, newAccu, idx, val);
        } else {
            int leftRes = query1stLess((p << 1) + 1, s, m, newAccu, idx, val);
            return (leftRes != -1) ? leftRes : query1stLess((p << 1) + 2, m + 1, e, newAccu, idx, val);
        }
        
    }

    ll querySum(int p, int s, int e, int accu, int l, int r) {
        if (s == e || (s == l && e == r)) {
            return getMin(p, s, e, accu).sum;
        }

        int m = (s + e) >> 1;
        int newAccu = updateAccu(accu, layer[p]);
        if (r <= m) {
            return querySum((p << 1) + 1, s, m, newAccu, l, r);
        } else if (l > m) {
            return querySum((p << 1) + 2, m + 1, e, newAccu, l, r);
        } else {
            return querySum((p << 1) + 1, s, m, newAccu, l, m) + querySum((p << 1) + 2, m + 1, e, newAccu, m + 1, r);
        }
    }
};

class Solution {
public:
    long long minMaxSubarraySum(vector<int>& nums, int k) {
        int len = nums.size();
        MinTree mintree(len);
        MaxTree maxtree(len);
        ll cnt = 0;

        cnt += 2 * nums.back();
        mintree.updateRange(0, 0, len - 1, mintree.INVALID, len - 1, len - 1, nums.back());
        maxtree.updateRange(0, 0, len - 1, mintree.INVALID, len - 1, len - 1, nums.back());

        for (int i = len - 2; i >= 0; i --) {
            int lessIdx = mintree.query1stLess(0, 0, len - 1, mintree.INVALID, i + 1, nums[i]);
            lessIdx = (lessIdx == -1) ? len - 1 : lessIdx - 1;
            mintree.updateRange(0, 0, len - 1, mintree.INVALID, i, lessIdx, nums[i]);
            ll minsum = mintree.querySum(0, 0, len - 1, mintree.INVALID, i, min(i + k - 1, len - 1));
            
            int moreIdx = maxtree.query1stMore(0, 0, len - 1, maxtree.INVALID, i + 1, nums[i]);
            moreIdx = (moreIdx == -1) ? len - 1 : moreIdx - 1;
            maxtree.updateRange(0, 0, len - 1, maxtree.INVALID, i, moreIdx, nums[i]);
            ll maxsum = maxtree.querySum(0, 0, len - 1, maxtree.INVALID, i, min(i + k - 1, len - 1));

            cnt += maxsum + minsum;
        }

        return cnt;


    }
};

int main() {
    Solution sol;
    vector<int> arr{1,-3,1};
    int k = 2;
    cout << sol.minMaxSubarraySum(arr, k) << endl;
}