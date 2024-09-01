#include <vector>
#include <iostream>
#include <cmath>
#include <unordered_map>
using namespace std;

void print(vector<int> arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}

void print(vector<vector<int>> arr) {
    for (vector<int> ar : arr) {
        for (int x : ar) {
            cout << x << " ";
        }
        cout << endl;
    }
}


// if let say the 1st, 2nd, 4th, 8th ... parent is invalid (tree not that deep), the entry will be -1
class LCA {
public:
    vector<vector<int>> adjList;
    vector<vector<int>> store;
    vector<int> depths;
    int maxJumps;

    LCA(vector<vector<int>>& adjList) {
        this->adjList = adjList;
        maxJumps = (int) floor(log(adjList.size() - 1) / log(2));
        store = vector(adjList.size(), vector(maxJumps + 1, -1));
        depths = vector(adjList.size(), -1);
        process(0, 0, 0);
    }

    void process(int vtx, int parent, int depth) {
        depths[vtx] = depth;
        
        if (vtx != parent) {
            store[vtx][0] = parent;
            for (int i = 1; i <= maxJumps; i ++) {
                int ithParent = store[vtx][i - 1];
                if (ithParent != -1) store[vtx][i] = store[ithParent][i - 1];
            }
        } 
        
        for (int child : adjList[vtx]) {
            if (child != parent) process(child, vtx, depth + 1);
        }
    }

    // jumps is 1 index, so if want to get immediate parent, jumps is 1
    // as you need 1 jump to get from vtx to immediate parent
    int getIthParent(int vtx, int jumps) {
        int power = 0;
        
        // invariant: vtx is always valid at the start of the iteration
        // i.e. vtx != -1
        while (jumps > 0) {
            int i = jumps & 1;
            if (i == 1) vtx = store[vtx][power];
            if (vtx == -1) break;
            power ++;
            jumps = jumps >> 1;
        }
        return vtx;
    }

    int getLCA(int u, int v) {
        if (depths[u] < depths[v]) return getLCA(v, u);
        
        u = getIthParent(u, depths[u] - depths[v]);
        if (u == v) return u;
        for (int i = maxJumps; i >= 0; i --) {
            // the direct child of the LCA is a fixed height away.
            // Suppose jumping 2^i, and the 2^i parent is the same, means that we never have to jump >= 2^i vertices
            // if not we jump
            // u will never go to -1
            if (store[u][i] != store[v][i]) {
                u = store[u][i];
                v = store[v][i];
            }
        }
        // at the end of the iteration, u, v are direct children of the LCA of the original u, v
        return store[u][0];
    }
};

// get lca
// the minimum number of edges to change is total amount of edges - max(num of edges of the same type)
class Solution {
public:
    vector<vector<int>> edgesSum;
    vector<vector<int>> adjList;
    unordered_map<int, unordered_map<int, int>> edgeWeights;
    LCA *lca;

    void processAdjList(vector<vector<int>> edges, int n) {
        adjList = vector(n, vector<int>());
        for (vector<int>& edge : edges) {
            edgeWeights[edge[0]][edge[1]] = edge[2];
            edgeWeights[edge[1]][edge[0]] = edge[2];
            adjList[edge[0]].push_back(edge[1]);
            adjList[edge[1]].push_back(edge[0]);
        }
    }


    // weight is stored at index weight - 1
    void processEdgesSum(int vtx, int parent, vector<int>& edgeSums) {
        edgesSum[vtx] = edgeSums;
        for (int child : adjList[vtx]) {
            if (child != parent) {
                int weight = edgeWeights[child][vtx];
                edgeSums[weight - 1] ++;
                processEdgesSum(child, vtx, edgeSums);
                edgeSums[weight - 1] --;
            }
        }
    }

    int mininumOp(vector<int>& a, vector<int>& b, vector<int>& parent) {
        int sum = 0;
        int maxEdgeType = 0;
        for (int i = 0; i < 26; i ++) {
            int res = a[i] + b[i] - 2 * parent[i];
            sum += res;
            maxEdgeType = max(maxEdgeType, res);
        }
        return sum - maxEdgeType;
    }

    vector<int> minOperationsQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        if (n == 1) return {0};
        
        processAdjList(edges, n);
        lca = new LCA(adjList);
        
        edgesSum = vector(n, vector<int>());
        vector<int> edgeSums(26, 0);
        processEdgesSum(0, 0, edgeSums);

        vector<int> out;
        for (vector<int>& query : queries) {
            int parent = lca->getLCA(query[0], query[1]);
            //cout << parent << endl;
            //print(edgesSum[query[0]]);
            //print(edgesSum[query[1]]);
            //print(edgesSum[parent]);
            int numOp = mininumOp(edgesSum[query[0]], edgesSum[query[1]], edgesSum[parent]);
            out.push_back(numOp);
        }

        return out;
    }




};


int main() {
   Solution sol;
   int n = 7;
   vector<vector<int>> edges = {{0,1,1}, {1,2,1}, {2,3,1}, {3,4,2}, {4,5,2}, {5,6,2}};
   vector<vector<int>> queries = {{0,3}, {3,6}, {2,6}, {0,6}};

   print(sol.minOperationsQueries(n, edges, queries));

}

/*int main() {
Solution sol;
   int n = 1;
   vector<vector<int>> edges = {};
   vector<vector<int>> queries = {{0,0}};
   print(sol.minOperationsQueries(n, edges, queries));
}*/