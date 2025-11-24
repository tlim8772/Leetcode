#include <bits/stdc++.h>
using namespace std;

// interesting question, key is to work backwards
// basically 1st index not 0, has to be 1
// and we definitely have a coin of value (idx + 1)
// now we remove for all ways to create denominations, the number of ways using at least 1 of the former coin
// it is simply numWays[i] - numWays[i - (idx + 1)]

// invariant at iteration i
// nnumWays[i] is numer of ways to create that denonimation using coin i, discovered in this round
// and larger coins

class Solution {
public:
    int find1stNonZeroIdx(const vector<int>& numWays) {
        for (int i = 0; i < numWays.size(); i++) {
            if (numWays[i] > 0) return i;
        }
        return numWays.size();
    }
    
    vector<int> findCoins(vector<int>& numWays) {
        vector<int> currCoins;

        while (1) {
            int idx = find1stNonZeroIdx(numWays); //numWays[idx] is always 1, if idx is valid
            
            if (idx >= numWays.size()) break;
            if(numWays[idx] != 1) {
                return {};
            }
            
            

            currCoins.push_back(idx + 1);
            vector<int> store = numWays;
            for (int i = idx + 1; i < numWays.size(); i++) {
                if (numWays[i] == 0) {
                    // this means no valid coins
                    if (store[i - (idx + 1)] != 0) {
                        return {};
                    } else {
                        continue;
                    }
                }
                numWays[i] -= store[i - (idx + 1)];
            }
            numWays[idx] = 0;
        }

        return currCoins;
    }
};

int main() {
    Solution sol;

    vector<int> ways = {1,2,3,4,15};
    vector<int> coins = sol.findCoins(ways);
    for (int c : coins) cout << c << " ";
    cout << endl;
}