#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// use segment tree. Every time we want to remove an element, e.g -1, we are changing subarrays (a contigous range) of that elem only
// to 0, and we want the new max subarray.
// each segment tree node store [leftMax, rightMax, subarrayMax]
// leftmax: max subarray sum that starts from the left
// rightmax: max subarray sum that starts from the right
// subarrayMax: max subarray sum in that range

// for each element, we find all ranges where the subarray consists of that elem only.
// then we update all ranges with val 0, then get the max subarray sum
// them we revert back to the orginal value.

// for constant factor optimisation, we do not need to consider removing positive elem, 
// because remove positive elems will only reduce the max subarray sum. The new best subarray cannot contain
// any of the removed elems, otherwise it will be lesser than the result we get when we do not do anything
// but if it does, we can increase the best result, by adding all the removed elems back,as they are all +ve.

// TC is O(nlogn) because we have a max of n ranges only


struct Store {
    ll sum;
    ll lmax; // max that starts from the left endpoint, or 0 (no subarray used)
    ll rmax;
    ll allmax;

    Store() {}

    Store(ll x) {
        ll res = max(0LL, x);
        sum = x, lmax = res, rmax = res, allmax = res;
    }

    Store(ll s, ll l, ll r, ll a): sum(s), lmax(l), rmax(r), allmax(a) {}

    Store operator+(const Store& other) {
        ll s = sum + other.sum;
        ll l = max(lmax, sum + other.lmax);
        ll r = max(other.rmax, other.sum + rmax);
        ll a = max({allmax, other.allmax, rmax + other.lmax}); // either in left node, right node or crosses the middle
        return Store(s, l, r, a);
    }
};


struct SegTree {
    int len;
    vector<Store> tree;

    SegTree() {}

    SegTree(vector<int>& arr): len(arr.size()), tree(4 * arr.size(), Store()) {
        build(0, 0, arr.size() - 1, arr);
    }

    void build(int p, int s, int e, vector<int>& arr) {
        if (s == e) {
            tree[p] = Store(arr[s]);
            return;
        }

        int m = (s + e) >> 1;
        build((p << 1) + 1, s, m, arr);
        build((p << 1) + 2, m + 1, e, arr);
        tree[p] = tree[(p << 1) + 1] + tree[(p << 1) + 2];
    }

    void updateRange(int p, int s, int e, int l, int r, int val) {
        if (s == e || (s == l && e == r)) {
            int len = e - s + 1;
            ll all = (ll) val * len;
            ll res = max(0LL, all);
            tree[p] = Store(all, res, res, res);
            return;
        }

        int m = (s + e) >> 1;
        if (r <= m) {
            updateRange((p << 1) + 1, s, m, l, r, val);
        } else if (l > m) {
            updateRange((p << 1) + 2, m + 1, e, l, r, val);
        } else {
            updateRange((p << 1) + 1, s, m, l, m, val);
            updateRange((p << 1) + 2, m + 1, e, m + 1, r, val);
        }
        tree[p] = tree[(p << 1) + 1] + tree[(p << 1) + 2];
    }

    ll getMaxSubarraySum() {
        return tree[0].allmax;
    }
};

class Solution {
public:

    
    long long maxSubarraySum(vector<int>& nums) {
        bool allneg = accumulate(nums.begin(), nums.end(), true, [] (bool accu, int x) {return accu && (x < 0);});
        if (allneg) {
            return accumulate(nums.begin(), nums.end(), -1e9, [] (int accu, int x) {return max(accu, x);});
        }

        unordered_map<int, vector<tuple<int, int>>> store;
        int l = 0;
        int r = 0;
        int elem = nums[0];
        for (int i = 1; i < nums.size(); i ++) {
            if (nums[i] != elem) {
                store[elem].push_back({l, r});
                l = i;
                r = i;
                elem = nums[i];
            } else {
                r ++;
            }
        }
        store[elem].push_back({l, r}); // the final one

        SegTree st(nums);
        ll best = st.getMaxSubarraySum();
        for (auto it = store.begin(); it != store.end(); it ++) {
            if (it->first >= 0) continue;

            vector<tuple<int, int>> ranges = it->second;
            for (tuple<int, int>& r : ranges) {
                st.updateRange(0, 0, st.len - 1, get<0>(r), get<1>(r), 0);
            }

            ll res = st.getMaxSubarraySum();
            best = max(best, res);

             for (tuple<int, int>& r : ranges) {
                st.updateRange(0, 0, st.len - 1, get<0>(r), get<1>(r), it->first);
            }
            
        }

        return best;
    }
};

void test1() {
    vector<int> arr = {-3,2,-2,-1,3,-2,3};
    SegTree st(arr);

    cout << st.getMaxSubarraySum() << endl;
    
    st.updateRange(0, 0, st.len - 1, 2, 2, 0);
    st.updateRange(0, 0, st.len - 1, 5, 5, 0);
    cout << st.getMaxSubarraySum() << endl;

    st.updateRange(0, 0, st.len - 1, 2, 2, -2);
    st.updateRange(0, 0, st.len - 1, 5, 5, -2);
    st.updateRange(0, 0, st.len - 1, 4, 4, 0);
    st.updateRange(0, 0, st.len - 1, 6, 6, 0);
    cout << st.getMaxSubarraySum() << endl;
}

int main() {
    vector<int> arr = {-2,-2,-2};
    Solution sol;

    cout << sol.maxSubarraySum(arr) << endl;

}

