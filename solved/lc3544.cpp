#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INVALID = -1e15;

// simple tree dp
// dp(node, how many edges left before having enough distances, inverted or not)

class Solution {
public:
    int N, K, B = 2;

    vector<vector<int>> adj;
    vector<int> nums;

    vector<ll> dp;

    inline int coor(int n, int k, int b) {
        return n * K * B + k * B + b;
    }

    void process(vector<vector<int>>& edges) {
        for (vector<int>& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }
    }

    ll helper(int n, int k, int b, int p) {
        int pos = coor(n, k, b);
        if (dp[pos] != INVALID) {
            return dp[pos];
        }

        ll noInvert = (b == 0) ? nums[n] : -nums[n];
        for (int c : adj[n]) {
            if (c == p) continue;
            noInvert += helper(c, max(k - 1, 0), b, n);
        }

        ll invert = INVALID;
        if (k == 0) {
            invert = (b == 1) ? nums[n] : -nums[n];
            for (int c : adj[n]) {
                if (c == p) continue;
                invert += helper(c, K - 1, 1 - b, n);
            }
        }

        ll best = max(noInvert, invert);
        dp[pos] = best;
        return best;

    }

    long long subtreeInversionSum(vector<vector<int>>& edges, vector<int>& nums, int k) {
        N = nums.size(), K = k;
        adj = vector(N, vector<int>());
        this->nums = nums;
        dp = vector(N * K * 2, INVALID);

        process(edges);

        ll ans = helper(0, 0, 0, 0);
        return ans;
    }




};

int main() {
    Solution sol;
    vector<vector<int>> edges = {{0,1},{0,2}};
    vector<int> nums = {0,-1,-2};
    int k = 3;

    cout << sol.subtreeInversionSum(edges, nums, k) << endl;
}