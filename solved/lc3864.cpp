#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// simple algorithm.
// if len is odd, return the cost.
// if len is even, we can split or not split.
// if we split, recurse.
// time complexity is T(n) = O(n) + 2T(n/2)

class Solution {
public:
    ll helper(int start, int end, const string& s, int encCost, int flatCost) {
        int len = end - start + 1;
        int ones = 0;
        for (char c : s.substr(start, end - start + 1)) ones += (c == '1');
        
        if (len % 2 == 1) return (ones == 0) ? flatCost : (ll) len * ones * encCost;
        
        ll nosplit = (ones == 0) ? flatCost : (ll) len * ones * encCost;
        int m = (start + end) >> 1;
        ll split = helper(start, m, s, encCost, flatCost) + helper(m + 1, end, s, encCost, flatCost);
        return min(nosplit, split);



    }
    
    long long minCost(string s, int encCost, int flatCost) {
        return helper(0, s.size() - 1, s, encCost, flatCost);
    }
};

int main() {
    Solution sol;
    string s = "1010";
    int encCost = 2, flatCost = 1;
    ll ans = sol.minCost(s, encCost, flatCost);
    println("Ans: {}", ans);
}