#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = (ll) 1e9 + 7;

// for each elem, store the number of trees that can be formed when that elem is the root.

// nums is sorted. 
// also the number '1' is not included (leads to infinite recursion)
unordered_map<int, vector<pair<int,int>>> build_pairs_per_num(const vector<int>& nums) {
    unordered_set<int> store(nums.begin(), nums.end());
    unordered_map<int, vector<pair<int,int>>> out;
    for (int i = 0; i < nums.size(); i++) {
        int num = nums[i];
        int limit = (int) sqrt(num);

        out[num] = {};

        for (int j = 0; j <= i && nums[j] <= limit; j++) {
            int d = nums[j];
            if (num % d != 0) continue;
            if (!store.contains(num / d)) continue;
            out[num].emplace_back(d, num / d);
        }
    }
    return out;
}

class Solution {
public:
    // stores how many bst can be formed with num as the root.
    unordered_map<int, ll> store;

    int dp(int root, const unordered_map<int, vector<pair<int,int>>>& divisor_store) {
        if (store.contains(root)) return store[root];

        ll& ans = store[root];
        ans = 1; // single node is also valid
        const auto& my_pairs = divisor_store.at(root);

        if (my_pairs.size() == 0) {
            //println("pair size for {} is {}", root, 0);
            return ans;
        };

        for (const auto [a, b] : my_pairs) {
            if (a == b) {
                ans += (ll) dp(a, divisor_store) * dp(a, divisor_store);
            } else {
                ans += (ll) 2 * dp(a, divisor_store) * dp(b, divisor_store);
            }
            ans %= MOD;
        }
        
        //println("{} {}", root, ans);
        return ans;

    }
    
    int numFactoredBinaryTrees(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        auto divisor_store = build_pairs_per_num(arr);

        /*for (auto [k, v] : divisor_store) {
            cout << k << ": ";
            for (auto [p1, p2] : v) {
                println("({} {})", p1, p2);
            }
        }*/
        
        for (int x : arr) dp(x, divisor_store);

        ll sum = 0;
        for (auto [k, v] : store) {
            //println("{} {}", k, v);
            sum += v;
            sum %= MOD;
        }

        return (int) sum;
    }
};

int main() {
    Solution sol;

    vector<int> arr = {18, 3, 6, 2};

    int ans = sol.numFactoredBinaryTrees(arr);
    println("Ans is {}", ans);
}