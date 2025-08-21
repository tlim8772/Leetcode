#include <bits/stdc++.h>
using namespace std;

// greedy
// the heaviest person is paired with the heaviest person 2 s.t p1 + p2 <= limit

class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        multiset<int> weights(people.begin(), people.end());
        
        int cnt = 0;
        while (weights.size() > 0) {
            auto backPtr = --weights.end(); 
            auto backWeight = *backPtr;
            auto remainder = limit - backWeight;
            
            // cannot use backPtr anymore
            weights.erase(backPtr);

            if (weights.size() > 0) {
                // +1, so that we do not have to deal with the case where the value is equal to remainder
                auto lowerPtr = weights.lower_bound(remainder + 1);
                if (lowerPtr != weights.begin()) {
                    weights.erase(--lowerPtr);
                }
            }

            cnt++;
        }

        return cnt;
    }
};