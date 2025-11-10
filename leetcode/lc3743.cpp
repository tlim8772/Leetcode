#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*
score of elem = (max elem - min elem)

there exist a optimal solution which cuts at either the left or right of the smallest elem in nums.
this is because the maximum elem is either to the left or the right. suppose it is to the right, then 
any elems to the right of the smallest elem can be discarded (i.e given to the partition to the left).
adding more elems to a partition can only increase its score. this means we can break the circular array into 
a linear array.

2 cases, break on the right of the smallest elem, or on the left

let dp(i, k) = maximum sum of score from partitioning nums[i:] into <= k subarrays.
some properties:
dp(i, k) >= dp(i, k - 1)
dp(i, k) >= dp(i + 1, k)
suppose we have solve dp(i, k - 1) for all i in [0, n - 1].
for dp(i, k) if for the 1st partition, the max, min elems are index at m,n > i, then the score is dp(i + 1, k).
so a better score can only be achieved using nums[i]

case 1: nums[i] = nums[i + 1]. then no need to consider anything, if nums[i] is the max or min, just replace it
with nums[i + 1] and the score is 'inside' dp(i + 1, k)
even if nums[i] is it own partition, the score of [nums[i]] is 0, then the score is inside dp(i + 1, k - 1)

case 2: nums[i] > nums[i + 1]
then find smallest j s.t nums[j] >= nums[i].
the new scores to consider are 
nums[i] - nums[i + 1] + dp(i + 2, k - 1)
nums[i] - nums[i + 2] + dp(i + 3, k - 1)
...
nums[i] - nums[j - 1] + dp(j, k - 1)
we use a seg tree on  -nums[i] + dp(i, k - 1) to compute the max O(logn)

case 3: nums[i] < nums[i + 1]
then find smallest j s.t nums[j] <= nums[i]
the new scores to consider are
nums[i + 1] - nums[i] + dp(i + 2, k - 1)
...
nums[j - 1] - nums[i] + dp(j, k - 1)
use seg tree on nums[i] + dp(i, kk - 1)
*/

ll NEG = -1e12;

struct SegTree {
    int n = 0;
    vector<ll> tree;

    SegTree(int n): n(n), tree(4 * n, 0) {}

    void build(vector<ll>& nums, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = n - 1;

        if (s == e) {
            tree[p] = nums[s];
            return;
        }

        int m = (s + e) >> 1;
        build(nums, (p << 1) + 1, s, m);
        build(nums, (p << 1) + 2, m + 1, e);
        tree[p] = max(tree[(p << 1) + 1], tree[(p << 1) + 2]);
    }

    void point_update(int i, ll v, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = n - 1;

        if (s == e) {
            tree[p] = v;
            return;
        }

        int m = (s + e) >> 1;
        if (i <= m) {
            point_update(i, v, (p << 1) + 1, s, m);
        } else {
            point_update(i, v, (p << 1) + 2, m + 1, e);
        }
        tree[p] = max(tree[(p << 1) + 1], tree[(p << 1) + 2]);
    }

    ll range_query(int l, int r, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = n - 1;

        if (s == e || (s == l && e == r)) {
            return tree[p];
        }

        int m = (s + e) >> 1;
        if (r <= m) {
            return range_query(l, r, (p << 1) + 1, s, m);
        } else if (l > m) {
            return range_query(l, r, (p << 1) + 2, m + 1, e);
        } else {
            return max(range_query(l, m, (p << 1) + 1, s, m), range_query(m + 1, r, (p << 1) + 2, m + 1, e));
        }
    }
};

struct SegTree2 {
    int n;
    vector<pair<int,int>> tree;

    SegTree2(int n): n(n), tree(4 * n, {1e9 + 1, 0}) {}

    SegTree2(vector<int>& nums): n(nums.size()), tree(4 * n, {1e9 + 1, 0}) {
        build(0, 0, n - 1, nums);
    }

    void build(int p, int s, int e, vector<int>& nums) {
        if (s == e) {
            tree[p] = {nums[s], nums[s]};
            return;
        }

        int m = (s + e) >> 1;
        build((p << 1) + 1, s, m, nums);
        build((p << 1) + 2, m + 1, e, nums);
        auto& [lmi, lma] = tree[(p << 1) + 1];
        auto& [rmi, rma] = tree[(p << 1) + 2];
        tree[p] = pair<int,int>{min(lmi, lma), max(lma, rma)};
    }

    void point_update(int i, int v, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = n - 1;

        if (s == e) {
            tree[p] = {v, v};
            return;
        }

        int m = (s + e) >> 1;
        if (i <= m) {
            point_update(i, v, (p << 1) + 1, s, m);
        } else {
            point_update(i, v, (p << 1) + 2, m + 1, e);
        }
        
        pair<int,int> &l = tree[(p << 1) + 1], &r = tree[(p << 1) + 2];
        tree[p].first = min(l.first, r.first);
        tree[p].second = max(l.second, r.second);
    }

    pair<int,int> earliest_geq(int i, int v, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = n - 1;
        
        auto& [mi, ma] = tree[p];
        if (s == e) {
            return (ma >= v) ? pair<int,int>{s, ma} : pair<int,int>{n, -1};
        }

        int m = (s + e) >> 1;
        if (i > m) {
            return earliest_geq(i, v, (p << 1) + 2, m + 1, e);
        }

        if (i <= s) {
            if (ma < v) {
                return pair<int,int>{n, -1};
            } 

            auto [lmi, lma] = tree[(p << 1) + 1];
            if (lma >= v) {
                return earliest_geq(i, v, (p << 1) + 1, s, m);
            } else {
                return earliest_geq(i, v, (p << 1) + 2, m + 1, e);
            }
        } 

        auto res = earliest_geq(i, v, (p << 1) + 1, s, m);
        if (res.second == -1) {
            return earliest_geq(i, v, (p << 1) + 2, m + 1, e);
        } else {
            return res;
        }
    }

    pair<int,int> earliest_leq(int i, int v, int p = 0, int s = 0, int e = -1) {
        if (e == -1) e = n - 1;

        auto& [mi, ma] = tree[p];
        if (s == e) {
            return (mi <= v) ? pair<int,int>{s, mi} : pair<int,int>{n, -1};
        }

        int m = (s + e) >> 1;
        if (i > m) {
            return earliest_leq(i, v, (p << 1) + 2, m + 1, e);
        }

        if (i <= s) {
            if (mi > v) {
                return pair<int,int>{n, -1};
            }

            auto [lmi, lma] = tree[(p << 1) + 1];
            if (lmi <= v) {
                return earliest_leq(i, v, (p << 1) + 1, s, m);
            } else {
                return earliest_leq(i, v, (p << 1) + 2, m + 1, e);
            }
        }

        auto res = earliest_leq(i, v, (p << 1) + 1, s, m);
        if (res.second == -1) {
            return earliest_leq(i, v, (p << 1) + 2, m + 1, e);
        } else {
            return res;
        }
    }
};

ll dp(vector<int>& nums, int k) {
    int N = nums.size();
    vector<ll> store(N * k, 0);
    auto to_pos = [k] (int i, int j) { return i * k + j; };

    SegTree2 st2(nums);
    
    SegTree stneg(N), stpos(N);
    

    // do k == 0 (i.e 0 + 1 = 1 max # of partitions)
    int ma = nums.back(), mi = nums.back();
    for (int i = N - 1; i > -1; i--) {
        ma = max(ma, nums[i]), mi = min(mi, nums[i]);
        store[to_pos(i, 0)] = ma - mi;

        ll res = (i == N - 1) ? 0 : store[to_pos(i + 1, 0)];
        stneg.point_update(i, -nums[i] + res);
        stpos.point_update(i, nums[i] + res);
    }

    for (int j = 1; j < k; j++) {
        for (int i = N - 1; i > -1; i--) {
            ll best = max(store[to_pos(i, j - 1)], (i < N - 1) ? store[to_pos(i + 1, j)] : 0);

            if (i == N - 1) continue;
            
            if (nums[i] < nums[i + 1]) {
                int limit = st2.earliest_leq(i + 1, nums[i]).first;
                ll res = -nums[i] + stpos.range_query(i + 1, limit - 1);
                best = max(best, res);
            } else if (nums[i] > nums[i + 1]) {
                int limit = st2.earliest_geq(i + 1, nums[i]).first;
                ll res = nums[i] + stneg.range_query(i + 1, limit - 1);
                best = max(best, res);
            }

            store[to_pos(i, j)] = best;
        }

        /*
        constant factor optimisation here.
        instead of O(nlogn) of inserting each element individually,
        use the O(n) build on the array of new values
        */
        vector<ll> temp(N, 0);
        for (int i = N - 1; i > -1; i--) {
            temp[i] = -nums[i] + ((i == N - 1) ? 0 : store[to_pos(i + 1, j)]);
        }
        stneg.build(temp);

        for (int i = N - 1; i > -1; i--) {
            temp[i] = nums[i] + ((i == N - 1) ? 0 : store[to_pos(i + 1, j)]);
        }
        stpos.build(temp);
    }

    ll ans = store[to_pos(0, k - 1)];

    return ans;
}

ll solve(vector<int>& nums, int k) {
    auto it = min_element(nums.begin(), nums.end());

    vector<int> cut_left, cut_right;
    cut_left.insert(cut_left.end(), it, nums.end());
    cut_left.insert(cut_left.end(), nums.begin(), it);

    cut_right.insert(cut_right.end(), it + 1, nums.end());
    cut_right.insert(cut_right.end(), nums.begin(), it + 1);

    /*for (int x : cut_left) cout << x << " ";
    cout << endl;

    for (int x : cut_right) cout << x << " ";
    cout << endl;*/

    ll ans1 = dp(cut_left, k), ans2 = dp(cut_right, k);
    return max(ans1, ans2);
}

class Solution {
public:
    long long maximumScore(vector<int>& nums, int k) {
        return solve(nums, k);
    }
};


void test1() {
    SegTree st(10);
    for (int i = 0; i < 10; i++) {
        st.point_update(i, i);
    }

    cout << st.range_query(3, 7) << endl;
    st.point_update(4, 100);
    cout << st.range_query(2, 8) << endl;
    st.point_update(4, 1);
    cout << st.range_query(4, 4) << endl;
}

void test2() {
    
    vector<int> nums = {1,3,10,2,5,6,11,3,4,0};
    SegTree2 st2(nums);

    cout << st2.earliest_geq(3, 10).first << endl;
    st2.point_update(6, 0);
    cout << st2.earliest_geq(3, 10).first << endl;
    st2.point_update(6, 11);

    cout << st2.earliest_leq(4, 4).first << endl;
    st2.point_update(5, 0);
    cout << st2.earliest_leq(4, 4).first << endl;

}

int main() {
    //test1();
    //test2();

    vector<int> nums = {1,2,3,3};
    int k = 4;
    cout << solve(nums, k) << endl;
}