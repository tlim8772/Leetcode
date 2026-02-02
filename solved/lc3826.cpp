#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Pair = tuple<bool, ll>;

// score of subarray = sumArr * sumArr / 2.
// dp(i, k) = minimum sum of score of the k partitions of arr[0:i].
// cost(i, j) = score of subarray(arr[i:j])

// dp(i, k) = min dp(j, k - 1) + cost(j + 1, i).
// the cut point can only move right,
// i.e for i + 1, j' >= j.
// proof:
// lemma 1: dp(i, k) <= dp(i + 1, k).
// cost(j, i) >= cost(j + 1, i) and since cost is a convex function, 
// cost(j, x) increases faster than cost(j + 1, x) as x moves right.

// divide and conquer dp.
// for find_dp(0, n - 1), find the answer for dp((n - 1) / 2, k)
// then for the 2 halves, the 1st half only checks [0, j] and the 2nd half check [j, n - 1].
// for the next round, we have [0, j'], [j', j], [j, j''], [j'', n - 1].
// each round we have O(n) checks total and have logn rounds.

class Solution {
public:
    vector<vector<ll>> cost_store;
    vector<vector<Pair>> store;

    void make_cost_store(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            ll sum = 0;
            for (int j = i; j < nums.size(); j++) {
                sum += nums[j];
                cost_store[i][j] = (sum * (sum + 1)) / 2;
            }
        }
    }

    void divide_conquer_dp(int l, int r, int optL, int optR, int k) {
        if (r < l || l > r) return;

        int m = (l + r) >> 1;
        
        if (k == 0) {
            store[m][0] = {true, cost_store[0][m]};
            divide_conquer_dp(l, m - 1, optL, 0, k);
            divide_conquer_dp(m + 1, r, 0, optR, k);
            return;
        }
        
        int split = -1;
        ll best = (ll) 1e16;
        for (int j = optL; j <= min(m, optR); j++) {
            if (j < k) continue;
            
            auto [has, res] = store[j - 1][k - 1];
            if (!has) continue;

            ll ans = res + cost_store[j][m];
            if (ans < best) {
                split = j;
                best = ans;
            }
        }

        store[m][k] = (split == -1) ? Pair{false, 0} : Pair{true, best};
        divide_conquer_dp(l, m - 1, optL, split, k);
        divide_conquer_dp(m + 1, r, split, optR, k);
        

       
    }
    
    
    long long minPartitionScore(vector<int>& nums, int k) {
        cost_store = vector(nums.size(), vector<ll>(nums.size(), 0));
        store = vector(nums.size(), vector<Pair>(k, {false, 0}));

        make_cost_store(nums);
        
        for (int l = 0; l < k; l++) {
            divide_conquer_dp(0, nums.size() - 1, 0, nums.size() - 1, l);
        }

        auto [has, ans] = store[nums.size() - 1][k - 1];
        return ans;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {5,1,2,1};
    int k = 2;
    cout << sol.minPartitionScore(nums, k) << endl;
}