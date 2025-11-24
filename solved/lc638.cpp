#include <bits/stdc++.h>
using namespace std;

// simple backtracking, take or not take curr offer

class Solution {
public:
    
    int helper(vector<int>& needs, int idx, vector<vector<int>>& offers, vector<int>& prices) {
        if (idx == offers.size()) {
            int sum = 0;
            for (int i = 0; i < needs.size(); i ++) sum += needs[i] * prices[i];
            return sum;
        } else {
            bool canUse = true;
            for (int i = 0; i < needs.size(); i ++) canUse = canUse && (needs[i] >= offers[idx][i]);

            int opt1 = 1e6;
            if (canUse) {
                for (int i = 0; i < needs.size(); i ++) needs[i] -= offers[idx][i];
                opt1 = offers[idx][needs.size()] + helper(needs, idx, offers, prices);

                for (int i = 0; i < needs.size(); i ++) needs[i] += offers[idx][i];
            }

            int opt2 = helper(needs, idx + 1, offers, prices);

            return min(opt1, opt2);
        }
    }



    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        return helper(needs, 0, special, price);
    }
};

int main() {
    Solution sol;

    vector<int> price = {2,5};
    vector<vector<int>> special = {{3,0,5},{1,2,10}};
    vector<int> needs = {3,2};

    cout << sol.shoppingOffers(price, special, needs) << endl;
}