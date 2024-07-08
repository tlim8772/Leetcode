#include <vector>
#include <iostream>
#include <stdio.h>
using namespace std;
#define MAX 14

// used hint that max squares is <= max(n, m), but I cannot prove why hehe
class Solution {
public:
   vector<int> stack;
   vector<vector<int>> store;

    void addPath() {
        store.push_back(vector(stack));
    }

    void helper(vector<vector<int>> adjList, int node, int dest) {
        stack.push_back(node);
        if (node == dest) {
            addPath();
        } else {
            for (int i = 0; i < adjList[node].size(); i ++) {
                helper(adjList, adjList[node][i], dest);
            }
        }
        stack.pop_back();
    }

    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        helper(graph, 0, graph.size() - 1);
        return store;
    }

    
};

int main() {
    Solution sol;
    
}
