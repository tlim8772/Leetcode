#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// order statistics on (num, coubt of nums in the subarray). There seems to be O(n^2) of such elems, but actually only 
// O(n) of such pairs
// we can use a segment tree to delete, add and get TopK (well actually x) sum in O(logn)

struct Pair {
    ll val;
    int cnt;

    Pair(): val(0), cnt(0) {}
        
    Pair(ll v, int c): val(v), cnt(c) {}

    Pair operator+(const Pair& p) {
        return Pair(val + p.val, cnt + p.cnt);
    }
};

struct SegTree {
    vector<Pair> tree;
    int n;

    SegTree() {}

    SegTree(int n): tree(4 * n), n(n) {}

    void del(int p, int s, int e, int idx) {
        if (s == e) {
            tree[p].cnt = 0;
            tree[p].val = 0;
            return;
        }

        int m = (s + e) >> 1;
        if (idx <= m) {
            del((p << 1) + 1, s, m, idx);
        } else if (idx > m) {
            del ((p << 1) + 2, m + 1, e, idx);
        }
        tree[p] = tree[(p << 1) + 1] + tree[(p << 1) + 2];
    }

    void add(int p, int s, int e, int idx, ll sum) {
        if (s == e) {
            tree[p] = Pair(sum, 1);
            return;
        }

        int m = (s + e) >> 1;
        if (idx <= m) {
            add((p << 1) + 1, s, m, idx, sum);
        } else {
            add((p << 1) + 2, m + 1, e, idx, sum);
        }
        tree[p] = tree[(p << 1) + 1] + tree[(p << 1) + 2];
    }

    ll getTopKSum(int p, int s, int e, int k) {
        if (k == 0 || tree[p].cnt == 0) return 0;
        else if (s == e) return tree[p].val;

        int m = (s + e) >> 1;
        int rcnt = tree[(p << 1) + 2].cnt;
        if (k <= rcnt) return getTopKSum((p << 1) + 2, m + 1, e, k);
        else return tree[(p << 1) + 2].val + getTopKSum((p << 1) + 1, s, m, k - rcnt);
    }
};

class Solution {
public:
    unordered_map<int, unordered_map<int, int>> map;
    SegTree st;

    void process(vector<int>& arr) {
        vector<Pair> store;
        unordered_map<int, int> freq;
        for (int i = 0; i < arr.size(); i ++) {
            store.emplace_back(arr[i], freq[arr[i]] + 1);
            freq[arr[i]] ++;
        }

        sort(store.begin(), store.end(), [](Pair& p0, Pair& p1) {return p0.cnt < p1.cnt || (p0.cnt == p1.cnt && p0.val < p1.val);});
        for (int i = 0; i < store.size(); i ++) {
            Pair& p = store[i];
            map[p.val][p.cnt] = i;
        }

        /*for (Pair& p : store) {
            cout << p.val << " " << p.cnt << endl;
        }*/

        st = SegTree(store.size());
    }

    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        vector<long long> out;

        process(nums);

        unordered_map<int, int> freq;
        for (int i = 0; i < k; i ++) {
            freq[nums[i]] ++;
        }

        for (const auto& [key, value] : freq) {
            st.add(0, 0, st.n - 1, map[key][value], (ll) key * value);
        }

        out.push_back(st.getTopKSum(0, 0, st.n - 1, x));

        for (int i = 1; i <= nums.size() - k; i ++) {
            int prevCnt = freq[nums[i - 1]];
            freq[nums[i - 1]] --;
            int prevIdx = map[nums[i - 1]][prevCnt];
            st.del(0, 0, st.n - 1, prevIdx);

            if (prevCnt > 1) {
                st.add(0, 0, st.n - 1, map[nums[i - 1]][prevCnt - 1], (ll) nums[i - 1] * (prevCnt - 1));
            }

            int nextCnt = freq[nums[i + k - 1]];
            freq[nums[i + k -1]] ++;
            if (nextCnt > 0) {
                st.del(0, 0, st.n - 1, map[nums[i + k - 1]][nextCnt]);
            }

            st.add(0, 0, st.n - 1, map[nums[i + k - 1]][nextCnt + 1], (ll) nums[i + k - 1] * (nextCnt + 1));
            //cout << nums[i + k - 1] * (nextCnt + 1) << endl;

            out.push_back(st.getTopKSum(0, 0, st.n - 1, x));
        }

        return out;

    }
};

int main() {
    Solution sol;
    vector<int> nums = {3,8,7,8,7,5};
    int k = 2;
    int x = 2;
    
    vector<ll> ans = sol.findXSum(nums, k, x);
    for (ll x : ans) cout << x << " ";
    cout << endl;

}