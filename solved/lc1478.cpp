#include <bits/stdc++.h>
using namespace std;

// sort houses
// for each mailbox assign a contigous range of houses to it

class Solution {
public:
    vector<vector<int>> dp;

    int helper(int idx, int k, vector<int>& houses) {
        if (idx == houses.size()) return 0; // if no houses left, we are done
        if (k == 0) return 999999999; // k == 0, but idx != houses.size(), so we have not reach the end
        if (dp[idx][k] != -1) return dp[idx][k];

        int sum = 0;
        int currMedian = idx;
        int minDist = helper(idx + 1, k - 1, houses);
        for (int i = idx + 1; i < houses.size(); i ++) {
            int newMedian = (idx + i) >> 1;
            if (newMedian == currMedian) {
                sum += houses[i] - houses[currMedian];
            } else {
                sum += houses[i] - houses[newMedian];
                sum += (currMedian - idx + 1) * (houses[newMedian] - houses[currMedian]);
                sum -= (i - 1 - currMedian) * (houses[newMedian] - houses[currMedian]);
            }
            currMedian = newMedian;
            minDist = min(minDist, sum + helper(i + 1, k - 1, houses));
        }
        dp[idx][k] = minDist;
        return minDist;
    }

    int minDistance(vector<int>& houses, int k) {
        sort(houses.begin(), houses.end());
        dp = vector(houses.size(), vector(k + 1, -1));
        return helper(0, k, houses);
    }
};

int main() {
    vector<int> houses = {7,4,6,1};
    int k = 1;
    Solution sol;
    cout << sol.minDistance(houses, k) << endl;
}