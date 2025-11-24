#include <bits/stdc++.h>
using namespace std;

// a num is a multiple of 3 iff the sum of its digit is a multiple of 3

struct Pair {
    int res, take, d, m;
};

Pair invalidPair = {-999999, -1, -1, -1};

class Solution {
public:
    
    // router(d, m) return Pair(res, take, d, m) 
    // res: max number of digits we can take starting at digit d and below, with modulo m
    // take: how many digits we take for d, and 
    // (d, m): next state to go
    // at each digit we only need to consider cnt, cnt - 1, cnt - 2, as the modulo 3 will cycle over
    unordered_map<int, unordered_map<int, Pair>> dp;
    vector<int> digitCnts;

    void countDigits(vector<int>& digits) {
        digitCnts = vector(10, 0);
        for (int d : digits) digitCnts[d] += 1;
    }
    

    bool contains(int d, int m) {
        return dp.contains(d) && dp[d].contains(m);
    }

    int helper(int d, int m) {

        if (d == -1) {
            return (m == 0) ? 0 : -999999;
        } else if (contains(d, m)) {
            return dp[d][m].res;
        } else {
            int cnt = digitCnts[d];
            int best = -1;
            Pair next = invalidPair;
            
            for (int i = 0; i < 3; i ++) {
                if (cnt - i < 0) break;
                int res = cnt - i + helper(d - 1, (m + (cnt - i) * d) % 3);

                if (res > best) {
                    best = res;
                    next = {res, cnt - i, d - 1, (m + (cnt - i) * d) % 3};
                }
            }

            dp[d][m] = next;
            return next.res;
        }
    }

    Pair init() {
        int best = -1;
        Pair p = invalidPair;
        
        for (int d = 9; d >= 0; d --) {
            if (digitCnts[d] == 0) continue;

            if (d == 0) {
                int res = 1;
                if (res > best) {
                    best = res;
                    p = {1, 1, -1, 0};
                }
            } else {
                int cnt = digitCnts[d];
                for (int i = 0; i < 3; i ++) {
                    if (cnt - i < 1) break; // have to take at least 1 digit
                    int res = cnt - i + helper(d - 1, ((cnt - i) * d) % 3);
                   
                    if (res > best) {
                        best = res;
                        p = {res, cnt - i, d - 1, ((cnt - i) * d) % 3};
                    }
                }
            }
        }
        
        return p;
    }

    string buildNum(Pair p) {
        string out = "";
        while (true) {
            if (p.take > 0) out.append(p.take, p.d + 1 + '0');

            if (!contains(p.d, p.m)) {
                break;
            } else {
                p = dp[p.d][p.m];
            }
        }
        return out;
    }


    string largestMultipleOfThree(vector<int>& digits) {
        countDigits(digits);
        Pair bestP = init();

        //printf("%d %d %d %d\n", bestP.res, bestP.take, bestP.d, bestP.m);
        string s = buildNum(bestP);
        return s;
    }
};

int main() {
    Solution sol;
    vector<int> arr = {0,0,0,1};
    cout << sol.largestMultipleOfThree(arr) << endl;
}