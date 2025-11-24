#include <bits/stdc++.h>
using ll = long long;
using namespace std;

// binary lifting
// to avoid O(nlog^2n) we binary search the dist inside the binary lifting

// 1. find the lca, then find the path len
// since path is from u to v, we split into 2 sections [u, lca] and [lca, v]
// binary search these 2 sections

class Solution {
public:
    int MAX_POW;
   
    vector<vector<pair<int,ll>>> binVals; // store 2^i parent and dist, if parent = -1, means overshoot, dist is invalid
    vector<int> depths;
    vector<ll> distFromRootVals;
    
    vector<vector<pair<int,int>>> adj;

    void dfs(int v, int p, int dist, int depth, ll distFromRoot) {
        depths[v] = depth;
        distFromRootVals[v] = distFromRoot;
        
        if (v != p) {
            binVals[v][0] = {p, dist};

            for (int pow = 1; pow <= MAX_POW; pow++) {
                auto [parI, dist] = binVals[v][pow - 1];

                if (parI == -1) break;
                binVals[v][pow].first = binVals[parI][pow - 1].first;
                binVals[v][pow].second = binVals[v][pow - 1].second 
                    + binVals[parI][pow - 1].second;
            }
        }

        for (const auto& c : adj[v]) {
            if (c.first == p) continue;
            dfs(c.first, v, c.second, depth + 1, distFromRoot + c.second);
        }
    }

    int jump(int v, int j) {
        int node = v;
        int pow = 0;
        while (pow <= MAX_POW && j > 0) {
            if (j & 1) {
                node = binVals[node][pow].first;
                if (node == -1) break;
            }
            j >>= 1;
            pow++;
        }
        return node;
    }

    int getLca(int u, int v) {
        if (depths[u] < depths[v]) swap(u, v);
        u = jump(u, depths[u] - depths[v]);

        if (u == v) return u;

        for (int pow = MAX_POW; pow >= 0; pow--) {
            int parentU = binVals[u][pow].first, parentV = binVals[v][pow].first;
            if (parentU != parentV) {
                u = parentU, v = parentV;
            }
        }

        return binVals[u][0].first;
    }

    int get1stNode(int u, int lca, ll pathLen) {
        ll median = (pathLen + 1) >> 1; // the actual median, +1 to account for odd numbers
        
        int currNode = u;
        ll currLen = 0;
        
        // we jump the largest possible pow of 2
        // if it exceeds lca or exceed median length, continue
        // else start jumping from this node
        // hence, curr node is always < median length (impt invariant)
        for (int pow = MAX_POW; pow >= 0; pow--) {
            auto [node, dist] = binVals[currNode][pow];
            if (node == -1 || depths[node] < depths[lca] || currLen + dist >= median) continue;

            currNode = node;
            currLen += dist;
        }
        
        if (currNode == lca || binVals[currNode][0].first == -1) {
            return currNode;
        } else {
            return binVals[currNode][0].first; // due to invariant, ans is the direct parent of currNode
        }
    }

    int getLastNode(int v, int lca, ll pathLen) {
        ll median = (pathLen + 1) >> 1;
        ll limit = pathLen - median;
        
        int currNode = v;
        ll currLen = 0;
        
        for (int pow = MAX_POW; pow >= 0; pow--) {
            auto [node, dist] = binVals[currNode][pow];
            if (node == -1 || depths[node] < depths[lca] || currLen + dist > limit) continue;

            currNode = node;
            currLen += dist;
        }
        
        return currNode;
    }

    int query(int u, int v) {
        int lca = getLca(u, v);
        ll pathLen = distFromRootVals[u] + distFromRootVals[v] - 2 * distFromRootVals[lca];

        int left = get1stNode(u, lca, pathLen);
        int right = getLastNode(v, lca, pathLen);

        if (left == lca && right == lca) {
            return lca;
        } else if (left != lca) {
            return left;
        } else {
            return right;
        }
    }

    










    void processEdges(const vector<vector<int>>& edges) {
        for (const vector<int>& e  : edges) {
            adj[e[0]].push_back(pair{e[1], e[2]});
            adj[e[1]].push_back(pair{e[0], e[2]});
        }
    }

    vector<int> findMedian(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        MAX_POW = (int) floor(log2(n));
        binVals = vector(n, vector(MAX_POW + 1, pair{-1, -1LL}));
        depths = vector(n, -1);
        distFromRootVals = vector<ll>(n, 0);

        adj = vector(n, vector<pair<int,int>>());

        processEdges(edges);
        dfs(0, 0, 0, 0, 0);

        /*for (vector<pair<int,int>> arr : binVals) {
            for (pair<int,int> p : arr) {
                printf("%d:%d ", p.first, p.second);
            }
            cout << endl;
        }*/

        vector<int> ans;
        for (const vector<int>& q : queries) {
            int res = query(q[0], q[1]);
            ans.push_back(res);
        }

        return ans;
    }


};

int main() {
    Solution sol;

    int n = 7;
    vector<vector<int>> edges = {{0,1,1},{0,2,1},{1,3,1},{1,4,1},{2,5,1},{2,6,1}};
    vector<vector<int>> queries = {{2,3}};

    sol.findMedian(n, edges, queries);
}