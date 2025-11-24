#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1000000007;

// only have 10 prime numbers <= 30.
// only need to consider numbers with 'good' prime factorisation (i.e each prime power is 1).
// the key here is that we do not do dp on the array, because it is too long at 10^5.
// we do dp on the 'good' numbers.
// eg, the sequence we got is 2, 3, 5, 7,
// the number of subarrays is freq[2] * freq[3] * freq[5] * freq[7].
// basically we can choose any index i s.t nums[i] = 2, nums[i] = 3 ...
// the only way to arrange is 1, in increasing order.
// i.e we create the 'sorted' good subarray, then count all possible permutations.
// then is just simple take, no take dp.

// BUT, need to be careful of 1. We can take any number of 1s, but for the other 'good' numbers,
// we can only take 1 of each.
// which means for the dp, we must start at bitmask 1, not 0.
// then for the final answer, we multiply by 2^(# of 1s).

vector<int> primes = {2,3,5,7,11,13,17,19,23,29};

int get_bitset(int n) {
    int bm = 0;
    for (int i = 0; i < primes.size(); i++) {
        int cnt = 0;
        while (n % primes[i] == 0) {
            n /= primes[i];
            cnt++;
        }
        
        if (cnt > 1) return -1;
        else if (cnt == 0) continue;
        bm |= (1 << i);
    }
    return bm;
}

vector<int> get_good_num_freq(const vector<int>& nums) {
    vector<int> out(1024, 0);
    for (int x : nums) {
        int bm = get_bitset(x);
        if (bm == -1) continue;
        out[bm] += 1;
    }
    return out;
}

ll pow_2_mod(int p) {
    if (p == 0) return 1;
    if (p % 2 == 0) {
        ll ans = pow_2_mod(p / 2);
        return (ans * ans) % MOD;
    }
    return (2 * pow_2_mod(p - 1)) % MOD;
}


class Solution {
public:
    vector<int> freqs;
    vector<ll> store;

    int to_pos(int bm, int curr) {
        return bm * 1024 + curr;
    }

    ll dp(int bm, int curr) {
        if (curr == 1024) return (bm == 0) ? 0 : 1;

        int pos = to_pos(bm, curr);
        if (store[pos] != -1) return store[pos];

        ll notake = dp(bm, curr + 1);
        ll take = ((bm & curr) != 0 || freqs[curr] == 0) ? 0 : freqs[curr] * dp(bm | curr, curr + 1);
        return store[pos] = (notake + take) % MOD;
    }
    int numberOfGoodSubsets(vector<int>& nums) {
        freqs = get_good_num_freq(nums);
        store = vector<ll>(1024 * 1024, -1);

        ll ans = dp(0, 1);
        ans *= pow_2_mod(freqs[0]);
        ans %= MOD;
        return ans;

    }
};

int main() {
    Solution sol;

    vector<int> nums = {5,10,1,26,24,21,24,23,11,12,27,4,17,16,2,6,1,1,6,8,13,30,24,20,2,19};
    cout << sol.numberOfGoodSubsets(nums) << endl;
}