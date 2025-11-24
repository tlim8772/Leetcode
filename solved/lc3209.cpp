#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct SegTree {
    int len;
    int initAccu = ((long long) 1 << 31) - 1;
    vector<int> tree;

    SegTree(const vector<int>& arr): len(arr.size()), tree(4 * len, 0) {
        build(0, 0, len - 1, arr);
    }



    void build(int p, int s, int e, const vector<int>& arr) {
        if (s == e) {
            tree[p] = arr[s];
            return;
        }

        int m = (s + e) >> 1;
        build((p << 1) + 1, s, m, arr);
        build((p << 1) + 2, m + 1, e, arr);
        tree[p] = tree[(p << 1) + 1] & tree[(p << 1) + 2];
    }

    // initial accu value is (1 << 31) - 1
    // invariant: accu > k, because if it is <= k we would have return
    // i <= e
    // i <= s || i > s
    // returns the leftmost index l, l >= i, s.t AND[i..l] <= k
    // if cannot i.e AND[i..len - 1] > k, then it will return (len - 1, AND result)
    pair<int,int> findLeft(int p, int s, int e, int i, int k, int accu) {
        int m = (s + e) >> 1;
        if (s == e) {
            return pair{s, accu & tree[p]};
        } else if (i <= s) {
            int res = accu & tree[p];
            if (res > k) {
                return pair{e, res};
            } else {
                pair<int,int> leftAns = findLeft((p << 1) + 1, s, m, i, k, accu);
                if (leftAns.second <= k) {
                    return leftAns;
                } else {
                    return findLeft((p << 1) + 2, m + 1, e, i, k, leftAns.second);
                }
            }
        } else if (i > m) {
            return findLeft((p << 1) + 2, m + 1, e, i, k, accu);
        } else {
            pair<int,int> leftAns = findLeft((p << 1) + 1, s, m, i, k, accu);
            if (leftAns.second <= k) {
                return leftAns;
            } else {
                return findLeft((p << 1) + 2, m + 1, e, i, k, leftAns.second);
            }
        }
    }
};

class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        ll cnt = 0;
        SegTree st(nums);

        for (int i = 0; i < nums.size(); i++) {
             int l, r;

            pair<int,int> leftAns = st.findLeft(0, 0, st.len - 1, i, k, st.initAccu);
            if (leftAns.second != k) {
                // it can be AND[i..len - 1] > k
                // or cannot find l s.t AND[i..l] = k
                continue;
            }
            l = leftAns.first;
           
            pair<int,int> rightAns = st.findLeft(0, 0, st.len - 1, i, k - 1, st.initAccu);
            if (rightAns.second > k - 1) {
                r = st.len;
            } else {
                r = rightAns.first;
            }

            cnt += r - l;

        }

        return cnt;
    }
};

int main() {
    vector<int> nums = {1,1,2};
    SegTree st(nums);

    cout << st.findLeft(0, 0, st.len - 1, 2, 1, st.initAccu).first << endl;

}