#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// split into 2 cases: product is 0 and not 0
// reason is because if product is 0, the interim product can be arbitarily large
// very annoying dp
// improve time by pruning impossible states, i.e whem k < -900 || k > 900
// and for case 1, when intermin product > limit

struct Pair {
    bool poss;
    int p;
};

// if product == 0, we have dp(hasTaken, hasTaken0, side, i, sum)
class Case0 {
public:
    ll S0 = 2 * 2 * 150 * 1801, S1 = 2 * 150 * 1801, S2 = 150 * 1801, S3 = 1801;
    unordered_map<ll, Pair> dp;

    inline ll coor(int hasTaken, int hasTaken0, int side, int i, int sum) {
        return hasTaken * S0 + hasTaken0 * S1 + side * S2 + i * S3 + sum;
    }

    Pair helper(int hasTaken, int hasTaken0, int side, int i, int sum, vector<int>& nums, int target) {
        if (i == nums.size()) {
            return (hasTaken && hasTaken0 && sum == target) ? Pair{true, 0} : Pair{false, -1};
        }

        int pos = coor(hasTaken, hasTaken0, side, i, sum);
        if (dp.contains(pos)) {
            return dp[pos];
        } 

        Pair noTake = helper(hasTaken, hasTaken0, side, i + 1, sum, nums, target);

        int nSum = (side == 0) ? sum + nums[i] : sum - nums[i];
        Pair take = helper(1, hasTaken0 || nums[i] == 0, !side, i + 1, nSum, nums, target);

        Pair ans;
        if (!noTake.poss && !take.poss) {
            ans = {false, -1};
        } else {
            ans = {true, 0};
        }

        dp[pos] = ans;
        return ans;
    }

    int solve(vector<int>& nums, int k, int limit) {
        Pair ans = helper(0, 0, 0, 0, 0, nums, k);
        return ans.p;
    }

};

// dp(hasTaken, int side, int i, int sum, int prod)
class Case1 {
public:
    ll S0 = (ll) 2 * 150 * 1801 * 5001, S1 = 150 * 1801 * 5001, S2 = 1801 * 5001, S3 = 5001;
    unordered_map<ll, Pair> dp;

    inline ll coor(int hasTaken, int side, int i, int sum, int prod) {
        return hasTaken * S0 + side * S1 + i * S2 + sum * S3 + prod;
    }

    Pair helper(int hasTaken, int side, int i, int sum, int prod, vector<int>& nums, int target, int limit) {
        if (i == nums.size()) {
            return (hasTaken && sum == target) ? Pair{true, prod} : Pair{false, -1};
        }

        ll pos = coor(hasTaken, side, i, sum, prod);
        if (dp.contains(pos)) {
            return dp[pos];
        }

        Pair notake = helper(hasTaken, side, i + 1, sum, prod, nums, target, limit);

        int nSum = (side == 0) ? sum + nums[i] : sum - nums[i];
        int nProd = prod * nums[i];
        Pair take = (nProd == 0 || nProd > limit) ? Pair{false, -1} : helper(1, 1 - side, i + 1, nSum, nProd, nums, target, limit);

        Pair ans;
        if (!notake.poss && !take.poss) {
            ans = {false, -1};
        } else {
            ans = {true, max(take.p, notake.p)};
        }

        dp[pos] = ans;
        return ans;
    }

    int solve(vector<int>& nums, int k, int limit) {
        Pair ans = helper(0, 0, 0, 0, 1, nums, k, limit);
        return ans.p;
    }
};

class Solution {
public:
    int maxProduct(vector<int>& nums, int k, int limit) {
        if (k < -900 || k > 900) return -1;
        
        Case0 c0;
        Case1 c1;

        int p1 = c1.solve(nums, k, limit);
        if (p1 != -1) return p1;

        int p0 = c0.solve(nums, k, limit);
        return p0;
    }
};



int main() {
    Case1 c0;

    vector<int> nums = {2,2,3,3};
    int k = 0;
    int limit = 9;

    cout << c0.solve(nums, k, limit) << endl;
}