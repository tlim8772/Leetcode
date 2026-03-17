#include <bits/stdc++.h>
using namespace std;

// basically, we do 2 dp
// 1st dp is to determine for substring s[i:j+1] the cost to make it palindrome.
// 2nd dp is to partition with minimum total cost.


struct Hash {
    size_t operator()(const pair<int, int>& p) const {
        return ((size_t) p.first << 32) + p.second;
    }
};

class Solution {
public:
    unordered_map<pair<int, int>, int, Hash> store1;
    unordered_map<pair<int, int>, int, Hash> store2;

    int dp1(int i, int j, const string& s) {
        if (i >= j) return 0;
        if (store1.contains({i, j})) return store1[{i, j}];

        int add1 = s[i] != s[j];
        return store1[{i, j}] = add1 + dp1(i + 1, j - 1, s); 
    }

    int dp2(int i, int k, const string& s) {
        if (i == s.size()) {
            return (k == 0) ? 0 : 101;
        }
        if (s.size() - i < k) return 101;
        if (store2.contains({i, k})) return store2[{i, k}];

        int best = 101;
        for (int j = i; j < s.size(); j++) {
            best = min(best, dp1(i, j, s) + dp2(j + 1, k - 1, s));
        }
        return store2[{i, k}] = best;

    }


    int palindromePartition(string s, int k) {
        return dp2(0, k, s);
    }
};

int main() {
    Solution sol;
    string s = "aabbc";
    int k = 3;
    int ans = sol.palindromePartition(s, k);
    println("Ans: {}", ans);

}