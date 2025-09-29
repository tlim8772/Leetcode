#include <bits/stdc++.h>
using namespace std;

// swap [p, q] is an edge.
// the edges form a connected component (CC).
// within each CC, I can rearrange any element to any position. Any configuration is possible.
// proof by induction
// take a spanning tree of the component, and a configuration
// start at the leaf, peform swaps to get the desired element there
// remove the leaf
// by induction on smaller tree, I can achieve any configuration I want

// after that, sort the elems in increasing order, give the minus slots to the smallest elements, 
// positive slots to the bigger elements

// first try can compile and correct wow !!

struct UnionFind {
    vector<int> parents, weights;

    UnionFind(int n): parents(n, 0), weights(n, 1) {
        for (int i = 0; i < n; i++) parents[i] = i;
    }

    int find(int v) {
        return parents[v] == v 
            ? v 
            : parents[v] = find(parents[v]);
    }

    void join(int u, int v) {
        int pu = find(u), pv = find(v);
        int wu = weights[pu], wv = weights[v];
        
        if (pu == pv) return;
        if (wu < wv) join(v, u);
        
        parents[pv] = pu;
        weights[pu] += weights[pv];
    }
};

struct Store {
    int evenSlots = 0, oddSlots = 0;
    vector<int> myNums;
};

class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums, vector<vector<int>>& swaps) {
        int N = nums.size();
        UnionFind uf(N);
        unordered_map<int, Store> store;

        for (const vector<int>& swap : swaps) {
            uf.join(swap[0], swap[1]);
        }

        for (int i = 0; i < N; i++) {
            int p = uf.find(i);
            store[p].myNums.push_back(nums[i]);
            (i % 2 == 0) ? store[p].evenSlots++ : store[p].oddSlots++;
        }

        long long ans = 0;
        for (pair<const int, Store>& entry : store) {
            Store& s = entry.second;
            sort(s.myNums.begin(), s.myNums.end());

            int neg = s.oddSlots, total = s.evenSlots + s.oddSlots;
            for (int i = 0; i < total; i++) {
                if (i < neg) { 
                    ans -= s.myNums[i];
                } else {
                    ans += s.myNums[i];
                }
            }

        }

        return ans;
    }
};