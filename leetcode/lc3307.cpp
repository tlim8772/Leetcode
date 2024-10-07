#include <bits/stdc++.h>
using ll = long long;
using namespace std;

// k is 1 indexed

class Solution {
public:
    vector<ll> indices;

    ll findMaxPow(ll k) {
        ll i = 1;
        while (i < k) i <<= 1;
        return i;
    }

    void fillIndices(ll k, ll i) {
        if (i == 1) indices.push_back(1);
        else {
            
            (k > (i >> 1)) ? fillIndices(k - (i >> 1), i >> 1) : fillIndices(k, (i >> 1));
            indices.push_back(k);
        }
    }

    char kthCharacter(long long k, vector<int>& operations) {
        fillIndices(k, findMaxPow(k));
        int c = 0;
        for (ll i = 0; i < 48 && i < operations.size() && k > (1ll << i); i ++) {
            // if the indice tracked changes after doubling, this means the char needs to be modified
            // if k > (1 << i), then i cannot be the final operations index
            if (indices[i] != indices[i + 1] && operations[i] == 1) {
                c ++;
                c %= 26;
            }
        }
        return 'a' + c;
    }
};

int main() {
    Solution sol;
    /*sol.fillIndices(10, 16);
    for (int i = 0; i < sol.indices.size(); i ++) {
        cout << sol.indices[i] << endl;
    }*/
   vector<int> ops = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    cout << sol.kthCharacter(100000000000000, ops) << endl;

}