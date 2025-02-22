#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;

class UnionFind {
public:
    vector<int> parent;
    vector<int> weight;

    UnionFind(int size): parent(size, 0), weight(size, 1) {
        for (int i = 0; i < size; i ++) {
            parent[i] = i;
        }
    }

    int find(int i) {
        if (parent[i] == i) {
            return i;
        } else {
            int p = find(parent[i]);
            parent[i] = p;
            return p;
        }
    }

    void union_node(int i, int j) {
        int pI = find(i);
        int pJ = find(j);
        if (pI != pJ) {
            if (weight[pJ] > weight[pI]) {
                union_node(j, i);
            } else {
                weight[i] += weight[j];
                parent[pJ] = pI;
            }
        }
    }
};

class Solution {
public:
    vector<vector<int>>* adjList;
    vector<int>* result;
    UnionFind* uf;

    void process(vector<int>& parents) {
        adjList = new vector<vector<int>>(parents.size(), vector<int>());
        for (int i = 0; i < parents.size(); i ++) {
            int p = parents[i];
            if (p != -1) {
                (*adjList)[i].push_back(p);
                (*adjList)[p].push_back(i);
            }
        }
    }

    int minGene(int node, int parent, vector<int>& nums) {
        int minGeneMissing = (nums[node] == 1) ? 2 : 1;
        vector<int>& nbrs = (*adjList)[node];
        for (int i = 0; i < nbrs.size(); i ++) {
            if (nbrs[i] != parent) {
                int missing = minGene(nbrs[i], node, nums);
                minGeneMissing = max(minGeneMissing, missing);
                uf->union_node(nums[node], nums[nbrs[i]]);
            }
        }
        int pNode = uf->find(nums[node]);
        // even though for each node, potentially iterate through O(n), but amortised is O(1)
        // because once a number is passed, it is never passes again, because all gene values in the tree are distinct
        // it cannot be that in another subtree, we go through that number again, because that number is not in 
        // that subtree, so will stop at that number or lesser
        for (int i = minGeneMissing; i <= 100000; i ++) {
            int pI = uf->find(i);
            if (pI != pNode) {
                (*result)[node] = i;
                return i;
            }
        }
        (*result)[node] = 100001;
        return 100001;
    }

    vector<int> smallestMissingValueSubtree(vector<int>& parents, vector<int>& nums) {
        uf = new UnionFind(100001);
        result = new vector<int>(parents.size(), 0);
        process(parents);
        minGene(0, 0, nums);
        return *result;
    }
};

int main() {
    vector<int> parents = {-1,2,3,0,2,4,1};
    vector<int> nums = {2,3,4,5,6,7,8};
    Solution sol;
    vector<int>&& ans = sol.smallestMissingValueSubtree(parents, nums);
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
}
