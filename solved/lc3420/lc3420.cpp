#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// need to use a special segtree
// updateRange: make cost for all elem with idx i in [l,r] val - i
// updatePoint: make cost for elem at idx i val


// array good: array is non-decreasing
// op: increase an element by 1
// 2 pointers approach, start from the back. Suppose we know that for idx i + 1, we get good arrays until idx ptr
// for idx i, we only need to move ptr backwards, never forward, as when idx decrease, the cost to make array good only increases

// once iteration for idx i is done
// special segtree contains, at idx j, the cost to make elem j good, should we want to make a good array from idx i to j
// to update result from idx i + 1 to idx i
// we need to find the 1st elem to the right that is >= idx[i]
// eg ... 10, 5, 1, 4, 11
// if idx i is 10, we need to update the cost to make array good for elem 5, 1, 4
// specialSegTree enables us to update the cost for 5, 1, 4 to 10 - array[k]
// the cost to make arr[j] good if we are starting at idx i is max(arr[i, j]) - arr[j]
// so make MaxSegTree, and update accordingly

template <template<typename> typename T, typename S>
void print(T<S> arr) {
    for (S s : arr) {
        cout << s << " ";
    }
    cout << endl;
}

vector<int> getLeftMostGeq(vector<int> arr) {
    vector<int> stack;
    vector<int> out(arr.size(), arr.size());
    for (int i = 0; i < arr.size(); i ++) {
        while (!stack.empty() && arr[i] >= arr[stack.back()]) {
            out[stack.back()] = i;
            stack.pop_back();
        }
        stack.push_back(i);
    }
    return out;
}

struct MaxSegTree {
    int n;
    vector<int> tree;

    MaxSegTree() {}
    
    MaxSegTree(vector<int>& arr): n(arr.size()), tree(4 * n, 0) {
        build(0, 0, n - 1, arr);
    }

    void build(int p, int s, int e, vector<int>& arr) {
        if (s == e) {
            tree[p] = arr[s];
            return;
        }

        int m = (s + e) >> 1;
        build((p << 1) + 1, s, m, arr);
        build((p << 1) + 2, m + 1, e, arr);
        tree[p] = max(tree[(p << 1) + 1], tree[(p << 1) + 2]);
    }

    int query(int p, int s, int e, int l, int r) {
        if (s == e || (s == l && e == r)) return tree[p];

        int m = (s + e) >> 1;
        if (r <= m) return query((p << 1) + 1, s, m, l, r);
        else if (l > m) return query((p << 1) + 2, m + 1, e, l, r);
        else return max(query((p << 1) + 1, s, m, l, m), query((p << 1) + 2, m + 1, e, m + 1, r));
    }
};

// we have to support 2 updates. 
// update idx to be a val
// update(l, r, val): for all idx i, l <= i <= r value of idx i is val - arr[i]
// 1 query(l, r): sum of all idxs in [l, r]
// invariant: tree[p] contains sum of results from [s,e] if there is no layer at that node or above
// layer[p]: means we layer layer[p] over all idxs in [s,e]. Clearly, only the highest node layer matter
// i.e layer[p] = 5 and left child layer[(p << 1) + 1] is 10, the left child layer does not matter

struct SpecialSegTree {
    int n;
    vector<ll> sumtree;
    vector<ll> tree;
    vector<ll> layer; // layer[p] == -1 if the range [s,e] is not layered 

    SpecialSegTree(vector<int>& arr): n(arr.size()), sumtree(4 * n, 0), tree(4 * n, 0), layer(4 * n, -1) {
        build(0, 0, n - 1, arr);
    }
    

    void build(int p, int s, int e, vector<int>& arr) {
        if (s == e) {
            sumtree[p] = arr[s];
            return;
        }

        int m = (s + e) >> 1;
        build((p << 1) + 1, s, m, arr);
        build((p << 1) + 2, m + 1, e, arr);
        sumtree[p] = sumtree[(p << 1) + 1] + sumtree[(p << 1) + 2];
    }

    // gets the sum and also update layer[p] with the correct value if necessary
    ll getSumAndUpdate(int p, int s, int e, ll accu) {
        if (accu != -1) {
            layer[p] = accu;
            return accu * (e - s + 1) - sumtree[p];
        } else if (layer[p] != -1) {
            return layer[p] * (e - s + 1) - sumtree[p];
        } else {
            return tree[p];
        }
    }

    ll getSum(int p, int s, int e, ll accu) {
        if (accu != -1) {
            return accu * (e - s + 1) - sumtree[p];
        } else if (layer[p] != -1) {
            return layer[p] * (e - s + 1) - sumtree[p];
        } else {
            return tree[p];
        }
    }

    ll updateAccu(int oldAccu, int newAccu) {
        return (oldAccu == -1) ? newAccu : oldAccu;
    }

    // returns the sum of [s, e] after updating
    // all ranges that do not strictly contain the range updated, and nothing else, has their layer invalidated
    // accu is the layer val of the top most ancestor (if any), not including the curr node
    ll updatePoint(int p, int s, int e, ll accu, int idx, ll val) {
        if (s == e) {
            tree[p] = val;
            layer[p] = -1;
            return val;
        }
        int m = (s + e) >> 1;
        ll lsum, rsum;
        if (idx <= m) {
            lsum = updatePoint((p << 1) + 1, s, m, updateAccu(accu, layer[p]), idx, val);
            rsum = getSumAndUpdate((p << 1) + 2, m + 1, e, updateAccu(accu, layer[p]));
        } else if (idx > m) {
            lsum = getSumAndUpdate((p << 1) + 1, s, m, updateAccu(accu, layer[p]));
            rsum  = updatePoint((p << 1) + 2, m + 1, e, updateAccu(accu, layer[p]), idx, val);
        }
        layer[p] = -1;
        tree[p] = lsum + rsum;
        return tree[p];
    }


    // all ranges that do not strictly contain the range updated, and nothing else, has their layer invalidated
    ll updateRange(int p, int s, int e, ll accu, int l, int r, ll val) {
        if (s == e || (s == l && e == r)) {
            layer[p] = val;
            return val * (e - s + 1) - sumtree[p];
        }
        int m = (s + e) >> 1;
        ll lsum, rsum;
        if (r <= m) {
            lsum = updateRange((p << 1) + 1, s, m, updateAccu(accu, layer[p]), l, r, val);
            rsum = getSumAndUpdate((p << 1) + 2, m + 1, e, accu);
        } else if (l > m) {
            lsum = getSumAndUpdate((p << 1) + 1, s, m, updateAccu(accu, layer[p]));
            rsum = updateRange((p << 1) + 2, m + 1, e, updateAccu(accu, layer[p]), l, r, val);
        } else {
            lsum = updateRange((p << 1) + 1, s, m, updateAccu(accu, layer[p]), l, m, val);
            rsum = updateRange((p << 1) + 2, m + 1, e, updateAccu(accu, layer[p]), m + 1, r, val);
        }
        layer[p] = -1;
        tree[p] = lsum + rsum;
        return tree[p];

    }


    // fo this we know that s <= l <= r <= e
    // if layer exists, we can and must return the sum value immediately, to ensure the topmost layer val
    // is used
    ll query(int p, int s, int e, ll accu, int l, int r) {
        if (s == e || (s == l && e == r)) {
            return getSum(p, s, e, accu);
        }

        int m = (s + e) >> 1;
        if (r <= m) {
            return query((p << 1) + 1, s, m, updateAccu(accu, layer[p]), l, r);
        } else if (l > m) {
            return query((p << 1) + 2, m + 1, e, updateAccu(accu, layer[p]), l, r);
        } else {
            return query((p << 1) + 1, s, m, updateAccu(accu, layer[p]), l, m) + 
                query((p << 1) + 2, m + 1, e, updateAccu(accu, layer[p]), m + 1, r);
        }
    }
};


struct PrefixSum {
    vector<ll> prefixSums;

    PrefixSum(vector<int>& arr): prefixSums(arr.size()) {
        build(arr);
    }

    void build(vector<int>& arr) {
        ll sum = 0;
        for (int i = 0; i < arr.size(); i ++) {
            sum += arr[i];
            prefixSums[i] = sum;
        }
    }

    ll query(int l, int r) {
        ll lsum = (l == 0) ? 0 : prefixSums[l - 1];
        return prefixSums[r] - lsum;
    }

};

class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int len = nums.size();
        PrefixSum pSum(nums);
        MaxSegTree maxTree(nums);
        SpecialSegTree specialTree(nums);
        vector<int> nextGeq = getLeftMostGeq(nums);
        ll cnt = 1; // last idx is already a good array

        ll kUsed = 0;
        int ptr = len - 1;
        specialTree.updatePoint(0, 0, len - 1, -1, len - 1, 0);

        for (int i = nums.size() - 2; i >= 0; i --) {
            int nextGeqIdx = nextGeq[i] - 1, r = min(ptr, nextGeqIdx);
            
            if (nextGeqIdx > i) {
                ll toMinus = specialTree.query(0, 0, len - 1, -1, i + 1, r);
                ll toAdd = (ll) nums[i] * (r - i) - pSum.query(i + 1, r);
                kUsed += (toAdd - toMinus);
                specialTree.updateRange(0, 0, len - 1, -1, i + 1, r, nums[i]);
            }
            

            while (kUsed > k) {
                int m = maxTree.query(0, 0, len - 1, i, ptr);
                int cost = m - nums[ptr];
               
                kUsed -= cost;
                ptr --;
               
            }
            
            cnt += ptr - i + 1;
        }

        return cnt;

    }
};




int main() {
    vector<int> arr = {(int) 1e9,1,1,1,1};
    int k = 1e9;
    Solution sol;
    cout << sol.countNonDecreasingSubarrays(arr, 1e9) << endl;


}