#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// simple add 1 and m to hF, 1 and n to vF then sort both vectors.
// since we want a square, we find all possible gaps between all pairs of (hF[i], hF[j]) 
// and also for (vF[i], vF[j]).
// then we find the largest gap that is present in both sets.

class Solution {
public:
    int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences) {
        hFences.push_back(1);
        hFences.push_back(m);
        sort(hFences.begin(), hFences.end());
        
        vFences.push_back(1);
        vFences.push_back(n);
        sort(vFences.begin(), vFences.end());

        unordered_set<int> hs, vs;

        for (int i = 0; i < hFences.size(); i++) {
            for (int j = i + 1; j < hFences.size(); j++) {
                hs.insert(hFences[j] - hFences[i]);
            }
        }

        for (int i = 0; i < vFences.size(); i++) {
            for (int j = i + 1; j < vFences.size(); j++) {
                vs.insert(vFences[j] - vFences[i]);
            }
        }

        
        ll best = -1;
        for (int x : hs) {
            if (vs.contains(x)) {
                best = max(best, (ll) x * x);
            }
        }

        return best % (int) (1e9 + 7);
    }
};