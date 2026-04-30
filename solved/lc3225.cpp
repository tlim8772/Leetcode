#include <bits/stdc++.h>
#include <ranges>
using namespace std;
using ll = long long;
// challenging dp.
// dp(i, a, b) mean max score from submatrix mat[0:i + 1] and
// where the i + 1 col is of height a and the i + 2 col is of height b.
// also assume the covered white boxes due to colored cols i + 1, i + 2 already summed.
// (which means we have to minus some).
// for col i, we can color 0, 1, 2, 3 ... n, but then T.C is O(n^4).

// do some optimisation to make it O(n^3logn).
// key insight is to notice the similarity between dp(i, a, b) and dp(i, a, b + 1).
// hard to explain.
// we need a range update (+) range query (max) segment tree.

// explanation.
// consider dp(i, a, b)
// at col i, we can build a height of up to len N, N = grid.size().
// suppose a < b
// the score for dp(i, a, b) is 
// max (
//  dp(i - 1, 0, a),
//  grid[0][i - 1] - grid[0][i] + dp(i - 1, 1, a)
//  ...
//  grid[0][i - 1] - grid[0][i] + grid[1][i - 1] - grid[1][i] ... + grid[a - 1][i - 1] - grid[a - 1][i] + dp(i - 1, a, a)
//  ... (and so on, must consider the white boxes covered, not covered by b as height increases)
// )

// when moving do dp(i, a, b + 1)
// height b, b + 1 ... N is affected, the effect is that previous res - grid[b][i + 1]
// because the white boxes was previously not covered by the i + 2 colored column, now it is covered,
// so by the definition of dp(i, a, b) must minus grid[b][i + 1]

// then you can see what happens for b + 2, b + 3 ...
// use range update, range query segment tree for this.

// what if a > b, it is simpler, because then we do not need to make the adjustment defined above.
// until b > a, then we need to do the adjustment.

// range_update add, range_query max
struct SegTree {
    int len;
    vector<ll> tree;
    vector<ll> accu_tree;

    inline int left(int p) { return (p << 1) + 1; }

    inline int right(int p) { return (p << 1) + 2; }

    inline int mid(int s, int e) { return (s + e) >> 1; }

    SegTree(int len): len(len), tree(4 * len, 0), accu_tree(4 * len, 0) {}

    SegTree(const vector<ll>& arr): len(arr.size()), tree(4 * len, 0), accu_tree(4 * len, 0) {
        build(arr);
    }

    void build(const vector<ll>& arr, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = len - 1;
        if (s == e) {
            tree[p] = arr[s];
            accu_tree[p] = 0;
            return;
        }
        int m = mid(s, e);
        build(arr, left(p), s, m);
        build(arr, right(p), m + 1, e);
        tree[p] = max(tree[left(p)], tree[right(p)]);
        accu_tree[p] = 0;
    }

    ll range_update(int l, int r, ll val, int p = 0, int s = 0, int e = -1, ll acc = 0) {
        if (e == -1) e = len - 1;
        if (s == l && e == r) {
            tree[p] += val;
            accu_tree[p] += val;
            return tree[p] + acc;
        }
        int m = mid(s, e);
        ll new_acc = acc + accu_tree[p];
        ll lres = tree[left(p)] + new_acc, rres = tree[right(p)] + new_acc;
        if (r <= m) {
            lres = range_update(l, r, val, left(p), s, m, new_acc);
        } else if (l > m) {
            rres = range_update(l, r, val, right(p), m + 1, e, new_acc);
        } else {
            lres = range_update(l, m, val, left(p), s, m, new_acc);
            rres = range_update(m + 1, r, val, right(p), m + 1, e, new_acc);
        }
        ll ans = max(lres, rres);
        tree[p] = ans - acc;
        return ans;
    }

    ll range_query(int l, int r, int p = 0, int s = 0, int e = -1, ll acc = 0) {
        if (e == -1) e = len - 1;
        if (s == l && e == r) return tree[p] + acc;
        int m = mid(s, e);
        ll new_acc = acc + accu_tree[p];
        if (r <= m) {
            return range_query(l, r, left(p), s, m, new_acc);
        } else if (l > m) {
            return range_query(l, r, right(p), m + 1, e, new_acc);
        } else {
            ll lres = range_query(l, m, left(p), s, m, new_acc);
            ll rres = range_query(m + 1, r, right(p), m + 1, e, new_acc);
            return max(lres, rres);
        }
    }
};

void test_seg_tree() {
    vector<ll> data = {1, 5, 2, 8, 3};
    SegTree st(data);

    // Test 1: Initial Max
    assert(st.range_query(0, 4) == 8);
    
    // Test 2: Range Update and Query
    st.range_update(0, 2, 10); // [11, 15, 12, 8, 3]
    assert(st.range_query(0, 4) == 15);
    assert(st.range_query(3, 4) == 8);
    assert(st.range_query(1, 1) == 15);

    // Test 3: Overlapping updates
    vector<ll> zeros(5, 0);
    SegTree st2(zeros);
    st2.range_update(0, 2, 5);  // [5, 5, 5, 0, 0]
    st2.range_update(2, 4, 10); // [5, 5, 15, 10, 10]
    assert(st2.range_query(0, 4) == 15);
    assert(st2.range_query(0, 1) == 5);
    assert(st2.range_query(2, 2) == 15);

    cout << "All tests passed!" << endl;
}

vector<vector<vector<ll>>> store = vector(100, vector(101, vector<ll>(101, 0)));

ll dp(const vector<vector<int>>& grid) {
    int N = grid.size();
    SegTree st(N + 1);

    // do col i = 0 first.
    for (int a = 0; a <= N; a++) {
        for (int b = 0; b <= N; b++) {
            ll sum = 0;
            ll best = 0; // when no height, then the result is 0
            for (int h = 1; h <= N; h++) {
                if (h <= a) sum -= grid[h - 1][0];
                if (h > max(a, b)) sum += (0 < N - 1) ? grid[h - 1][1] : 0; 
                best = max(best, sum);
            }
            store[0][a][b] = best;
        }
    }

    /*for (int a = 0; a <= N; a++) {
        for (int b = 0; b <= N; b++) {
            cout << store[0][a][b] << ' ';
        }
        cout << endl;
    }*/

    for (auto [i, a] : views::cartesian_product(views::iota(1, N), views::iota(0, N + 1))) {
        // dp(i, a, 0) first.
        vector<ll> res(N + 1, 0);
        ll sum = 0;
        res[0] = store[i - 1][0][a];
        for (int h = 1; h <= N; h++) {
            sum += grid[h - 1][i - 1];
            if (h <= a) sum -= grid[h - 1][i];
            if (h > a) sum += (i < N - 1) ? grid[h - 1][i + 1] : 0;
            res[h] = sum + store[i - 1][h][a];
        }
        store[i][a][0] = ranges::max(res);

        // then do dp(i, a, 1), dp(i, a, 2) ... dp(i, a, N)
        st.build(res);
        for (int b = 1; b < N + 1; b++) {
            if (b > a && i < N - 1) {
                st.range_update(b, N, -grid[b - 1][i + 1]);
            }
            store[i][a][b] = st.range_query(0, N);
        }
    }

    return store[N - 1][0][0];
}

class Solution {
public:
    long long maximumScore(vector<vector<int>>& grid) {
        return dp(grid);
    }
};

int main() {
    //test_seg_tree();
    Solution sol;

    vector<vector<int>> grid = {{10,9,0,0,15},{7,1,0,8,0},{5,20,0,11,0},{0,0,0,1,2},{8,12,1,10,3}};
    ll ans = sol.maximumScore(grid);
    cout << ans << endl;
}