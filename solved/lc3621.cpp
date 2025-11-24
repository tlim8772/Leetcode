#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// digit dp;
// n is at most 10^15 <= 2^50, so at most 50 bits
// dp(isFirstDigit, digitLeft, accu)
// means how many ways to make a digit with pop count = k
// with digitLeft to choose from and accu 1 bits already used on the left



class Solution {
public:
    // 10^15 = 2^50, so only need to store 1 to 50
    vector<int> popCountStore = vector(51, 0);

    int k;
    vector<ll> store = vector<ll>(2 * 51 * 51, -1);

    int bits(ll n) {
        int cnt = 0;
        while (n > 0) {
            cnt += n & 1;
            n >>= 1;
        }
        return cnt;
    }

    
    void processPopCount() {
        popCountStore[1] = 0;
        for (int i = 2; i <= 50; i++) {
            int cnt = bits(i);
            popCountStore[i] = 1 + popCountStore[cnt];
        }
    }

    int popCount(ll n) {
        int cnt = bits(n);
        return 1 + popCountStore[cnt];
    }

    string convertToBinaryString(ll n) {
        if (n == 0) return "0";

        string s;
        while (n > 0) {
            char c = (n & 1) ? '1' : '0';
            s.append(1, c);
            n >>= 1;
        }
        reverse(s.begin(), s.end());
        return s;
    }

   

    int coor(int isFirst, int left, int accu) {
        return isFirst * 51 * 51 + left * 51 + accu;
    }

    // cannot call this if total num of digits is 1
    // because then returns 1 and not 0
    ll dp(bool isFirst, int left, int accu) {
        int pos = coor(isFirst, left, accu);
        if (store[pos] != -1) return store[pos];
        
        if (left == 0) {
            int popCount = 1 + popCountStore[accu];
            return store[pos] = (popCount == k);
            
        } 

        if (isFirst) {
            return store[pos] = dp(false, left - 1, accu + 1);
        } else {
            ll take0 = dp(false, left - 1, accu);
            ll take1 = dp(false, left - 1, accu + 1);
            return store[pos] = take0 + take1;
        }
    }

    ll helper(ll n, int k) {
        
        
        string binString = convertToBinaryString(n);

        ll ans = 0;
        for (int i = 1; i < binString.size(); i++) {
            if (i == 1) {
                ans += (k == 0);
            } else {
                ans += dp(true, i, 0);
            }
            
        }

        //cout << ans << endl;
        
        int accu = 1; // again, 1st char is always 1
        for (int i = 1; i < binString.size(); i++) {
            if (binString[i] == '0') continue;
            
            // must consider the case we put 0
            ans += dp(false, binString.size() - i - 1, accu);
            accu++;
        }

        // check for n too
        if (n == 1) {
            ans += (k == 0);
        } else {
            ans += (1 + popCountStore[accu] == k);
        }

        return ans;
    }
    
    long long popcountDepth(long long n, int k) {
        processPopCount();
        this->k = k;
        ll ans = helper(n, k);
        return ans;
    }
};

int main() {
    Solution sol;
    cout << sol.popcountDepth(1,0) << endl;;

}