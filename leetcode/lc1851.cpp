#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;

class SegmentTree {
public: 
    vector<int>* tree;
    int size;

    SegmentTree(int n) {
        size = n;
        tree = new vector(4 * n, 100000000);
    }

    void updateRangeMin(int p, int s, int e, int l, int r, int val) {
        int m = (s + e) / 2;
        if (s == e) {
            (*tree)[p] = min((*tree)[p], val);
        } else if (s == l && e == r) {
            (*tree)[p] = min((*tree)[p], val);
        } else if (r <= m) {
            updateRangeMin(2 * p + 1, s, m, l, r, val);
        } else if (l > m) {
            updateRangeMin(2 * p + 2, m + 1, e, l, r, val);
        } else {
            updateRangeMin(2 * p + 1, s, m, l, m, val);
            updateRangeMin(2 * p + 2, m + 1, e, m + 1, r, val);
        }
    }

    int getMin(int p, int s, int e, int i) {
        int m = (s + e) / 2;
        if (s == e) {
            return (*tree)[p];
        } else if (i <= m) {
            int thisRange = (*tree)[p];
            int rest = getMin(2 * p + 1, s, m, i);
            return min(rest, thisRange);
        } else {
            int thisRange = (*tree)[p];
            int rest = getMin(2 * p + 2, m + 1, e, i);
            return min(rest, thisRange);
        }
    }
};

class Solution {
public:
    unordered_map<int, int> compress(vector<vector<int>>& intervals, vector<int>& queries) {
        unordered_map<int, int> result;
        vector<int> store;
        for (int i = 0; i < queries.size(); i ++) {
            if (result.find(queries[i]) == result.end()) {
                store.push_back(queries[i]);
                result[queries[i]] = 1;
            }
        }
        for (int i = 0; i < intervals.size(); i ++) {
            int num1 = intervals[i][0];
            if (result.find(num1) == result.end()) {
                store.push_back(num1);
                result[num1] = 1;
            }
            int num2 = intervals[i][1];
            if (result.find(num2) == result.end()) {
                store.push_back(num2);
                result[num2] = 1;
            }
        }
        sort(store.begin(), store.end());
        for (int i = 0; i < store.size(); i ++) {
            result[store[i]] = i;
        }
        return result;
    }

    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        unordered_map<int, int>&& map = compress(intervals, queries);
        SegmentTree st(map.size());
        vector<int> out;
        for (int i = 0; i < intervals.size(); i ++) {
            int score = intervals[i][1] - intervals[i][0] + 1;
            int l = map[intervals[i][0]];
            int r = map[intervals[i][1]];
            st.updateRangeMin(0, 0, st.size - 1, l, r, score);
        }
        for (int i = 0; i < queries.size(); i ++) {
            int index = map[queries[i]];
            int ans = st.getMin(0, 0, st.size - 1, index);
            ans = (ans == 100000000) ? -1 : ans;
            out.push_back(ans);
        }
        return out;
    }

};

int main() {
    Solution sol;
    vector<vector<int>> intervals({{2,3},{2,5},{1,8},{20,25}});
    vector<int> queries({2,9,5,22});
    vector<int> ans = sol.minInterval(intervals, queries);
    for (int i = 0; i < ans.size(); i ++) {
        cout << ans[i] << " ";
    }

}