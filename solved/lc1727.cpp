#include <bits/stdc++.h>
using namespace std;

// key insight, assume largest angle in histogram where we can rearrange the histogram.
// we sort in decreasing order, the go left to right, area for index i is height[i] * (i + 1).
// we do this for each row.

class Solution {
public:
    vector<vector<int>> get_height(const vector<vector<int>>& matrix) {
        vector<vector<int>> store = vector(matrix.size(), vector(matrix[0].size(), 0));
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                int val = matrix[i][j], &val2 = store[i][j];
                if (matrix[i][j] == 0) {
                    val2 = 0;
                } else if (i == 0) {
                    val2 = 1;
                } else {
                    val2 = store[i - 1][j] + 1;
                }
            }
        }
        return store;
    }

    int largest_submatrix_per_row(const vector<int>& heights) {
        vector<int> temp = heights;
        sort(temp.begin(), temp.end(), greater<int>());

        int best = 0;
        for (int i = 0; i < heights.size(); i++) {
            best = max(best, (i + 1) * temp[i]);
        }
        return best;
    }

    int largestSubmatrix(vector<vector<int>>& matrix) {
        auto store = get_height(matrix);

        vector<int> results(matrix.size(), 0);
        transform(store.begin(), store.end(), results.begin(), [this] (const vector<int>& row) { return largest_submatrix_per_row(row);});
        return *max_element(results.begin(), results.end());
    }
};

int main() {
    Solution sol;
    vector<vector<int>> matrix = {{1,1,0,1,1},{1,0,1,1,1},{1,1,1,0,1}};
    int ans = sol.largestSubmatrix(matrix);
    println("Ans: {}", ans);
}