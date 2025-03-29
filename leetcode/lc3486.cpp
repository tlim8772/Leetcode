#include <bits/stdc++.h>
using namespace std;

// sliding window on path from root to currNode
// key here is to maintain invariants judicously
// no need to store arr of MyStartPos (start pos of node i best range) and 
// MyDoubleVal (value that occurs twice for node i best range)
// as we store it in the function variable itself when we call dfs on node i

struct Best {
    int len, numNodes;

    bool operator<(const Best& b2) {
        if (len != b2.len) {
            return len < b2.len;
        } else {
            return numNodes < b2.numNodes;
        }
    }
};

bool operator<(const Best& b1, const Best& b2) {
    if (b1.len == b2.len) {
        return b1.numNodes > b2.numNodes;
    }
    return b1.len < b2.len;
}

// store result of binary search
struct Pair {
    int i, v;
};

Pair geq(vector<int>& arr, int val) {
    int s = 0, e = arr.size() - 1;
    while (s < e) {
        int m = (s + e) >> 1;
        if (arr[m] >= val) e = m;
        else s = m + 1;
    }
    return (arr[s] >= val) ? Pair{s, arr[s]} : Pair{-1, -1};
}

Pair leq(vector<int>& arr, int val) {
    int s = 0, e = arr.size() - 1;
    while (s < e) {
        int m = (s + e + 1) >> 1;

        if (arr[m] <= val) s = m;
        else e = m - 1;
    }
    return (arr[s] <= val) ? Pair{s, arr[s]} : Pair{-1, -1};
}

class Solution {
public:
    int N;
    vector<vector<Pair>> adj; // Pair.i is node, Pair.v is edge value
    vector<int> nodeVals;
    
    unordered_map<int, vector<int>> posOfVals; // for each node val eg 10, store the depth in which it appears
    vector<int> prefixSum;
    vector<int> currNodes;
    
    Best best = {-1, 0};

    void makeAdj(int n, vector<vector<int>>& edges) {
        adj = vector(n, vector<Pair>());
        for (vector<int>& e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
            adj[e[1]].push_back({e[0], e[2]});
        }
    }


    // invariant is that path [start, depth - 1] is valid
    // so either all nodes values are distinct, or only 1 node value is repeated
    void dfs(int n, int par, int depth, int start, int currDouble, int len) {
        //currNodes.push_back(n);
        prefixSum.push_back(len);
        
        int nodeVal = nodeVals[n];
        vector<int>& myValArr = posOfVals[nodeVal];
        myValArr.push_back(depth);
        
        Pair l = geq(myValArr, start);
        Pair r = leq(myValArr, depth);
        int num = r.i - l.i + 1;
        
        int oldCurr = currDouble;
        int oldStart = start;
        if (num == 1) {
            // case 1: only 1 occurence of this nodeVal
            // pass, no changes to start and currDouble
        } else if (num == 2) {
            // case 2: 2 occurence of this nodeVal, either currently path already has a repeated nodeVal or not
            if (currDouble == -1) {
                currDouble = nodeVal;
            } else if (currDouble != nodeVal) {
                Pair lold = geq(posOfVals[currDouble], start);
                if (l.v + 1 < lold.v + 1) {
                    start = l.v + 1;
                } else {
                    start = lold.v + 1;
                    currDouble = nodeVal;
                }
                
            } else {
                assert(false); // should not go here
            }
        } else {
            // case 3: 3 occurences of this nodeVal, no change to currDouble as currDouble = nodeVal
            start = l.v + 1;
        }

        best = max(best, {len - prefixSum[start], depth - start + 1});
        //if (len - prefixSum[start] == 10) printf("%d %d\n", currNodes[start], currNodes[depth]);
        //printf("%d %d\n", currNodes[start], currNodes[depth]);
        
        for (Pair& p : adj[n]) {
            if (p.i == par) continue;
            dfs(p.i, n, depth + 1, start, currDouble, len + p.v);
        }

        prefixSum.pop_back();
        myValArr.pop_back();
        //currNodes.pop_back();
    }

    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        N = nums.size();
        makeAdj(N, edges);
        this->nodeVals = nums;

        dfs(0, 0, 0, 0, -1, 0);
        return {best.len, best.numNodes};
    }



    

};

int main() {
    Solution sol;

    vector<vector<int>> edges = {{2,1,7},{0,3,10},{4,0,3},{1,5,5},{4,1,5},{4,6,1}};
    vector<int> nums {2,4,2,2,4,4,1};

    vector<int> ans = sol.longestSpecialPath(edges, nums);
    printf("%d %d\n", ans[0], ans[1]);  
}

