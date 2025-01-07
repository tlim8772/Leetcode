#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// dynamic programming
// sort in increasing left end point
// state is (idx, cnt) idx means we are looking for best ans in arr[idx, end], with <= cnt indices chosen


struct Res {
    ll score = -1;
    vector<int> indices;

    Res() {}

    Res(int score): score(score) {}

    Res add(int idx, int score) {
        Res res = *this;
        res.score += score;
        res.indices.push_back(idx);
        sort(res.indices.begin(), res.indices.end());
        return res;
    }

    Res add(int x) {
        Res res = *this;
        res.indices.push_back(x);
        sort(res.indices.begin(), res.indices.end());
        return res;
    }

    bool operator>(const Res& other) {
        if (score > other.score) return true;
        else if (score < other.score) return false;
        
        int len = min(indices.size(), other.indices.size());
        for (int i = 0; i < len; i ++) {
            if (indices[i] < other.indices[i]) return true;
            else if (indices[i] > other.indices[i]) return false;
        }

        return (indices.size() < other.indices.size());

    } 
};

class Solution {
public:
    vector<vector<Res>> dp;

    void process(vector<vector<int>>& intervals) {
        for (int i = 0; i < intervals.size(); i ++) {
            intervals[i].push_back(i);
        }

        auto cmp = [] (vector<int>& a1, vector<int>& a2) {return a1[0] < a2[0];};
        sort(intervals.begin(), intervals.end(), cmp);
        
    }

    int binarySearch(vector<vector<int>>& intervals, int key) {
        int s = 0, e = intervals.size() - 1;
        while (s < e) {
            int m = (s + e) >> 1;
            if (intervals[m][0] > key) e = m;
            else s = m + 1;
        }
        return (intervals[s][0] > key) ? s : intervals.size();
    }

    Res helper(int idx, int cnt, vector<vector<int>>& intervals) {
        if (idx == intervals.size() || cnt == 0) {
            return Res(0);
        } else if (dp[idx][cnt].score != -1) {
            return dp[idx][cnt];
        } else {
            Res best;
            vector<int>& interval = intervals[idx];
            
            // take
            int end = interval[1];
            int nextIdx = binarySearch(intervals, end);
            Res res1 = helper(nextIdx, cnt - 1, intervals).add(interval[3], interval[2]);
            if (res1 > best) best = res1;

            // no take
            Res res2 = helper(idx + 1, cnt, intervals);
            if (res2 > best) best = res2;

            dp[idx][cnt] = best;
            return best;
        }
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        dp = vector(intervals.size(), vector(5, Res()));
        process(intervals);

        Res ans = helper(0, 4, intervals);
        return ans.indices;
    }



};

int main() {
    Solution sol;
    Res res;
    
    vector<vector<int>> intervals = {{5,8,1}, {6,7,7}, {4,7,3}, {9,10,6}, {7,8,2}, {11,14,3}, {3,5,5}};
    vector<int> ans = sol.maximumWeight(intervals);

    for (int x : ans) cout << x << " ";
    cout << endl;
}