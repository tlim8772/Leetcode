#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1e9 + 7;

/*
use dp to get all numbers whose bit representation is a subset of bitmask.
let dp(x, i) = # of elems in nums whose bit representation is a subset of x and also whose 
bits from [0:i) matches x exactly.
here index 0 means leftmost (most significant) bit

if x[i] = 0, dp(x, i) = dp(x, i + 1)
if x[i] = 1, dp(x, i) = dp(x - (1 << len - i - 1), i + 1) + dp(x, i + 1)

now to reduce the OR value, have to remove all occurences of a bit.
eg want to remove bit at pos 1 (from the right), we have to find # of elems s.t elem & 10 = 0
or elem is a subset of 101 (suppose max # of bits is 3).

we also have to do this for bit mask 001, 010, 100, 110, 101, 011, 111 and finally do 
principle of inclusion and exclusion.

have to do bottom up dp with state space saving + other constant time optimisations.
time complexity is O(20 * 2^20)
*/

int bit_length(int x) {
    int c = 0;
    for (int y = x; y > 0; y >>= 1) {
        c++;
    }
    return c;
}

int bit_count(int x) {
    int c = 0;
    for (int y = x; y > 0; y >>= 1) {
        c += y & 1;
    }
    return c;
}

vector<int> store(100001, -1);
// exp <= 100000
ll pow_2(int exp) {
    if (store[exp] != -1) return store[exp];
    if (exp == 0) return 1;
    if (exp % 2 == 0) {
        ll ans = pow_2(exp >> 1);
        return store[exp] = (ans * ans) % MOD;
    }

    ll ans = pow_2((exp - 1) >> 1);
    return store[exp] = (ans * ans * 2) % MOD;
}

//vector<int> store(1 << 20, -1), temp(1 << 20, -1);

class Solution {
public:
    vector<int> store, temp;
    unordered_map<int,int> freqs;
    int max_bits = 0;

    int to_pos(int x, int i) {
        return x * max_bits + i;
    }

    void bottom_up_dp() {
        for (int bm = 0; bm < (1 << max_bits); bm++) {
            store[bm] = freqs[bm];
        }

        for (int i = max_bits - 1; i >= 0; i--) {
            for (int x = 0; x < (1 << max_bits); x++) {
                int gap = max_bits - i - 1;
                bool is_set = (x >> gap) & 1;
                if (!is_set) {
                    temp[x] = store[x];
                } else {
                    int put1 = store[x];
                    int put0 = store[x - (1 << gap)];
                    temp[x] = put1 + put0;
                }
            }
            store = temp;
        }
    }
    
    int countEffective(vector<int>& nums) {
        max_bits = bit_length(*max_element(nums.begin(), nums.end()));
        store = temp = vector(1 << max_bits, 0);
        
        int all_or = 0;
        for (int x : nums) all_or |= x;

        for (int x : nums) {
            freqs[x]++;
        }

        bottom_up_dp();

        ll sum = 0;
        for (int bm = all_or; bm > 0; bm = (bm - 1) & all_or) {
            int sign = (bit_count(bm) % 2 == 1) ? 1 : -1;
            int inv = ~bm & ((1 << max_bits) - 1);
            int cnt = store[inv];
            
            sum += sign * pow_2(cnt);
            sum %= MOD;
        }

        return (sum < 0) ? sum + MOD : sum;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1,2,3};
    cout << bit_count(5) << endl;
    cout << sol.countEffective(nums) << endl;
}