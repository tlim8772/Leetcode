#include <bits/stdc++.h>
using namespace std;

// given a range [l, r] want to know if it can be made non decreasing using cyclic left/right shift.
// use segment tree.
// find the index of the min element m.
// check if [l, m - 1] and [m, r] is sorted.
// check if arr[r] <= arr[l].

// given len, iterate though all its divisors, and test.

template <typename T, typename R, typename Transformer, typename Reducer>
struct SegTree {
    int len;
    vector<R> tree;
    Transformer trans;
    Reducer reduce;

    int mid(int s, int e) const {
        return (s + e) >> 1;
    }

    int left(int p) const {
        return (p << 1) + 1;
    }

    int right(int p) const {
        return (p << 1) + 2;
    }

    SegTree(int len): len(len), tree(4 * len, R()) {}

    SegTree(const vector<T>& arr): len(arr.size()), tree(4 * len, R()) {
        build(arr);
    }

    void build(const vector<T>& arr, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;

        if (s == e) {
            tree[p] = trans(arr[s]);
            return;
        }

        int m = mid(s, e);
        build(arr, left(p), s, m);
        build(arr, right(p), m + 1, e);
        tree[p] = reduce(tree[left(p)], tree[right(p)]);
    }

    R query(int l, int r, int p = 0, int s = 0, int e = -1) const {
        if (e == -1) e = len - 1;
        if (s == l && e == r) {
            return tree[p];
        }
        
        int m = mid(s, e);
        if (r <= m) {
            return query(l, r, left(p), s, m);
        } else if (l > m) {
            return query(l, r, right(p), m + 1, e);
        } else {
            R lres = query(l, m, left(p), s, m);
            R rres = query(m + 1, r, right(p), m + 1, e);
            return reduce(lres, rres);
        }
    }
};

struct SortR {
    bool sorted;
    int mi;
    int ma;
};

struct SortTrans {
    SortR operator()(int x) const {
        return SortR{true, x, x};
    }
};

struct SortRed {
    SortR operator()(const SortR& l, const SortR& r) const {
        if (!l.sorted || !r.sorted || l.ma > r.mi) {
            return {false, -1, -1};
        } 
        return {true, l.mi, r.ma};
    }
};


// pair<int, int> is {idx, val}
struct MinIdxTrans {
    pair<int, int> operator()(const pair<int, int>& p) const {
        return p;
    }
};

struct MinIdxRed {
    pair<int, int> operator()(const pair<int, int>& l, const pair<int, int>& r) const {
        if (l.second < r.second) {
            return l;
        } else if (r.second < l.second) {
            return r;
        } else if (l.first <= r.first) {
            return l;
        } else {
            return r;
        }
    }
};

// checks whether range [l, r] is sorted in non decreasing manner
using SortST = SegTree<int, SortR, SortTrans, SortRed>;

// get the leftmost idx and val of the minimum value in range [l, r]
using MinIdxST = SegTree<pair<int, int>, pair<int, int>, MinIdxTrans, MinIdxRed>;

// returns {is cyclic sortable, min elem of range, max elem of range}
tuple<bool, int, int> is_cyclic_sortable(int l, int r, 
    const vector<int>& nums, const SortST& sort_st, const MinIdxST minidx_st) 
{
    if (l == r) {
        return {true, nums[l], nums[l]};
    } 
    
    else if (r - l + 1 == 2) {
        int mi = min(nums[l], nums[l + 1]);
        int ma = max(nums[l], nums[l + 1]);
        return {true, mi, ma};
    }


    auto [idx, val] = minidx_st.query(l, r);
    if (idx == l) {
        SortR res = sort_st.query(l, r);
        if (res.sorted) {
            return {true, val, nums[r]};
        } else {
            return {false, -1, -1};
        }
    }

    SortR lres = sort_st.query(l, idx - 1);
    SortR rres = sort_st.query(idx, r);

    if (!lres.sorted || !rres.sorted || nums[r] > nums[l]) {
        return {false, -1, -1};
    }

    return {true, val, nums[idx - 1]};
}

bool can(int k, vector<int>& nums, SortST& sort_st, MinIdxST& minidx_st) {
    int prev_ma = -1;
    for (int i = 0; i < nums.size(); i += k) {
        auto [b, mi, ma] = is_cyclic_sortable(i, i + k - 1, nums, sort_st, minidx_st);
        if (!b) {
            return false;
        }

        if (i == 0) {
            prev_ma = ma;
        } else {
            if (prev_ma > mi) {
                return false;
            }
            prev_ma = ma;
        }
    }
    return true;
}


class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        vector<pair<int,int>> temp;
        for (int i = 0; i < nums.size(); i++) {
            temp.emplace_back(i, nums[i]);
        }

        int len = nums.size();
        int lim = (int) floor(sqrt(len));
        int cnt = 0;
        SortST sort_st(nums);

        MinIdxST minidx_st(temp);
        
        for (int i = 1; i <= lim; i++) {
            if (len % i != 0) continue;

            bool r1 = can(i, nums, sort_st, minidx_st);
            bool r2 = (i == len / i) ? false : can(len / i, nums, sort_st, minidx_st);
            
            if (r1) cnt += i;
            if (r2) cnt += len / i;
        }

        return cnt;
    }
};

void test1() {
    struct Trans {
        int operator()(int x) const { return x; }
    };

    struct Red {
        int operator()(int x, int y) const { return x + y; }
    };

    vector<int> arr = {1,3,2,4,5,6};

    SegTree<int, int, Trans, Red> st(arr);

    assert(st.query(2, 4) == 11);
    assert(st.query(1, 1) == 3);
    assert(st.query(3, 5) == 15);
}

void test2() {
    SortST st({1,2,3,2,4,5,6});
    assert(st.query(0, 2).sorted == true);
    assert(st.query(1, 3).sorted == false);
    assert(st.query(4, 6).sorted == true);
}

int main() {
    //test1();
    //test2();

    Solution sol;

    vector<int> nums = {423};
    int ans = sol.sortableIntegers(nums);
    cout << ans << endl;
}