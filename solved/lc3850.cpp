#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 1 <= nums[i] <= 6 and nums.size() <= 19.
// dp(top, bottom, i) where top / bottom represents the curr rational value, and i is the start index.
// somehow this can pass already.


struct tuple_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(const std::tuple<long long, long long, int>& t) const {
        uint64_t a = splitmix64(std::get<0>(t));
        uint64_t b = splitmix64(std::get<1>(t));
        uint64_t c = splitmix64(std::get<2>(t));

        // Combine hashes
        size_t h = a;
        h ^= b + 0x9e3779b97f4a7c15 + (h << 6) + (h >> 2);
        h ^= c + 0x9e3779b97f4a7c15 + (h << 6) + (h >> 2);
        return h;
    }
};

class Solution {
public:
    unordered_map<tuple<ll, ll, int>, int, tuple_hash> store;

    int dp(ll top, ll bottom, int i, const vector<int>& nums, const ll k) {
        if (i == nums.size()) {
            return (top % bottom == 0 && top / bottom == k) ? 1 : 0;
        }
        
        if (store.contains({top, bottom, i})) {
            return store[{top, bottom, i}];
        }

        int &ans = store[{top, bottom, i}];

        if (nums[i] == 1) {
            return ans = 3 * dp(top, bottom, i + 1, nums, k);
        }

        ll top1 = top * nums[i];
        ll gcd1 = gcd(top1, bottom);
        ans += dp(top1 / gcd1, bottom / gcd1, i + 1, nums, k);

        ll bottom2 = bottom * nums[i];
        ll gcd2 = gcd(top, bottom2);
        ans += dp(top / gcd2, bottom2 / gcd2, i + 1, nums, k);

        ans += dp(top, bottom, i + 1, nums, k);

        return ans;
    }
    
    int countSequences(vector<int>& nums, long long k) {
        return dp(1, 1, 0, nums, k);
    }
};

int main() {
    Solution sol;
    vector<int> nums = {4, 6, 3};
    int k = 2;

    int ans = sol.countSequences(nums, k);
    cout << ans << endl;
}