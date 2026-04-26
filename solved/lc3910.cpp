#include <bits/stdc++.h>
using namespace std;

// at most 13 nodes, so just enumerate all subsets and check.

vector<vector<int>> get_adj(int n, const vector<vector<int>>& edges) {
    auto out = vector(n, vector<int>());
    for (auto e : edges) {
        out[e[0]].push_back(e[1]);
        out[e[1]].push_back(e[0]);
    }
    return out;
}

int get_node_sum(const vector<int>& nodes, int bm) {
    int s = 0;
    for (int i = 0; i < nodes.size(); i++) {
        if ((bm >> i) & 1) s += nodes[i];
    }
    return s;
}

bool is_connected(const vector<vector<int>>& adj, int bm) {
    assert(bm != 0);

    function<int(int,int)> dfs = [&, seen = unordered_set<int>()] (int n, int p) mutable -> int {
        seen.insert(n);
        int sum = 1;
        for (auto c : adj[n]) {
            if (c == p || seen.contains(c) || !((bm >> c) & 1)) continue;
            sum += dfs(c, n);
        }
        return sum;
    };

    int first = countr_zero<unsigned int>(bm);
    int ans = dfs(first, first);
    return ans == popcount<unsigned int>(bm);
}


class Solution {
public:
    int evenSumSubgraphs(vector<int>& nums, vector<vector<int>>& edges) {
        int cnt = 0;
        int n = nums.size();
        auto adj = get_adj(n, edges);
        for (int bm = 1; bm < (1 << n); bm++) {
            int node_sum = get_node_sum(nums, bm);
            if (node_sum % 2 != 0) continue;
            bool connected = is_connected(adj, bm);
            cnt += connected;
        }
        return cnt;
    }
};

int main() {
    Solution sol;

    vector<int> nums = {1, 0, 1};
    vector<vector<int>> edges = {{0,1}, {1,2}};

    int ans = sol.evenSumSubgraphs(nums, edges);
    cout << ans << endl;
}