#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// simple dp.
// let dp(n1, n2, k) be max score we can get from nums1[n1:], nums2[n2:] with k + 1 pairs left.
// we can take nums1[n1] and nums2[n2] or we skip either 1 of them to simulate not taking this pair.

class Solution {
public:
    int N1, N2, K;
    vector<ll> store;
    ll INVALID = (ll) -1e16;
    ll NOT_USED = (ll) -1e18;

    int to_pos(int n1, int n2, int k) {
        return n1 * N2 * K + n2 * K + k;
    }

    ll dp(int n1, int n2, int k, const vector<int>& nums1, const vector<int>& nums2) {
        if (n1 == nums1.size() || n2 == nums2.size()) {
            if (k == -1) {
                return 0;
            } else {
                return INVALID;
            }
        } else if (k == -1) {
            return 0;
        }

        int pos = to_pos(n1, n2, k);
        ll& ans = store[pos];
        
        if (ans != NOT_USED) return ans;

        ll op1 = (ll) nums1[n1] * nums2[n2] + dp(n1 + 1, n2 + 1, k - 1, nums1, nums2);
        ll op2 = dp(n1 + 1, n2, k, nums1, nums2);
        ll op3 = dp(n1, n2 + 1, k, nums1, nums2);
        
        return ans = max({op1, op2, op3});
    }

    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
        N1 = nums1.size(), N2 = nums2.size(), K = k;
        store = vector<ll>(N1 * N2 * K, NOT_USED);
        return dp(0, 0, k - 1, nums1, nums2);
    }
};

int main() {
    Solution sol;
    vector<int> nums1 = {-2,0,5};
    vector<int> nums2 = {-3,4,-1,2};
    int k = 2;
    ll ans = sol.maxScore(nums1, nums2, k);
    cout << ans << endl;
}