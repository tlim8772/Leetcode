#include <bits/stdc++.h>
using namespace std;

// build dag, then use kahn algorithm
// basically start with nodes with 0 indegree, then prune onwards

template <typename It>
void print(It begin, It end) {
    for (It s = begin; s != end; s++) {
        cout << *s << endl;
    }
}

class Solution {
public:
    unordered_map<string, unordered_set<string>> adj;
    unordered_map<string, int> counts;
    unordered_set<string> isRecipe;
    vector<string> canReach;

    void processAdj(const vector<string>& recipes, const vector<vector<string>>& ingredients) {
        for (int i = 0; i < recipes.size(); i++) {
            const string r = recipes[i];
            const vector<string>& in = ingredients[i];
            
            counts[r] = 0;
            isRecipe.insert(r);

            for (const string& s : in) {
                // actually no need, ingredients[i] has no duplicate values
                if (adj[s].count(r) == 0) counts[r]++; 
                adj[s].insert(r);
            }
        }
    }

    void getCanReachRecipes(const vector<string>& supplies) {
        queue<string> q{supplies.begin(), supplies.end()};

        while (!q.empty()) {
            string s = q.front(); q.pop();
            if (isRecipe.contains(s)) {
                canReach.push_back(s);
            }

            const unordered_set<string>& nexts = adj[s];
            for (auto it = nexts.begin(); it != nexts.end(); it++) {
                const string& s2 = *it;
                counts[s2]--;
                if (counts[s2] == 0) q.push(s2);
            }
        }
    }

    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        processAdj(recipes, ingredients);
        getCanReachRecipes(supplies);
        return canReach;
    }
};

int main() {
    Solution sol;

    vector<string> recipes = {"bread"};
    vector<vector<string>> ingredients = {{"yeast", "flour"}};
    vector<string> supplies = {"yeast", "flour", "corn"};

    vector<string> ans = sol.findAllRecipes(recipes, ingredients, supplies);
    print(ans.begin(), ans.end());


}