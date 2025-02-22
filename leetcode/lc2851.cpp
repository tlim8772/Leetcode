#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Pair = tuple<int, int>;

// string t must be a rotated version of string s. So we need to find the indices such that
// if we make s start at indice i, it becomes t.
// We use z-algo. We append 2 string s together, and in the 1st half, find which indice match t.

// next, each op can make string s start from indice i, no matter what rotation string s is at now
// means we have a complete graph of n vertices numbered 0 to n - 1.
// find number of walks of length k from 0 to i
// due to symmetry, there is only 2 cases. num of walks of length k from i to j, i == j and i != j
// so for length k, if k is even we find path from i to i and i to j of length k/2
// for i to i the walk of k / 2 can end either at i or j so we have 2 cases i to i to i or i to j to i.
// for i to j, walk of k / 2 have 3 cases, i to i to j, i to j to j, i to k to j.
// if k is odd we find result for k - 1, then we calculate for each case repectively

class Solution {
    static constexpr int MOD = 1e9 + 7;

    int mult(int a, int b) {
        ll ans = (ll) a * b;
        return ans % MOD;
    }

    int add(int a, int b) {
        return (a + b) % MOD;
    }

public:
    Pair countWays(int n, ll k) {
        if (k == 1) {
            return {0, 1};
        } else if (k % 2 == 0) {
            Pair wish = countWays(n, k / 2);
            
            // i to i
            int same = mult(get<0>(wish), get<0>(wish)); // i to i to i
            same = add(same, mult(n - 1, mult(get<1>(wish), get<1>(wish)))); // i to j to i

            // i to j
            int diff = mult(get<0>(wish), get<1>(wish)); // i to i to j
            diff = add(diff, mult(get<1>(wish), get<0>(wish))); // i to j to j
            diff = add(diff, mult(n - 2, mult(get<1>(wish), get<1>(wish)))); // i to k to j

            return {same, diff};
        } else {
            Pair wish = countWays(n, k - 1);

            int same = mult(n - 1, get<1>(wish)); // i to j to i
            
            int diff = get<0>(wish); // i to i then j
            diff = add(diff, mult(n - 2, get<1>(wish))); // i to k then j
            
            return {same, diff};
        }
    }

    vector<int> zAlgo(const string& s) {
        vector<int> res(s.size(), 0);
        res[0] = s.size();

        int l = 1;
        int r = -1;
        for (int i = 1; i < s.size(); i ++) {
            if (i > r) {
                l = i;
                int ptr = 0;
                while (ptr < s.size() - i && s[ptr] == s[i + ptr]) ptr ++;
                res[i] = ptr;
                r = i + ptr - 1;
            } else if (res[i - l] + i - 1 < r) {
                res[i] = res[i - l];
            } else {
                int ptr = r - i + 1;
                while (ptr < s.size() - i && s[ptr] == s[i + ptr]) ptr ++;
                res[i] = ptr;
                l = i;
                r = i + ptr - 1;
            }
        }
        return res;

    }

    vector<int> findStartIndices(const string& s, const string& t) {
        string res = t + "$" + s + s;
        vector<int> zRes = zAlgo(res);
        vector<int> out;
        
        for (int i = 0; i < s.size(); i ++) {
            if (zRes[t.size() + 1 + i] == t.size()) out.push_back(i);
        }
        return out;
    }

    int numberOfWays(string s, string t, long long k) {
        Pair ways = (k == 1) ? Pair{0, 1} : countWays(s.size(), k);
        vector<int> startIndices = findStartIndices(s, t);

        int sum = 0;
        for (int i : startIndices) {
            if (i == 0) sum = add(sum, get<0>(ways));
            else sum = add(sum, get<1>(ways));
        }

        return sum;

    }
    
    
    

};

int main() {
    Solution sol;
    //Pair p = sol.countWays(10, 4);
    //cout << get<0>(p) << " " << get<1>(p) << endl;

    string s = "ababab";
    string t = "ababab";

    cout << sol.numberOfWays(s, t, 6);
    
}