#include <vector>
#include <cmath>
#include <iostream>
using namespace std;


// state is index (i.e start of roads[index]) and # of skips, stores the shortest time to reach that state
// i.e SSSP on a DAG
// we want the shortest path from (0, 0) to (n -1, 0), (n - 1, 1), (n - 1, 2) ...
// then we take the 1st (n - 1, i) with shortest time < limit
class Solution {
public:
    vector<vector<double>> dp;

    double helper(int n, int k, vector<int>& roads, double speed) {
        if (n == 0) {
            return (k == 0) ? 0.0 : 1000000000.0;
        } else if (dp[n][k] >= 0.0) {
            return dp[n][k];
        } else if (k == 0) {
            double ans = ceil(helper(n - 1, k, roads, speed) - 0.0000001) + roads[n - 1] / speed; // need to do round off correction i.e 2/3 + 1/3 = 1.000001 ceil gives 2
            dp[n][k] = ans;
            return ans;
        } else {
            double noSkip = ceil(helper(n - 1, k, roads, speed) - 0.0000001) + roads[n - 1] / speed;
            double skip = helper(n - 1, k - 1, roads, speed) + roads[n - 1] / speed;
            double ans = min(noSkip, skip);
            dp[n][k] = ans;
            return ans;
        }
    }

    int minSkips(vector<int>& dist, int speed, int hoursBefore) {
        dp = vector(dist.size() + 1, vector(dist.size(), -1.0));
        //int minSkip = 99999;
        for (int i = 0; i < dist.size(); i ++) {
            double time = helper(dist.size(), i, dist, (double) speed); // need n to be dist.size, because if n = dist.size - 1, miss out on last road
            if (time <= (double) hoursBefore) {
                return i;
            }
        }
        return -1;
    }
};

int main() {
    Solution s;
    vector<int> dist = {1,3,2};
    cout << s.minSkips(dist, 4, 2);
}