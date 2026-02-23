#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = (ll) 1e9 + 7;

// consider aabbccdd, change to (a,2) (b,2) (c,2) (d,2)
// want to find how many strings s.t each block has at least 1 char remaining
// and the total length is >= k.
// for each block we can remove 0, 1, 2, ... cnt - 1, so have cnt choices.
// total # of strings is cnt_0 * cnt_1 ... cnt_k.
// we find # of strings with length <= k - 1.

// dp(i, left) means how many ways to get a string of size exactly left from block i onwards.
// also you have to take at least 1 from each block.
// we have to do prefix dp, so means bottom up.
// dp(i, left) we can take 1, 2, 3 ... min(block_size, left)
// means we check dp(i + 1, left - 1), dp(i + 1, left - 2) ... dp(i + 1, left - min(block_size, left))

// dp(i, 0) = 0 if i < blocks.size() else 1.

// the annoying thing is handling the modulo.

// another optimisation is to notice we must take 1 char from each block.
// so if k == 2000 and we have 5 * 10^5 blocks, we can return 0 quickly.

vector<int> collect(const string& s) {
    vector<int> out;
    for (int p = 0; p < s.size();) {
        char c = s[p];
        int start = p;
        while (p < s.size() && s[p] == c) p++;
        out.push_back(p - start);
    }
    return out;
}

vector<ll> make_prefix(const vector<ll>& arr) {
    ll sum = 0;
    vector<ll> out;  
    out.reserve(arr.size());
    for (ll x : arr) {
        sum = sum + x;
        sum %= MOD;
        out.push_back(sum);
    }
    return out;
}

ll range_sum(int l, int r, const vector<ll>& arr) {
    ll ans = arr[r] - (l == 0 ? 0 : arr[l - 1]);
    ans %= MOD;
    if (ans < 0) ans += MOD;
    return ans;
}

class Solution {
public:
    
    // left == k - 1
    ll dp(const vector<int>& blocks, int left) {
        // handle i = n - 1
        vector<ll> prev_row(left + 1, 0);
        for (int l = 1; l <= min(left, blocks.back()); l++) {
            prev_row[l] = 1;
        }
        
        vector<ll> prefix_sums = make_prefix(prev_row);
        
        for (int i = blocks.size() - 2; i > -1; i--) {
            vector<ll> my_row(left + 1, 0);

            if (blocks.size() - i > left) {
                prefix_sums = make_prefix(my_row);
                break;
                // we can return immediately, because num of remaining blocks > left, so 
                // there is no way of getting a string of length == left, as we must
                // take >= 1 char from each block.
            }

            for (int l = 1; l <= left; l++) {
                // can take 1, 2, 3 ... blocks[i] chars.
                int right = l - 1;
                int left = max(0, l - blocks[i]);
                ll sum = range_sum(left, right, prefix_sums);
                my_row[l] = sum;
            }

            prefix_sums = make_prefix(my_row);
        }

        // now for i == 0, get the result for l = 1, 2, 3 ... k - 1
        return range_sum(1, left, prefix_sums);

    }
    int possibleStringCount(string word, int k) {
        vector<int> blocks = collect(word);
        /*for (int b : blocks) cout << b << " ";
        cout << endl;*/

        ll total_ways = 1;
        for (int b : blocks) {
            total_ways *= b;
            total_ways %= MOD;
        }

        ll invalid_ways = dp(blocks, k - 1);
        
        total_ways -= invalid_ways;
        total_ways %= MOD;
        if (total_ways < 0) total_ways += MOD;
        
        return total_ways;

    }
};

int main() {
    Solution sol;
    string word = "aaabbb";
    int k = 3;

    int ans = sol.possibleStringCount(word, k);
    cout << ans << endl;

}