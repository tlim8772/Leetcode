#include <bits/stdc++.h>
using namespace std;

// dont really know the time complexity for this one
// anyway bitmask, 1 means module i has been read
// get all available modules, then iterate through all nCk subsets (n is the # of modules we can read next),
// add to bitmask, then recurse

class Solution {
public:
    int N, K;
    vector<vector<int>> adj;
    vector<int> inDeg;

    // we can reuse these 2 arrays
    vector<int> canTake;

    vector<int> dp;

    void process(int n, vector<vector<int>>& relations, int k) {
        N = n, K = k;
        adj = vector(N, vector<int>());
        inDeg = vector(N, 0);
        
        dp = vector(1 << n, -1);
        
        for (vector<int>& r : relations) {
            adj[r[0] - 1].push_back(r[1] - 1);
            inDeg[r[1] - 1] ++;
        }
    }

    int helper1(int bm) {
        if (dp[bm] != -1) {
            return dp[bm];
        } else if (bm + 1 == (1 << N)) {
            return 0;
        } else {
            vector<int> canTake;
            vector<int> temp = inDeg;
            
            for (int i = 0; i < N; i ++) {
                if ((bm >> i) & 1) {
                    for (int c : adj[i]) temp[c] --;
                }
            }

            for (int i = 0; i < N; i ++) {
                if ((bm >> i) & 1) continue; // already taken before
                if (temp[i] == 0) canTake.push_back(i);
            }

            int ans = helper2(bm, canTake, 0, K);
            dp[bm] = ans;
            return ans;
        }
    }

    int helper2(int bm, vector<int>& canTake, int idx, int left) {
        if (canTake.size() - idx <= left) {
            // must take all
            for (int i = idx; i < canTake.size(); i ++) {
                bm = bm | (1 << canTake[i]);
            }
            return 1 + helper1(bm);
        } else if (left == 0) {
            return 1 + helper1(bm);
        } 
        else {
            // take idx
            int opt1 = helper2(bm | (1 << canTake[idx]), canTake, idx, left - 1);

            // dont take
            int opt2 = helper2(bm, canTake, idx + 1, left);
            return min(opt1, opt2);
        }
    }


    int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {
        process(n, relations, k);
        return helper1(0);
    }
};

int main() {
    Solution sol;

    int n = 6;
    vector<vector<int>> rs = {{1,2},{1,3},{4,3},{4,5},{2,6},{3,6},{5,6}};
    int k = 2;

    cout << sol.minNumberOfSemesters(n, rs, k) << endl;
}