#include <bits/stdc++.h>
using namespace std;

// sort the array and group equal elements together.
// eg [1,1,1,2,2,3,3,3] -> [(1, 3), (2, 1), (3, 3)].
// for each pair (value, quantity) we can take 0, 1, 2, ... quantity.
// this ensures each set we find that sums to target is different.
// do dp.
// after the dp, we can build all solutions by traversing the DAG.

vector<int> build_set(const vector<pair<int,int>>& sol) {
    vector<int> out;
    for (auto [v, q] : sol) {
        for (int i = 0; i < q; i++) out.push_back(v);
    }
    return out;
}

vector<pair<int,int>> process(vector<int>& candidates) {
    sort(candidates.begin(), candidates.end());
    
    vector<pair<int,int>> out;
    int curr_val = candidates[0], curr_cnt = 0;
    for (int i = 0; i < candidates.size(); i++) {
        if (candidates[i] != curr_val) {
            out.emplace_back(curr_val, curr_cnt);
            curr_val = candidates[i];
            curr_cnt = 1;
        } else {
            curr_cnt++;
        }
    }
    out.emplace_back(curr_val, curr_cnt);

    return out;
}



class Solution {
public:
    vector<vector<int>> store;
    vector<pair<int,int>> elems;
    
    vector<vector<int>> set_store;
    vector<pair<int,int>> stack;

    bool dp(int i, int target) {
        if (i == elems.size()) {
            return target == 0;
        }

        int& ans = store[i][target];
        if (ans != -1) return ans;

        ans = false;
        auto [v, q] = elems[i];
        for (int c = 0; c <= q; c++) {
            if (target < v * c) break;
            ans = ans || dp(i + 1, target - v * c);
            if (ans) return true;
        }
        return false;
    }

    void build(int i, int target) {
        if (target == 0) {
            set_store.push_back(build_set(stack));
            return;
        }

        if (i == elems.size()) return;

        if (!dp(i, target)) return;

        auto [v, q] = elems[i];
        for (int c = 0; c <= q; c++) {
            if (target < v * c || !dp(i + 1, target - v * c)) continue;
            
            if (c > 0) stack.emplace_back(v, c);
            build(i + 1, target - v * c);
            if (c > 0) stack.pop_back();
        }
    }



    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        elems = process(candidates);
        store = vector(elems.size(), vector(target + 1, -1));

        build(0, target);
        reverse(set_store.begin(), set_store.end());
        return set_store;
    }
};

int main() {
    Solution sol;
    vector<int> candidates = {10,1,2,7,6,1,5};
    int target = 8;
    vector<vector<int>> res = sol.combinationSum2(candidates, target);

    for (auto& v : res) {
        for (int x : v) cout << x << " ";
        cout << endl;
    }
}