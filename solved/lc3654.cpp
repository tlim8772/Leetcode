#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// let dp(i) = best result for arr[i..len - 1]
// consider the endpoint where some numbers are left
// eg p1, p2 ... pk
// then for [p1 + 1..p2-1] the sum is divisible by k, no matter how this subarray is removed
// basically
// the optimal solution consists of removed subarrays whose sum is divisble by k
// starting at dp(0)
// if we take, just consider dp(1)
// if not, we remove, we consider all j s.t sum[0..j] is divisble by k and then return dp(j + 1)

// so when considering dp(i)
// case 1: arr[i] not removed, proceed to dp(i + 1)
// case 2: arr[i] is removed, so consider all j s.t arr[i..j] sum is divisible by k
// arr[i..j] is valid if prefix sum [0..i-1] and [0..j] have the same remainder under k

// so let say i = 5, we want to take a subarray starting at 5
// since sum[0..4] % k = 4, we can only take j, s.t sum[0..j] % k = 4
// then we take the result of dp(j + 1)

// once we find the ans for dp(i), we store it for sum[0..i - 1] % k
// if there exist an entry for sum[0..i - 1] % k, take the min

class Solution {
public:

    vector<ll> getPrefixSum(const vector<int>& nums) {
        vector<ll> res(nums.size(), 0);
        res[0] = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            res[i] = res[i - 1] + nums[i];
        }
        return res;
    }
    
    long long minArraySum(vector<int>& nums, int k) {
        const ll MAX = 1e12;
        unordered_map<int, ll> store;
        vector<ll> dpStore(nums.size(), 0);
        vector<ll> prefixSums = getPrefixSum(nums);

        // we can remove all the remaining elems
        // eg arr[i..len - 1]
        store[prefixSums.back() % k] = 0;

        for (int i = nums.size() - 1; i >= 0; i--) {
            ll take = nums[i] + ((i == nums.size() - 1) ? 0 : dpStore[i + 1]);

            int m = (i == 0) ? 0 : prefixSums[i - 1] % k;
            ll notake = (store.contains(m)) ? store[m] : MAX;

            dpStore[i] = min(take, notake);

            if (i > 0) {
                store[m] = (!store.contains(m)) ? dpStore[i] : min(dpStore[i], store[m]);
            }
        }

        return dpStore[0];


    }
};

int main() {
    vector<int> nums = {3,1,4,1,5};
    int k = 3;

    Solution sol;
    cout << sol.minArraySum(nums, k) << endl;
}