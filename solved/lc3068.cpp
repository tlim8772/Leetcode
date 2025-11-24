#include <vector>
#include <iostream>
#include <stdio.h>
#include <queue>
using namespace std;
#define ll long long

// let dp[b][node] be the best result for the subtree rooted at node, and whether the edge of node-parent is used
// we find dp[0][child] for all childs of node
// if we want to flip, clearly we take the node edge child that is the biggest -dp[0][child] + dp[1][child];

class Solution {
public:
    vector<vector<int>> adjList;
    // dp[0][node] stores the the best sum of childred when even number of node-child edges are chosen, vice versa for dp[1][node]
    vector<vector<ll>> dp1;
    // stores best result for node;
    //vector<vector<ll>> dp2;
    vector<int> values;
    int k;

    void process(int n, vector<vector<int>>& edges) {
        adjList = vector(n, vector<int>());
        for (vector<int>& e : edges) {
            adjList[e[0]].push_back(e[1]);
            adjList[e[1]].push_back(e[0]);
        }
        dp1 = vector(2, vector<ll>(n, -1));
    }


    // 0 means not XORed before
    void helper(int node, int parent) {
        vector<int>& childs = adjList[node];
        int leaf = true;
        for (int c : childs) {
            if (c != parent) {
                helper(c, node);
                leaf = false;
            }
        }
        if (leaf) {
            dp1[0][node] = (ll) values[node];
            dp1[1][node] = (ll) values[node] ^ k;
            return;
        }
        ll sum = 0;
        priority_queue<ll, vector<ll>, less<ll>> pq;
        for (int i = 0; i < childs.size(); i ++) {
            if (childs[i] != parent) {
                sum += dp1[0][childs[i]];
                pq.push(dp1[1][childs[i]] - dp1[0][childs[i]]);
            }
        }
        ll evenBest = sum;
        ll oddBest = 0;
        int popped = 0;
        while (!pq.empty()) {
            
            ll res = pq.top();
            pq.pop();
            sum += res;
            (popped % 2 == 0) ? oddBest = max(oddBest, sum) : evenBest = max(evenBest, sum);
            popped += 1;
        }
        
        ll op1 = values[node];
        ll op2 = values[node] ^ k;
        dp1[0][node] = max(op1 + evenBest, op2 + oddBest);
        dp1[1][node] = max(op2 + evenBest, op1 + oddBest);
       
    }

    long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) {
        this->k = k;
        values = nums;
        process(nums.size(), edges);
        helper(0, 0);
        return dp1[0][0]; // root does not have parent
    }
};

void print(vector<vector<ll>> arr) {
    for (int i = 0; i < arr.size(); i ++) {
        for (int j = 0; j < arr[0].size(); j ++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    Solution sol;
    vector<int> nums = {24, 78, 1, 97, 44};
    int k = 6;
    vector<vector<int>> edges = {{0,2}, {1,2},{4,2},{3,4}};
    cout << sol.maximumValueSum(nums, k, edges) << endl;
    
    
}