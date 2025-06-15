#include <bits/stdc++.h>
using namespace std;

// key to O(n^2*1024) is to see a subtree as simply a set, the order of processing is not important
// in a linear take, no take dp, the TC is O(n*1024) and the order of elems does not matter
// so do this for every elem, we get O(n*n*1024)
// we flatten the tree into a array, such that a subtree is a contigous subarray
// for bitmask, 0 means digit is not used

class Solution {
public:
    const int MOD = 1e9 + 7;
    int MAX_BM = 1024;
    int N;
    
    vector<vector<int>> adj;
    vector<int> bmVals;
    vector<int> vals;

    vector<pair<int,int>> startEndPos; // the range [start, end] that represents the subtree
    vector<int> flatTree;

    unordered_map<int,int> store;

    inline int coor(int s, int e, int bm) {
        return s * N * MAX_BM + e * MAX_BM + bm;
    }

    // returns -1 if a digit occurs > 1
    int numToBm(int n) {
        int bm = 0;
        while (n > 0) {
            int lastDigit = n % 10;
            if (bm & (1 << lastDigit)) return -1;
            bm |= (1 << lastDigit);
            n /= 10;
        }
        return bm;
    }

    void processAdj(const vector<int>& par) {
        for (int i = 0; i < par.size(); i++) {
            if (par[i] == -1) continue;
            adj[par[i]].push_back(i);
        }
    }

    void processBmForNodes(const vector<int>& vals) {
        for (int i = 0; i < vals.size(); i++) {
            bmVals[i] = numToBm(vals[i]);
        }
    }

    void flatten(int node) {
        startEndPos[node].first = flatTree.size();
        flatTree.push_back(node);
        
        for (int c : adj[node]) {
            flatten(c);
        }
        
        startEndPos[node].second = flatTree.size() - 1;
    }

    int dp(int s, int e, int bm) {
        if (s > e) return 0;

        int pos = coor(s, e, bm);
        if (store.contains(pos)) return store[pos];

        int take = 0, notake = 0;
        int myBm = bmVals[flatTree[s]];
        bool canTake = myBm != -1 && (myBm & bm) == 0;

        if (canTake) {
            take = (vals[flatTree[s]] + dp(s + 1, e, bm | myBm)) % MOD;
        }

        notake = dp(s + 1, e, bm);
        store[pos] = max(take, notake);
        return store[pos];

    }

    int goodSubtreeSum(vector<int>& vals, vector<int>& par) {
        N = vals.size();
        
        
        adj = vector(N, vector<int>());
        bmVals = vector(N, 0);
        this->vals = vals;

        startEndPos = vector(N, pair(-1, -1));
        


        processBmForNodes(vals);
        processAdj(par);
        flatten(0);


        int sum = 0;
        for (int i = 0; i < N; i++) {
            pair<int,int> startEnd = startEndPos[i];
            int ans = dp(startEnd.first, startEnd.second, 0);

            sum = (sum + ans) % MOD;
        }

        return sum;

       
        
    }
};

int main() {
    Solution sol;
    vector<int> vals = {17,57,77,27};
    vector<int> par = {-1,0,1,1};

    cout << sol.goodSubtreeSum(vals, par) << endl;
}