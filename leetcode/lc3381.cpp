#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// we have (n % k) of size (n / k) arrays
// i.e for k = 5, n = 15
// for i = 0 we have arr = [0,4][5,9][10,14]
// i = 1 we have [1,5][6,10]
// i = 2 we have [2,6][7,11]
// and so on. The best result is the maximum subarray of 1 of these subarray

class Solution {
public:

    vector<ll> construct(vector<ll>& prefix, int s, int k) {
        vector<ll> ans;
        while (s + k - 1 < prefix.size()) {
            int e = s + k - 1;
            ll sum = prefix[e] - ((s == 0) ? 0 : prefix[s - 1]);
            
            ans.push_back(sum);
            s += k;
        }
        return ans;
    } 

    ll maxSubarraySum(vector<ll>& arr) {
        vector<ll> dp(arr.size(), 0);
        
        dp[arr.size() - 1] = arr[arr.size() - 1];
        for (int i = arr.size() - 2; i >= 0; i --) {
            dp[i] = max(arr[i], arr[i] + dp[i + 1]);
        }

        

        return accumulate(dp.begin(), dp.end(), -1e18, [] (ll accu, ll res) {return max(accu, res);});
    }

    ll maxSubarraySum(vector<int>& nums, int k) {
        ll ans = -1e18;
        vector<ll> prefix(nums.size(), 0);
        prefix[0] = nums[0];
        for (int i = 1; i < nums.size(); i ++) {
            prefix[i] = nums[i] + prefix[i - 1];
        }

       
        
        
        for (int s = 0; s < k; s ++) {
            vector<ll> arr = construct(prefix, s, k);
            if (arr.empty()) continue;
            
            
            ll best = maxSubarraySum(arr);
            
            ans = max(ans, best);
        }
        return ans;
    }

    template <typename T>
    void print(vector<T> arr) {
        for (T t : arr) cout << t << " ";
        cout << endl;
    }
};

int main() {
    vector<int> nums = {-1,-2,-3,-4,-5};
    int k = 4;
    Solution sol;
    ll ans = sol.maxSubarraySum(nums, k);
    cout << ans;
}