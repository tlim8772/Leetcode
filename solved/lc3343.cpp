#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class Solution {
public:
    ll MOD = 1000000007;
    int NUM_DIGITS;
    int EVEN_LIM;
    int ODD_LIM;
    int HALF_SUM_LIM;

    vector<int> digitCnt;
    vector<int> prefixCnt;
    vector<vector<vector<ll>>> dp;

    int gcd(int a, int b, int& x, int& y) {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        int x1, y1;
        int d = gcd(b, a % b, x1, y1);
        x = y1;
        y = x1 - y1 * (a / b);
        return d;
    }

    ll modInv(int a, int m) {
        int x, y;
        int g = gcd(a, m, x, y);
        if (g != 1) {
            return -1;
        } else {
            x = (x % m + m) % m;
            return (ll) x;
        }
    }

    ll factorial(int n, int r) {
        ll res = 1;
        for (int i = 0; i < r; i ++) {
            res *= ((n - i) % MOD);
            res %= MOD;
        }
        return res;
    }

    ll ncr(int n, int r) {
        if (r == 0) return 1;

        ll top = factorial(n, r);
        ll bottom = factorial(r, r);
        ll inv = modInv(bottom, MOD);
        
        ll temp = (top * inv) % MOD;
       
        return temp;
    }

    int offset(int diff) {
        return diff + HALF_SUM_LIM;
    }

    void process(string& s) {
        digitCnt = vector(10, 0);
        prefixCnt = vector(10, 0);
        for (char c : s) {
            digitCnt[c - '0'] ++;
        }

        prefixCnt[0] = digitCnt[0];
        for (int i = 1; i < 10; i ++) {
            prefixCnt[i] = digitCnt[i] + prefixCnt[i - 1];
        }
    }

    // we only care the total sum of digits used before idx
    // odd indices used = total indices used - even indices used
    int getNumOddUsed(int idx, int numEvenUsed) {
        return (idx == 0) ? 0 : prefixCnt[idx - 1] - numEvenUsed;
    }
    

    // diff is sum of even indices - sum of odd indices
    // dp(idx, numEvenUsed, diff) means we are now slotting digit idx, we have already numEvenUsed even indices used
    // we have to choose some even indices and odd indices to slot digit idx into, use nCr
    // we can squeeze states
    // from the idx, we know how many digits are used already, and have numEvenUSed, so we know numOddUsed
    
    ll helper(int idx, int numEvenUsed, int diff) {
        if (idx == 10) return (diff == 0 && numEvenUsed == EVEN_LIM) ? 1 : 0;
        else if (abs(diff) > HALF_SUM_LIM) return 0;
        else if (dp[idx][numEvenUsed][offset(diff)] != -1) return dp[idx][numEvenUsed][offset(diff)];
        
        int freq = digitCnt[idx];
        int evencnt = EVEN_LIM - numEvenUsed; // how many even idx slots
        int oddcnt = ODD_LIM - getNumOddUsed(idx, numEvenUsed); // how many odd idx slots

        ll sum = 0;
        for (int i = 0; i <= freq; i ++) {
            int putEven = i;
            int putOdd = freq - i;
            if (putEven > evencnt || putOdd > oddcnt) continue;

            ll res = (ncr(evencnt, putEven) * ncr(oddcnt, putOdd)) % MOD;
            //cout << evencnt << " "<<  putEven << " " << oddcnt << " "  << putOdd << " " << res << endl;
           
            
            res *= helper(idx + 1, numEvenUsed + putEven, diff + (2 * i - freq) * idx);
            res %= MOD;
            
            sum += res;
            sum %= MOD;
        }
        
        dp[idx][numEvenUsed][offset(diff)] = sum;
        return sum;
    }

    int countBalancedPermutations(string num) {
        int sum = accumulate(num.begin(), num.end(), 0, [](int accu, char c) {return accu + c - '0';});
        if (sum % 2 != 0) return 0;

        HALF_SUM_LIM = sum / 2;
        ODD_LIM = num.size() / 2;
        EVEN_LIM = num.size() - ODD_LIM;

        process(num);

        dp = vector(10, vector(EVEN_LIM + 1, vector<ll>(sum + 1, -1)));

        return (int) helper(0, 0, 0);
    }

    
};

int main() {
    Solution sol;
    //cout << sol.ncr(9, 9) << endl;
    int ans = sol.countBalancedPermutations("253");
    cout << ans << endl;
}