#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

// simple small to large merging + offline processing of queries
// we can use unique_ptr instead of shared_ptr
// learn about cpp policy based data str



template<typename T>
using ordered_set = tree<
    T, 
    null_type, 
    std::less<T>, 
    rb_tree_tag, 
    tree_order_statistics_node_update>;


// cannot use unique_ptr, as mySet (see dfs2) still has ownership when I call the function
// so t1 here (where mySet will be passed into) is a copy construct or copy assign (don't know) 
// which is invalid
template <typename T>
shared_ptr<ordered_set<T>> merge(shared_ptr<ordered_set<T>> t1, shared_ptr<ordered_set<T>> t2) {
    if (t1->size() < t2->size()) t1.swap(t2); // t1 is the bigger tree

    for (T t : *t2) {
        t1->insert(t);
    }

    return t1;
}

class Solution {
public:
    int N;
    
    vector<vector<int>> myQueries;
    unordered_map<ll, int> myQueryAns;

    vector<vector<int>> adj;

    vector<int> pathXorSums;
    
    // kth from leetcode is 1-indexed
    // kth here is 0-indexed
    inline ll flatten(int node, int kth) {
        return (ll) node * N + kth;
    }

    void processQueries(const vector<vector<int>>& queries) {
        for (const vector<int>& q : queries) {
            myQueries[q[0]].push_back(q[1] - 1);
        }

        for (vector<int>& arr : myQueries) {
            sort(arr.begin(), arr.end());
        }
    }

    void processAdj(const vector<int>& par) {
        for (int i = 0; i < par.size(); i++) {
            if (par[i] == -1) continue;
            adj[par[i]].push_back(i);
        }
    }

    void dfs(int u, int xr, const vector<int>& vals) {
        xr = xr ^ vals[u];
        pathXorSums[u] = xr;
        for (int c : adj[u]) {
            dfs(c, xr, vals);
        }
    }

    shared_ptr<ordered_set<int>>dfs2(int u) {
        shared_ptr<ordered_set<int>> mySet = make_shared<ordered_set<int>>();
        mySet->insert(pathXorSums[u]);

        for (int c : adj[u]) {
            mySet = merge(mySet, dfs2(c));
        }

        const vector<int>& q = myQueries[u];
        for (int kth : q) {
            if (kth >= mySet->size()) break;
            ll coor = flatten(u, kth);
            int ans = *mySet->find_by_order(kth);
            myQueryAns[coor] = ans;
        }

        return mySet;
    }

    

    vector<int> kthSmallest(vector<int>& par, vector<int>& vals, vector<vector<int>>& queries) {
        N = par.size();
        myQueries = vector(N, vector<int>());
        adj = vector(N, vector<int>());
        pathXorSums = vector(N, 0);

        processQueries(queries);
        processAdj(par);
        
        dfs(0, 0, vals);

        dfs2(0);

        vector<int> ans;
        for (const vector<int>& q : queries) {
            ll coor = flatten(q[0], q[1] - 1);
            if (!myQueryAns.contains(coor)) {
                ans.push_back(-1);
            } else {
                ans.push_back(myQueryAns[coor]);
            }
        }

        return ans;

    }
};

int main() {
    Solution sol;

    vector<int> par = {-1,0,1};
    vector<int> vals = {5,2,7};
    vector<vector<int>> queries = {{0,1},{1,2},{1,3},{2,1}};

    vector<int> ans = sol.kthSmallest(par, vals, queries);

    for (int a : ans) {
        cout << a << " ";
    }
    cout << endl;
}