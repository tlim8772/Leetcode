#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1e9 + 7;


// dp, but need to optimise
// use sliding window, because |max elem - min elem| is non decreasing from [i,i], [i,i+1], [i,i+2] ...
// using segtree to get range min, max, sum in O(logn)
// so suppose for index i + 1, we end at index j (i.e for [i + 1, j + 1], diff is > k)
// we don't have to check for j + 1 onwards
// so we just check for j, j - 1, j - 2 ...

// sum: number of ways to partition array[i, len - 1] into contigous subarrays such that diff <= k 

struct Res {
    int mi = 1e9 + 1;
    int ma = 0;
    int sum = 0;

    static Res merge(Res r1, Res r2) {
        ll temp = (ll) r1.sum + r2.sum;
        temp %= MOD;
        return {min(r1.mi, r2.mi), max(r1.ma, r2.ma), (int) temp};
    }
};

struct SegTree {
    int len;
    vector<Res> tree;

    SegTree(int len): len(len), tree(4 * len, Res()) {}

    void insert(int p, int s, int e, int i, Res res) {
        if (s == e) {
            tree[p] = res;
            return;
        }

        int m = (s + e) >> 1;
        if (i <= m) {
            insert((p << 1) + 1, s, m, i, res);
        } else {
            insert((p << 1) + 2, m + 1, e, i, res);
        }
        tree[p] = Res::merge(tree[(p << 1) + 1], tree[(p << 1) + 2]);
    }

    Res query(int p, int s, int e, int l, int r) {
        if (s == e || (s == l && e == r)) {
            return tree[p];
        }

        int m = (s + e) >> 1;
        if (r <= m) {
            return query((p << 1) + 1, s, m, l, r);
        } else if (l > m) {
            return query((p << 1) + 2, m + 1, e, l, r);
        } else {
            Res left = query((p << 1) + 1, s, m, l, m);
            Res right = query((p << 1) + 2, m + 1, e, m + 1, r);
            Res ans = Res::merge(left, right);
            return ans;
        }
    }
};

class Solution {
public:
    int countPartitions(vector<int>& nums, int k) {
        SegTree st(nums.size());
        int last = nums.size() - 1;

        for (int i = nums.size() - 1; i >= 0; i--) {
            st.insert(0, 0, st.len - 1, i, {nums[i], nums[i], 0});

        
            while (last >= i) {
                Res res = st.query(0, 0, st.len - 1, i, last);
                if (res.ma - res.mi > k) {
                    last--;
                } else {
                    break;
                }
            }
            // last is now at the rightmost index we can go from index i

            int sum = 0;
            if (last == nums.size() - 1) {
                sum++;
            }
            
            int ans = st.query(0, 0, st.len - 1, i + 1, min(last + 1, (int) nums.size() -1)).sum;
            sum += ans;
            // cout << i << " " << sum << endl;

            st.insert(0, 0, st.len - 1, i, {nums[i], nums[i], sum});
        }

        int ans = st.query(0, 0, st.len - 1, 0, 0).sum;
        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> arr = {9,4,1,3,7};
    int k = 4;

    cout << sol.countPartitions(arr, k) << endl;
}