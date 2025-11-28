#include <bits/stdc++.h>
using namespace std;

/*
build a trie to obtain maximum x xor s where s is an element of a set.
do dfs, trie contains all element from root to node, so we insert the node's value,
then answer all queries on this node. 
recurse on children.
once done, remove the node's value from the trie.
*/

struct Node {
    int cnt = 0;
    array<Node*, 2> nexts;

    Node() {
        nexts = {nullptr, nullptr};
    }
};

struct Trie {
    vector<unique_ptr<Node>> node_store;
    
    int LEN = 0;
    Node* root = make_node();

    Trie(int max_bit_length): LEN(max_bit_length) {}

    Node* make_node() {
        node_store.emplace_back(new Node());
        return node_store.back().get();
    }

    void insert(int v) {
        Node *curr = root;
        curr->cnt++;
        for (int i = LEN - 1; i > -1; i--) {
            int dg = (v >> i) & 1;
            if (curr->nexts[dg] == nullptr) curr->nexts[dg] = make_node();
            curr = curr->nexts[dg];
            curr->cnt++;
        }
    }

    int max_xor_result(int v) {
        Node *curr = root;
        int sum = 0;
        for (int i = LEN - 1; i > -1; i--) {
            int dg = (v >> i) & 1;
            if (curr->nexts[1 - dg] != nullptr && curr->nexts[1 - dg]->cnt > 0) {
                sum += (1 << i);
                curr = curr->nexts[1 - dg];
            } else if (curr->nexts[dg] != nullptr && curr->nexts[dg]->cnt > 0) {
                curr = curr->nexts[dg];
            } else {
                return sum;
            }
        }
        return sum;
    }

    void remove(int v) {
        Node *curr = root;
        curr->cnt--;
        for (int i = LEN - 1; i > -1; i--) {
            int dg = (v >> i) & 1;
            curr = curr->nexts[dg];
            curr->cnt--;
        }
    }
};

class Solution {
public:
    int root = -1;
    vector<vector<int>> adj;
    vector<vector<pair<int,int>>> my_queries;
    vector<int> results;
    Trie trie{18};

    void make_adj(vector<int>& parents) {
        adj = vector(parents.size(), vector<int>());
        for (int i = 0; i < parents.size(); i++) {
            if (parents[i] == -1) {
                root = i;
                continue;
            }

            adj[i].push_back(parents[i]);
            adj[parents[i]].push_back(i);
        }
    }

    void make_my_queries(int n, vector<vector<int>>& queries) {
        my_queries = vector(n, vector<pair<int,int>>());
        for (int i = 0; i < queries.size(); i++) {
            auto& q = queries[i];
            my_queries[q[0]].emplace_back(q[1], i);
        }
    }

    void dfs(int v, int p) {
        //cout << v << endl;
        trie.insert(v);
        
        for (auto [val, i] : my_queries[v]) {
            results[i] = trie.max_xor_result(val);
        }
        
        for (int c : adj[v]) {
            if (c == p) continue;
            dfs(c, v);
        }
        
        trie.remove(v);
    }
    vector<int> maxGeneticDifference(vector<int>& parents, vector<vector<int>>& queries) {
        make_adj(parents);
        make_my_queries(parents.size(), queries);
        results = vector(queries.size(), -1);
        dfs(root, root);
        return results;
    }
};

int main() {
    /*Trie trie{4};
    trie.insert(10);
    trie.insert(12);
    cout << trie.max_xor_result(5) << endl;

    trie.remove(10);
    cout << trie.max_xor_result(5) << endl;

    trie.insert(9);
    cout << trie.max_xor_result(5) << endl;
    */

    Solution sol;
    vector<int> parents = {-1,0,1,1};
    vector<vector<int>> queries = {{0,2},{3,2},{2,5}};
    vector<int> ans = sol.maxGeneticDifference(parents, queries);
    for (int a : ans) cout << a << " ";
    cout << endl;
}