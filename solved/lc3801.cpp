#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// use bitmasks
// for all possible sets, find the length and the median using brute force. 
// combine the respective lists.

// then use dp over subset.
// for each set, try all splits into 2 subsets then find the best result.

// time complexity is 2^12 * 2000 + 3^12

class Solution {
public:
    uint32_t n, max_bm;
    vector<vector<int>> lists;
    vector<pair<int,int>> values;
    vector<ll> dp_store;

    void getMedians() {
        vector<int> store;
        store.reserve(max_bm);

        for (uint32_t bm = 1; bm < max_bm; bm++) {
            store.clear();
            for (int s = 0; s < n; s++) {
                if (!((bm >> s) & 1)) continue;
                auto& lst = lists[s];
                store.insert(store.end(), lst.begin(), lst.end());
            }
            sort(store.begin(), store.end());
            values[bm] = {store.size(), store[(store.size() - 1) >> 1]};
        }
    }

    void dp() {
        for (uint32_t bm = 0; bm < max_bm; bm++) {
            ll best = 1e16;
            bool has_merge = false;
            for (uint32_t subset = (bm - 1) & bm; subset > 0; subset = (subset - 1) & bm) {
                uint32_t complement = (bm & ~subset);
                if (complement > subset) continue;
                
                pair<int,int>& p_subset = values[subset], p_complement = values[complement];
                ll ans = p_subset.first + p_complement.first + abs(p_subset.second - p_complement.second) + 
                    dp_store[subset] + dp_store[complement];
            

                has_merge = true;
                best = min(best, ans);
            }
            dp_store[bm] = (has_merge) ? best : 0;
        }
    }

    
    long long minMergeCost(vector<vector<int>>& lists) {
        n = lists.size(), max_bm = 1 << n;
        this->lists = lists;
        values = vector<pair<int,int>>(max_bm, {0, 0});
        dp_store = vector<ll>(max_bm, 0);

        getMedians();
        dp();

        //for (auto [len, median] : values) cout << len << " " << median << endl;

        return dp_store[max_bm - 1];
    }
};

int main() {
    Solution sol;

    vector<vector<int>> lists = {{1,3,5},{2,4},{6,7,8}};
    int ans = sol.minMergeCost(lists);
    cout << ans << endl;
}