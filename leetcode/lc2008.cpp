#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <chrono>
#include <queue>
using namespace std;

class Solution {
public:
    vector<long long>* dp;
    
    int binarySearch(int val, vector<vector<int>>& trips) {
        if (val > trips[trips.size() - 1][0]) {
            return trips.size();
        }
        int s = 0;
        int e = trips.size() - 1;
        while (s < e) {
            int m = (s + e) / 2;
            vector<int>& t = trips[m];
            if (t[0] < val) {
                s = m + 1;
            } else {
                e = m;
            }
        }
        return s;
    }

    long long helper(int index, vector<vector<int>>& trips) {
        if (index == trips.size()) {
            return 0;
        } else if ((*dp)[index] != -1) {
            return (*dp)[index]; 
        } else {
            vector<int>& trip = trips[index];
            int next = binarySearch(trip[1], trips);
            long long use = trip[1] - trip[0] + trip[2] + helper(next, trips);
            long long noUse = helper(index + 1, trips);
            long long ans = max(use, noUse);
            (*dp)[index] = ans;
            return ans;
        }
    }

    long long maxTaxiEarnings(int n, vector<vector<int>>& rides) {
        dp = new vector(rides.size(), -1LL);
        auto cmp = [](vector<int> x, vector<int> y) -> bool {return x[0] < y[0];};
        sort(rides.begin(), rides.end(), cmp);
        return helper(0, rides);
    }
};

int main() {
    vector<vector<int>> trips = {{1,6,1},{3,10,1},{10,12,3},{11,12,2},{12,15,2},{13,18,1}};
    Solution sol;
    cout << sol.maxTaxiEarnings(20, trips) << endl;
}