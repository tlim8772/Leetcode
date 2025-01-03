#include <bits/stdc++.h>
using namespace std;

// consider the 1d case
// if can split into 3 sections such that each interval does not intersect the 'line', 
// and 1 interval for each section, we are done
// check x-coor and y-coor seperately

class Solution {
public:

    bool checkCanCutIntervals(int n, vector<vector<int>>& intervals) {
        map<int, int> store;
        for (vector<int>& interval : intervals) {
            store[interval[0]] = max(interval[1], store[interval[0]]);
        }

        int cnt = 0;
        auto ptr = store.begin();
        int m = 0;
        while (ptr != store.end()) {
            int end = ptr->second;
            if (end == n) break;

            while (ptr != store.end() && ptr->first < end) {
                m = max(m, ptr->second);
                ptr ++;
            }

            if (m <= end) cnt ++;
            
        }
        return cnt >= 2;

    }

    bool checkValidCuts(int n, vector<vector<int>>& rectangles) {
        vector<vector<int>> xcoors;
        vector<vector<int>> ycoors;
        for_each(rectangles.begin(), rectangles.end(), [&xcoors, &ycoors] (vector<int>& r) {
            xcoors.push_back({r[0], r[2]});
            ycoors.push_back({r[1], r[3]});
        });

        bool xcan = checkCanCutIntervals(n, xcoors);
        bool ycan = checkCanCutIntervals(n, ycoors);
        return xcan || ycan;
      
    }
};

int main() {
    Solution sol;
    vector<vector<int>> intervals = {{1,0,5,2},{0,2,2,4},{3,2,5,3},{0,4,4,5}};
    cout << sol.checkValidCuts(5,intervals);


}