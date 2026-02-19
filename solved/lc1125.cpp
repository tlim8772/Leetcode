#include <bits/stdc++.h>
using namespace std;

// set cover problem.
// important properties of problem.
// 1. people skills are always in req skills.
// 2. a set cover is always possible.
// dp(current bitmask, i) = min length of sufficient team starting from index i onwards with bitmask of skills 
// already taken.

struct Hash {
    size_t operator()(const pair<int, int>& p) const {
        auto [a, b] = p;
        return a + (b << 16);
    }
};

class Solution {
public:
    int max_len;

    // tuple<bool, int, bool> is 
    // {can we cover the state from this state, mininmum length if possible, do we take this subset or not}.
    unordered_map<pair<int, int>, tuple<bool, int, bool>, Hash> store;

    function<int(string)> mapper(vector<string>& req_skills) {
        unordered_map<string, int> store;
        for (string& s : req_skills) {
            store[s] = store.size();
        }

        return [store] (const string& s) { 
            auto it = store.find(s);
            return it == store.end() ? -1 : (*it).second;
        };
    }

    pair<bool, int> dp(int bm, int i, const vector<int>& bit_masks) {
        if (i == bit_masks.size()) {
            return bm != ((1 << max_len) - 1) ? pair<bool, int>{false, 0} : pair<bool, int>{true, 0};
        }

        if (store.contains({bm, i})) {
            auto [a, b, c] = store[{bm, i}];
            return {a, b};
        }

        tuple<bool, int, bool> &ans = store[{bm, i}];
        auto [a1, b1] = dp(bm | bit_masks[i], i + 1, bit_masks);
        b1 += 1;
        
        auto [a2, b2] = dp(bm, i + 1, bit_masks);

        if (!a1 && !a2) {
            ans = {false, 0, 0};
            return {false, 0};
        } else if (a1 && !a2) {
            ans = {true, b1, true};
            return {true, b1};
        } else if (!a1 && a2) {
            ans = {true, b2, false};
            return {true, b2};
        } else {
            if (b1 < b2) {
                ans = {true, b1, true};
                return {true, b1};
            } else {
                ans = {true, b2, false};
                return {true, b2};
            }
        }
    }

    vector<int> rebuild(const vector<int>& bit_masks) {
        vector<int> out;
        int bm = 0, i = 0;
        while (i < bit_masks.size() && bm != (1 << max_len) - 1) {
            auto [can, len, take] = store[{bm, i}];
            if (take) {
                out.push_back(i);
                bm = bm | bit_masks[i];
                i++;
            } else {
                i++;
            }
        }
        return out;
    }

    

    

    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        max_len = req_skills.size();

        auto skill_to_int = mapper(req_skills);
        vector<int> people_bit_masks;
        for (auto& skills : people) {
            int bm = 0;
            for (auto& skill : skills) {
                bm += 1 << skill_to_int(skill);
            }
            people_bit_masks.push_back(bm);
        }
        
        dp(0, 0, people_bit_masks);

        vector<int> ans = rebuild(people_bit_masks);
        
        return ans;
        
    }
};

int main() {
    Solution sol;
    vector<string> req_skills = {"java","nodejs","reactjs"};
    vector<vector<string>> people = {{"java"}, {"nodejs"}, {"nodejs", "reactjs"}};
    vector<int> ans = sol.smallestSufficientTeam(req_skills, people);

    for (int x : ans) cout << x << " ";
    cout << endl;
}