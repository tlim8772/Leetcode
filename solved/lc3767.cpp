#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// sort tech1[i] - tech2[i] in decreasing order.
// we take the top k differences, (i.e these are the ones we do with technique 1)
// the rest we take the max of (tech1[i], tech2[i])

// score is sum of tech2 + (tech1[i] - tech2[i]) chosen.
// to maximise, these, we take the top k, but some of the pairs might be -ve.

class Solution {
public:
    long long maxPoints(vector<int>& technique1, vector<int>& technique2, int k) {
        vector<pair<int,int>> store;
        for (int i = 0; i < technique1.size(); i++) {
            store.emplace_back(technique1[i], technique2[i]);
        }

        sort(store.begin(), store.end(), [] (pair<int,int>& p1, pair<int,int>& p2) {
            int diff1 = p1.first - p1.second;
            int diff2 = p2.first - p2.second;
            return diff1 > diff2;
        });

        ll score = 0;
        for (int i = 0; i < k; i++) {
            score += store[i].first;
        }

        for (int i = k; i < store.size(); i++) {
            score += max(store[i].first, store[i].second);
        }

        return score;
    }
};