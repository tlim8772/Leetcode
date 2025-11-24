#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// output the string result from dfs from the root
// each string result for each node is a contigous subarray
// using string hashing to check if the string is a palindrome in O(1)

struct StringHash {
    ll p = 29, m = 1000000007, inv = 758620695;

    vector<ll> invArr;
    vector<ll> hashVals;

    StringHash(const string& s): invArr(s.size(), 0), hashVals(s.size(), 0) {
        process(s);
    }

    void process(const string& s) {
        ll sum = 0;
        ll pow = 1;
        for (int i = 0; i < s.size(); i ++) {
            sum += ((s[i] - 'a') * pow) % m;
            sum = sum % m;
            
            pow = (pow * p) % m;
            hashVals[i] = sum;
            if (i == 0) {
                invArr[i] = 1;
            } else {
                invArr[i] = (invArr[i - 1] * inv) % m;
            }
        }
    }

    ll hashVal(int l, int r) {
        if (l == 0) return hashVals[r];

        ll ans = (hashVals[r] - hashVals[l - 1]) % m;
        ans = (ans + m) % m;
        ans = (ans * invArr[l]) % m;
        
        return ans;
    }
};

class Solution {
public:
    string store;
    string reverseStore;
    vector<array<int, 2>> myRange;

    vector<vector<int>> adj;

    void processAdj(vector<int>& parent) {
        for (int i = 0; i < parent.size(); i ++) {
            if (parent[i] == -1) continue;
            adj[parent[i]].push_back(i); // adj list for each node already in sorted order
        }
    }

    void helper(int v, string& s) {
        int start = store.size();
        
        for (int c : adj[v]) {
            helper(c, s);
        }
        store.push_back(s[v]);

        int end = store.size() - 1;
        
        myRange[v] = {start, end};
    }

    
    vector<bool> findAnswer(vector<int>& parent, string s) {
        store = "";
        myRange = vector<array<int, 2>>(s.size(), {0,0});
        adj = vector(s.size(), vector<int>());
        processAdj(parent);

        helper(0, s);

        reverseStore = string(store.rbegin(), store.rend());
        StringHash sh1(store), sh2(reverseStore);

        vector<bool> out(s.size(), false);
        for (int i = 0; i < s.size(); i ++) {
            array<int, 2>& range = myRange[i];
            int len = range[1] - range[0] + 1;

            if (len == 1) {
                out[i] = true;
                continue;
            }

            pair<int, int> first, second;
            first = {range[0], range[0] + (len >> 1) - 1};
            second = {range[1] - (len >> 1) + 1, range[1]};
            

            ll h1 = sh1.hashVal(first.first, first.second);
            ll h2 = sh2.hashVal(s.size() - 1 - second.second, s.size() - 1 - second.first);

            out[i] = (h1 == h2);
        }
        return out;
    }
};

/*int main() {
    Solution sol;

    vector<int> parent = {-1,6,10,17,14,4,0,2,13,14,15,16,11,6,2,1,15,1,4};
    string s = "kbkfbhaahggaahfkggh";

    vector<bool> ans = sol.findAnswer(parent, s);
    for (bool b : ans) cout << b << " ";
    cout << endl;
}*/

int main() {
    string s1 = "ahhbgfkgaagkfgbhhak";
    string s2 = "kahhbgfkgaagkfgbhha";

    StringHash sh1(s1), sh2(s2);
    cout << sh1.hashVal(0, 8) << endl;
    cout << sh2.hashVal(1, 9) << endl;
}

