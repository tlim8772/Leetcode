#include <bits/stdc++.h>
using namespace std;

// to maximise # of nodes with dist <= k from node i in tree 1
// we stick tree 2 as close to node i as possible, so connect to node i
// for each tree, for each node, we have an array of len n.
// arr[i] is the number of nodes with dist <= i.
// when connecting tree 2 to node i, we try every possible node i tree 2 and take the best result.
// i.e when connecting node i of tree 1 to node j of tree 2, ans is sums1[i][k] + sums2[j][k - 1] 
// (if k == 0, then sums2[j][k - 1] = 0).

vector<vector<int>> getAdj(const vector<vector<int>>& edges) {
    vector<vector<int>> adj = vector(edges.size() + 1, vector<int>());
    for (const vector<int>& e : edges) {
        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]);
    }
    return adj;
}

vector<int> convertToPrefixSum(const vector<int>& arr) {
    vector<int> out(arr.size(), arr[0]);
    for (int i = 1; i < arr.size(); i++) {
        out[i] = arr[i] + out[i - 1];
    }
    return out;
}

void convertToPrefixSumInPlace(vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) arr[i] = arr[i] + arr[i - 1];
}

void dfs1(int v, int p, const vector<vector<int>>& adj, vector<vector<int>>& sums) {
    for (int next : adj[v]) {
        if (next == p) continue;
        dfs1(next, v, adj, sums);
    }
    
    vector<int>& mySum = sums[v];
    mySum[0] = 1;
    for (int next : adj[v]) {
        if (next == p) continue;
        vector<int>& sum = sums[next];
        for (int i = 1; i < sum.size(); i++) {
            mySum[i] += sum[i - 1];
        }
    }
}

void dfs2(int v, int p, const vector<vector<int>>& adj, vector<vector<int>>& sums) {
    if (v != p) {
        vector<int>& parentSum = sums[p];
        vector<int> copy = sums[v];
        vector<int>& mySum = sums[v];
        for (int i = 1; i < mySum.size(); i++) {
            int douCnt = (i - 2 < 0) ? 0 : copy[i - 2];
            int toAdd = (i - 1 < 0) ? 0 : parentSum[i - 1] - douCnt;
            mySum[i] += toAdd;
        }
    }
    for (int next : adj[v]) {
        if (next == p) continue;
        dfs2(next, v, adj, sums);
    }
}

void printRes(vector<vector<int>> arr) {
    for (vector<int> a : arr) {
        for (int x : a) cout << x << " ";
        cout << endl;
    }
}

class Solution {
public:
    vector<vector<int>> adj1, adj2;
    vector<vector<int>> sums1, sums2;


    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2, int k) {
        adj1 = getAdj(edges1), adj2 = getAdj(edges2);
    
        sums1 = vector(edges1.size() + 1, vector(edges1.size() + 1, 0));
        sums2 = vector(edges2.size() + 1, vector(edges2.size() + 1, 0));

        dfs1(0, 0, adj1, sums1);  dfs2(0, 0, adj1, sums1);
        dfs1(0, 0, adj2, sums2); dfs2(0, 0, adj2, sums2);

        for_each(sums1.begin(), sums1.end(), [] (vector<int>& arr) { convertToPrefixSumInPlace(arr); });
        for_each(sums2.begin(), sums2.end(), [] (vector<int>& arr) { convertToPrefixSumInPlace(arr); });

        vector<int> out(edges1.size() + 1, 0);
        for (int i = 0; i < edges1.size() + 1; i++) {
            int best = 1;
            for (int j = 0; j < edges2.size() + 1; j++) {
                int res = sums1[i][min(k, (int) edges1.size())] + ((k - 1 < 0) ? 0 : sums2[j][min(k - 1, (int) edges2.size())]);
                best = max(best, res);
            }
            out[i] = best;
        }
        printRes(sums1);
        return out;
    }
};

int main() {
    Solution sol;
    vector<vector<int>> edges1 = {{0,1},{0,2},{2,3},{2,4}};
    vector<vector<int>> edges2 = {{0,1},{0,2},{0,3},{2,7},{1,4},{4,5},{4,6}};

    vector<int> ans = sol.maxTargetNodes(edges1, edges2, 2);
    for (int x : ans) cout << x << " "; cout << endl;
    
}