#include <bits/stdc++.h>
using namespace std;
using state = tuple<int,int,bool>;
using res = tuple<bool,int,bool>;

// tree dp, but the state is more interesting.
// dp(v, i, p): means we are at node v, checking ith child, and node v has current parity p.
// if p = 0, dont flip v's value, if p = 1 then flip v's value.

// res(bool,int,bool) means 
// 1. can fulfil requirements
// 2. min cost to fulfil requirements
// 3. whether edge (v, c) is flipped or not


struct TupleHash {
    std::size_t operator()(const std::tuple<int, int, bool>& t) const noexcept {
        std::size_t h1 = std::hash<int>{}(std::get<0>(t));
        std::size_t h2 = std::hash<int>{}(std::get<1>(t));
        std::size_t h3 = std::hash<bool>{}(std::get<2>(t));

        std::size_t seed = h1;
        seed ^= h2 + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);
        seed ^= h3 + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);
        return seed;
    }
};

struct PairHash {
    std::size_t operator()(const std::pair<int,int>& p) const noexcept {
        std::size_t h1 = std::hash<int>{}(p.first);
        std::size_t h2 = std::hash<int>{}(p.second);

        // Boost-style hash combine
        std::size_t seed = h1;
        seed ^= h2 + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);
        return seed;
    }
};


class Solution {
public:
    int n;
    unordered_map<tuple<int,int,bool>, tuple<bool,int,bool>, TupleHash> store;
    vector<vector<int>> adj;
    string start, target;
    unordered_map<pair<int,int>, int, PairHash> edge_to_idx;

    void make_adj(int n, const vector<vector<int>>& edges) {
        adj = vector(n, vector<int>());
        for (const auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        /*for (auto& arr : adj) {
            sort(arr.begin(), arr.end());
        }*/
    }

    void make_edge_to_idx(const vector<vector<int>>& edges) {
        for (int i = 0; i < edges.size(); i++) {
            auto& e = edges[i];
            int a = min(e[0], e[1]), b = max(e[0], e[1]);
            edge_to_idx[{a, b}] = i;
        }
    }

    res dp(int v, int i, bool p, int parent) {
        state s{v, i, p};
        if (store.contains(s)) return store[s];

        const auto& my_adj = adj[v];
       
        if (i == adj[v].size()) {
            if ((start[v] - '0' + p) % 2 == target[v] - '0') {
                return store[s] = {true, 0, false};
            } else {
                return store[s] = {false, 0, false};
            }
        }

        if (my_adj[i] == parent) {
            return dp(v, i + 1, p, parent);
        }


        // no flip
        auto child_res = dp(my_adj[i], 0, 0, v);
        auto my_next_res = dp(v, i + 1, p, parent);
        
        bool success = get<0>(child_res) && get<0>(my_next_res);
        int cost = get<1>(child_res) + get<1>(my_next_res);

        // flip 
        auto child_res_flip = dp(my_adj[i], 0, 1, v);
        auto my_next_res_flip = dp(v, i + 1, (p + 1) % 2, parent);
        
        bool success_flip = get<0>(child_res_flip) && get<0>(my_next_res_flip);
        int cost_flip = 1 + get<1>(child_res_flip) + get<1>(my_next_res_flip);

        if (!success && !success_flip) {
            return store[s] = {false, 0, false};
        } else if (success && !success_flip) {
            return store[s] = {true, cost, false};
        } else if (!success && success_flip) {
            return store[s] = {true, cost_flip, true};
        } else if (cost <= cost_flip) {
            return store[s] = {true, cost, false};
        } else {
            return store[s] = {true, cost_flip, true};
        }
    }

    void reconstruct(int v, int i, int p, int parent, vector<int>& stack) {
        auto& my_adj = adj[v];
        if (i == my_adj.size()) return;
        
        if (my_adj[i] == parent) {
            return reconstruct(v, i + 1, p, parent, stack);
        }

        state s{v, i, p};
        res r = store[s];
        int c = my_adj[i];
        pair<int, int> edge = {min(v, c), max(v, c)};

        if (get<2>(r)) {
            stack.push_back(edge_to_idx[edge]);
        }

        reconstruct(c, 0, get<2>(r), v, stack);
        reconstruct(v, i + 1, (p + get<2>(r)) % 2, parent, stack);

    }

 
    vector<int> minimumFlips(int n, vector<vector<int>>& edges, string start, string target) {
        this->n = n;
        make_adj(n, edges);
        this->start = start, this->target = target;
        make_edge_to_idx(edges);

        dp(0, 0, 0, -1);
        if (res r = store[{0, 0, 0}]; !get<0>(r)) {
            return {-1};
        }

        vector<int> stack;
        
        reconstruct(0, 0, 0, -1, stack);
        sort(stack.begin(), stack.end());
        
        return stack;
    }
};

int main() {
    Solution sol;

    int n = 7;
    vector<vector<int>> edges = {{0,1},{1,2},{2,3},{3,4},{3,5},{1,6}};
    string start = "0011000";
    string target = "0010001";

    vector<int> ans = sol.minimumFlips(n, edges, start, target);
    for (int x : ans) cout << x << " ";
    cout << endl;


}