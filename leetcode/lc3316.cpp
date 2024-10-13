#include <bits/stdc++.h>
using namespace std;

// 2d dp
// dp(i, j) = max ops we can do that still ensures suffix of pattern starting at j is still a subsequence of the suffix of s
// starting at i

class Solution {
public:
    vector<bool> canRemove;
    vector<vector<int>> dp;
    vector<int> arr;

    int binarySearch(vector<int>& arr, int key) {
        int s = 0;
        int e = arr.size() - 1;
        while (s < e) {
            int m = (s + e) >> 1;
            if (arr[m] < key) s = m + 1;
            else e = m;
        }
        return (arr[s] >= key) ? arr.size() - s : 0;
    }

    int helper(int i, int j, string& s, string& patt) {
        if (j >= patt.size()) {
            return binarySearch(arr, i);
        }
        else if (i >= s.size()) return -999999;
        else if (dp[i][j] != -1) return dp[i][j];
        
        if (canRemove[i]) {
            // just remove
            if (s[i] != patt[j]) dp[i][j] = 1 + helper(i + 1, j, s, patt);
            
            // remove or keep
            else dp[i][j] = max(1 + helper(i + 1, j, s, patt), helper(i + 1, j + 1, s, patt));
        } else {
            if (s[i] == patt[j]) dp[i][j] = helper(i + 1, j + 1, s, patt);
            else dp[i][j] = helper(i + 1, j, s, patt);
        }
        return dp[i][j];
    }

    int maxRemovals(string source, string pattern, vector<int>& targetIndices) {
        canRemove = vector(source.size(), false);
        dp = vector(source.size(), vector(pattern.size(), -1));
        arr = targetIndices;

        for (int idx : targetIndices) canRemove[idx] = true;
        return helper(0, 0, source, pattern);
    }
};

int main() {
    Solution sol;
    string src = "yeyeykyded";
    string patt = "yeyyd";
    vector<int> arr = {0,2,3,4};
    cout << sol.maxRemovals(src, patt, arr) << endl;
}