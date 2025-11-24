#include <bits/stdc++.h>
using namespace std;

// since arr.size() = 2000, we can construct a pyramid of the xor result
// e.g a1       a2         a3        a4        a5
//         a1a2     a2a3        a3a4      a4a5
//              a1a3      a2a4       a3a5
//                 a1a2a3a4    a2a3a4a5
//                       a1a2a4a5
// for each node also store the best result i.e the max xor score for all subarrays in [l, r]
// to get the result just take max(left parent best score, right parent best score), xor score of [l, r])
// now each query is in O(1) if the query is [l, r], len is r - l + 1, go to the len - 1 row, and get
// the result from the matching subarray
// basically left parent stores best result of subarray [l, r - 1] and right stores best result of subarray [l + 1, r]
// the only new subarray not considered is [l, r]

struct Pair {
    int p0, p1;

    Pair(int x, int y): p0(x), p1(y) {}
};


class Solution {
public:
    vector<vector<Pair>> pyramid;
    
    void process(vector<int>& arr) {
        pyramid = vector(arr.size(), vector<Pair>());

        for (int e : arr) {
            pyramid[0].push_back(Pair(e, e));
        }

        for (int r = 1; r < arr.size(); r ++) {
            for (int cnt = 0; cnt < pyramid[r - 1].size() - 1; cnt ++) {
                int res = pyramid[r - 1][cnt].p0 ^ pyramid[r - 1][cnt + 1].p0;
                int best = max(res, max(pyramid[r - 1][cnt].p1, pyramid[r - 1][cnt + 1].p1));
                pyramid[r].push_back(Pair(res, best));
            }
        }
    }

    int query(int l, int r) {
        int len = r - l + 1;
        return pyramid[len - 1][l].p1;
    }

    vector<int> maximumSubarrayXor(vector<int>& nums, vector<vector<int>>& queries) {
        process(nums);

        vector<int> out;
        for (vector<int>& q : queries) {
            out.push_back(query(q[0], q[1]));
        }

        return out;
    }


};

int main() {
    Solution sol;
    vector<int> arr = {0,7,3,2,8,5,1};
    vector<vector<int>> queries = {{0,3},{1,5},{2,4},{2,6},{5,6}};

    vector<int>&& ans = sol.maximumSubarrayXor(arr, queries);
    for (int i = 0; i < ans.size(); i ++) {
        cout << ans[i] << endl;
    }
}