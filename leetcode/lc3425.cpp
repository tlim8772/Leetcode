#include <bits/stdc++.h>
using namespace std;

// sliding window on a tree
// consider the path from root (0) to a leaf
// can use sliding window to find all valid paths in O(len of path)
// any (special) path lies on a path from root to leaf

// however, we need to pop nodes as we traverse the tree
// use binary search to quickly jump to the next l index when we add a new color, by finding the index where the
// previous same color occurs. then l = index just found + 1
//
// for the new index r (r is now pointing to elem we are processing), 
// we store the leftmost index l1, s.t [l1, r] is all distinct color nodes 

// when we pop, r --. For r - 1 (the new endpoint, not past the last elem, we jst decremented r) 
// we need to find the earliest index l, s.t [l, r - 1] is all distinct
// color. We do that by storing, for each r, the earliest index l, s.t [l, r] is all distinct color, then we can go back
// in O(1)

// we use prefix sums to get the length when we have [l, r). We can push and pop the prefix sum stack as needed

class Solution {
public:
    int n;
    unordered_map<int, unordered_map<int, int>> adj;
    vector<vector<int>> adj2;
    vector<int> colors;

    int bestLen = 0;
    int minNumNode = 1e5;

    int l= 0, r = 0; // [l, r) is the curr valid sequence
    vector<int> nodes;
    vector<int> startIdx; //returns the leftmost possible startIdx 
    vector<int> prefixSum;
    vector<vector<int>> colorIdx = vector(50001, vector<int>());

     void updateRes(int len, int numNodes) {
        if (len == bestLen) {
            minNumNode = min(minNumNode, numNodes);
        } else if (len > bestLen) {
            bestLen = len;
            minNumNode = numNodes;
        }
    }

    void process(vector<vector<int>>& edges, vector<int>& nums) {
        n = nums.size();
        
        colors = nums;

        adj2 = vector(n, vector<int>());
        
        for (vector<int>& e : edges) {
            adj[e[0]][e[1]] = e[2];
            adj[e[1]][e[0]] = e[2];
            
            adj2[e[0]].push_back(e[1]);
            adj2[e[1]].push_back(e[0]);
        }
    }

    // returns the smallest elem >= key
    int binarySearch(const vector<int>& arr, int key) {
        if (arr.empty()) return -1;

        int s = 0, e = arr.size() - 1;
        while (s < e) {
            int m = (s + e) >> 1;
            if (arr[m] >= key) e = m;
            else s = m + 1;
        }
        return (arr[s] >= key) ? arr[s] : -1; // if res is -1, then l >= 0 > -1
    }


    // extend the sliding windows as we add nodes. Invariant, r is at "past the last elem"
    // but before we added the new elem.
    // basically r is the index to the new elem we just added.
    void extend() {
        int cIdx = binarySearch(colorIdx[colors[nodes[r]]], l);
        if (cIdx >= l) {
            l = cIdx + 1;
        }

        // only after binary searching, then we add the index to colorIdx
        colorIdx[colors[nodes[r]]].push_back(r);

        r++;
        startIdx.push_back(l);
        updateRes(prefixSum[r - 1] - prefixSum[l], r - l);
        // cout << nodes[l] << " " << nodes[r - 1] << " " << prefixSum[r - 1] - prefixSum[l] << endl;
    }

    // right now, r is pointing at 'past the last elem'
    void pop_back() {
        colorIdx[colors[nodes[r - 1]]].pop_back();
        startIdx.pop_back();
        nodes.pop_back();
        prefixSum.pop_back();
        r --;
        
        l = (startIdx.size() == 0) ? 0 : startIdx.back();
    }

    void dfs(int v, int p) {
        prefixSum.push_back((v == p) ? 0 : prefixSum.back() + adj[p][v]);
        nodes.push_back(v);
        extend();

        for (int c : adj2[v]) {
            if (c == p) continue;
            
            dfs(c, v);
        }

        pop_back();

    }

     vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        process(edges, nums);

        dfs(0, 0);

        return {bestLen, minNumNode};
    }

};

int main() {
    vector<vector<int>> edges = {{0,1,2},{1,2,3},{1,3,5},{1,4,4},{2,5,6}};
    vector<int> nums = {2,1,2,1,3,1};

    Solution sol;
    vector<int> ans = sol.longestSpecialPath(edges, nums);
    cout << ans[0] << " " << ans[1] << endl;
    
}