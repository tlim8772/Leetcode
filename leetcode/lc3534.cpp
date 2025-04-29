#include <bits/stdc++.h>
using namespace std;

// we sort the array, there exist a path from v2 to v1, v1 < v2, where we take the largest possible jump
// every time until the last jump (a greedy strategy) easy to prove
// the last jump can be a largest possible jump too, or not
// so keep taking the largest possible jump. use binary lifting to store the next val when we jump 2^0,
// 2^1, 2^2 .. etc.

class Solution {
public:
    int MAX, diff;
    vector<int> compressed;
    unordered_map<int, vector<int>> binLift;

    void process(vector<int>& nums) {
        MAX = (int) log2(nums.size());

        set<int> temp{nums.begin(), nums.end()};
        compressed = vector<int>{temp.begin(), temp.end()};
    }

    // find 1st jump for v
    // can return v itself, if diff is too small
    int binarySearch(const vector<int>& nums, int v, int diff) {
        int s = 0, e = nums.size() - 1;
        int target = v - diff;
        
        while (s < e) {
            int m = (s + e) >> 1;
            if (nums[m] < target) {
                s = m + 1;
            } else {
                e = m;
            }
        }

        return nums[s];
    }

    void binaryLift() {
        binLift[compressed[0]] = vector(MAX + 1, -1);

        for (int i = 1; i < compressed.size(); i++) {
            vector<int> myBin = vector(MAX + 1, -1);
            int par = binarySearch(compressed, compressed[i], diff);
            myBin[0] = (par == compressed[i]) ? -1 : par;
            
            for (int d = 1; d <= MAX; d++) {
                if (myBin[d - 1] == -1) break;
                myBin[d]  = binLift[myBin[d - 1]][d - 1];
            }

            binLift[compressed[i]] = myBin;
        }
    }

    int query(vector<int>& nums, int i, int j) {
        int start = nums[i];
        int end = nums[j];
        if (start < end) {
            swap(start, end);
        } else if (start == end) {
            // case 1: i == j, i.e same node
            // case 2: nums[i] == nums[j] but i != j, then only 1 jump needed. Nodes with same value form a clique
            return (i == j) ? 0 : 1; 
        }

        int cnt = 0;

        for (int p = MAX; p >= 0; p--) {
            int next = binLift[start][p];
            
            if (next == -1 || next < end) {
                continue;
            } else {
                start = next;
                cnt += (1 << p);
            }
            
        }

        if (start - diff > end) {
            // case 3: cannot reach end from start;
            return -1;
        } else {
            return (start == end) ? cnt : cnt + 1;
        }
    }



    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        diff = maxDiff;
        process(nums);
        binaryLift();

        vector<int> out;
        for (vector<int>& q : queries) {
            int ans = query(nums, q[0], q[1]);
            out.push_back(ans);
        }
        
        return out;;
    }
};

int main() {
    Solution sol;

    int n = 5;
    vector<int> nums = {0,1,2,3,4,5,6,100};
    int diff = 1;
    vector<vector<int>> queries = {{0,3},{2,4},{7,2}};

    vector<int> ans = sol.pathExistenceQueries(5, nums, diff, queries);
    for (int x : ans) cout << x << endl;

    
}