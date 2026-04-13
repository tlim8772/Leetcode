#include <bits/stdc++.h>
using namespace std;

// use segment tree to update and get gcd of all valid elems (divisible by p) at once.
// now gcd is at least p, since all elems processed are divisible by p.
// if gcd > p, then no valid strictly smaller subsequence, as any smaller subsequence will have
// larger or equal gcd.

// now if all elems are valid and gcd = p, we need to remove 1 elem and the gcd must stil be p
// not a larger number.
// suppose removing elem 1 causes gcd to increase. This means elems S - {e1} share a common prime factor p1
// that e1 does not have.
// suppos removing e2 causes same thing. This means elems S - {e2} share a common prime factor p2
// that e2 does not have
// and p2 != p1
// and so on.
// at most 6 prime factors 2 * 3 * 5 * 7 * 11 * 13 = 300000, so we check at most 6 times.
// otherwise each number will be very large if the elems we check always fail.

template <typename T, typename R, typename Transform, typename Reducer>
struct SegTree {
    int len;
    Transform trans;
    Reducer red;
    vector<R> tree;

    int mid(int s, int e) {
        return (s + e) >> 1;
    }

    int left(int p) {
        return (p << 1) + 1;
    }

    int right(int p) {
        return (p << 1) + 2;
    }

    SegTree(const vector<T> arr): len(arr.size()), tree(4 * len, R()) {
        build(arr);
    }

    SegTree(const vector<T> arr, Transform t, Reducer r): len(arr.size()), trans(t), red(r), tree(4 * len, R()) 
    {
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
        tree[p] = red(tree[left(p)], tree[right(p)]);
    }

    void update(T t, int i, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;
        if (s == e) {
            tree[p] = trans(t);
            return;
        }

        int m = mid(s, e);
        if (i <= m) {
            update(t, i, left(p), s, m);
        } else {
            update(t, i, right(p), m + 1, e);
        }
        tree[p] = red(tree[left(p)], tree[right(p)]);
    }

    R query(int l, int r, int p = 0, int s = 0, int e = -1) {
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
            return red(lres, rres);
        }
    }
};

class Solution {
public:
    int countGoodSubseq(vector<int>& nums, int p, vector<vector<int>>& queries) {
        auto trans = [p] (int x) { 
            return pair<int, int>{x % p == 0, (x % p == 0) ? x : 0}; 
        };
        
        auto red = [] (const pair<int,int>& p1, const pair<int,int>& p2) {
            return pair<int,int>{p1.first + p2.first, gcd(p1.second, p2.second)};
        };
        
        using ST = SegTree<int, pair<int,int>, decltype(trans), decltype(red)>;
        
        unordered_set<int> valid_idxs;
        ST st{nums, trans, red};

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] % p == 0) valid_idxs.insert(i);
        }

        int score = 0;
        for (const auto& q : queries) {
            int idx = q[0], val = q[1];
            
            if (nums[idx] % p == 0) valid_idxs.erase(idx);
            if (val % p == 0) valid_idxs.insert(idx);
            nums[idx] = val;
            st.update(val, idx);

            auto [cnt, gcd_val] = st.query(0, st.len - 1);

            if (gcd_val == 0 || gcd_val > p) continue;
            
            if (cnt < nums.size()) {
                score++;
                continue;
            }

            // at most 6 tries
            for (int v_idx : valid_idxs) {
                auto lres = (v_idx == 0) ? pair<int,int>{0, 0} : st.query(0, v_idx - 1);
                auto rres = (v_idx == nums.size() - 1) ? pair<int,int>{0, 0} : st.query(v_idx + 1, st.len - 1);
                auto res = red(lres, rres);
                if (res.second == p) {
                    score++;
                    break;
                }
            }

        }
        return score;
    }
};


void test_sum_query() {
    vector<int> data = {1, 3, 5, 7, 9, 11};
    
    // Transform: identity, Reducer: addition
    auto trans = [](int x) { return x; };
    auto red = [](int a, int b) { return a + b; };
    
    SegTree<int, int, decltype(trans), decltype(red)> st(data, trans, red);

    // Initial builds
    assert(st.query(0, 5) == 36); // 1+3+5+7+9+11
    assert(st.query(1, 3) == 15); // 3+5+7
    assert(st.query(0, 0) == 1);  // single element
    
    // Update index 1 from 3 to 10
    st.update(10, 1);
    assert(st.query(0, 5) == 43); // 1+10+5+7+9+11
    assert(st.query(1, 3) == 22); // 10+5+7
    
    cout << "Test Sum Query: PASSED" << endl;
}

void test_rmq() {
    vector<int> data = {18, 15, 20, 5, 30, 2, 10};
    
    auto trans = [](int x) { return x; };
    auto red = [](int a, int b) { return min(a, b); };
    
    SegTree<int, int, decltype(trans), decltype(red)> st(data, trans, red);

    assert(st.query(0, 6) == 2);
    assert(st.query(0, 3) == 5);
    
    // Update the '2' at index 5 to be '100'
    st.update(100, 5);
    assert(st.query(0, 6) == 5); // New minimum is 5
    
    cout << "Test RMQ: PASSED" << endl;
}

int main() {
    Solution sol;

    vector<int> nums{1,5,56,22,49,18,27,69};
    int p = 19;
    vector<vector<int>> queries{{0,9},{0,15},{6,23}};

    int ans = sol.countGoodSubseq(nums, p, queries);
    cout << ans << endl;
}