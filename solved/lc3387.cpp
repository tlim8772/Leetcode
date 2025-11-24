#include <bits/stdc++.h>
using namespace std;

// since each day forms a tree (questions says no cycle in the graph for each day)
// for day 1, we dfs1 from initCurrency to get the rate for all other currency
// same for day 2, then we join the results eg result1_ci * result_ci2 if day 1 ends and day 2 starts with currency ci.
// we cannot only use edges in 1 day only, because edges in a day do not form a cycle.

class Solution {
public:
    unordered_map<string, vector<tuple<string,double>>> adj1, adj2;
    unordered_map<string, double> resultsDay1, resultsDay2;

    void processAdj(vector<vector<string>>& pairs1, vector<double>& rates1, vector<vector<string>>& pairs2, vector<double>& rates2) {
        for (int i = 0; i < pairs1.size(); i++) {
            vector<string>& p = pairs1[i];
            adj1[p[0]].emplace_back(p[1], rates1[i]);
            adj1[p[1]].emplace_back(p[0], 1 / rates1[i]);
        }

        for (int i = 0; i < pairs2.size(); i++) {
            vector<string>& p = pairs2[i];
            adj2[p[0]].emplace_back(p[1], rates2[i]);
            adj2[p[1]].emplace_back(p[0],  1 / rates2[i]);
        }
    }

    void dfs(string curr, string p, double val, unordered_map<string, vector<tuple<string, double>>>& adj, unordered_map<string, double>& results) {
        results[curr] = val;
        
        for (auto& [nextCurr, rate] : adj[curr]) {
            if (nextCurr == p) continue;
            dfs(nextCurr, curr, val * rate, adj, results);
        }
    }
    
    double maxAmount(string initialCurrency, vector<vector<string>>& pairs1, vector<double>& rates1, vector<vector<string>>& pairs2, vector<double>& rates2) {
        processAdj(pairs1, rates1, pairs2, rates2);
        dfs(initialCurrency, initialCurrency, 1.0, adj1, resultsDay1);
        dfs(initialCurrency, initialCurrency, 1.0, adj2, resultsDay2);

        double best = 1.0;

        for (auto& [curr, res] : resultsDay1) {
            if (!resultsDay2.contains(curr)) continue;
            best = max(best, res / resultsDay2[curr]);
        }

        return best;
    }
};

int main() {
    Solution sol;
    string initCurr = "EUR";
    vector<vector<string>> pairs1 = {{"EUR","NGN"}};
    vector<double> rates1 = {9};
    vector<vector<string>> pairs2 = {{"EUR", "NGN"}};
    vector<double> rates2 = {6};
    cout << sol.maxAmount(initCurr, pairs1, rates1, pairs2, rates2) << endl;
}