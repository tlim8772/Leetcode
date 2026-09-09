#include <bits/stdc++.h>
using namespace std;

// let dp(start) be the best score we can get from processing tasks whose start time is >= start.
// sort by start time and group all tasks with the same start time together.
// at every stage, we can take a task and then go to the next stage with the smallest greater start time.

struct task {
    int start, end, price;
};

class Solution {
public:
    unordered_map<int, int> store;
    map<int, vector<task>> stages;

    int dp(int start) {
        auto stage = stages.lower_bound(start);
        if (stage == stages.end()) return 0;

        start = stage->first;
        
        auto ans = store.find(start);
        if (ans != store.end()) return ans->second;

        int best = dp(start + 1);
        for (auto [s, e, p] : stage->second) {
            int res = p + dp(e);
            best = max(best, res);
        }

        return store[start] = best;
    }

    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        for (int i = 0; i < startTime.size(); i++) {
            stages[startTime[i]].push_back({startTime[i], endTime[i], profit[i]});
        }

        return dp(1);
    }
};

int main() {
    Solution sol;

    vector<int> start = {1,2,3,3};
    vector<int> end = {3,4,5,6};
    vector<int> profit = {50,10,40,70};

    int ans = sol.jobScheduling(start, end, profit);
    cout << ans << endl;
}