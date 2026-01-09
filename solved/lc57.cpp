#include <bits/stdc++.h>
using namespace std;

// intervals is non overlapping and increasing
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> out;
        bool used = false;

        for (int i = 0; i < intervals.size(); i++) {
            auto v = intervals[i];
            if (!used && newInterval[0] <= v[0]) {
               v = newInterval;
               i--;
               used = true;
            }

            if (!out.empty() && out.back()[1] >= v[0]) {
                out.back()[1] = max(out.back()[1], v[1]);
            } else {
                out.push_back(v);
            }
        }

        if (!used) {
            if (!out.empty() && out.back()[1] >= newInterval[0]) {
                out.back()[1] = max(out.back()[1], newInterval[1]);
            } else {
                out.push_back(newInterval);
            }
        }

        return out;  
    }
};