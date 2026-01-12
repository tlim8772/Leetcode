#include <bit>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
using ui = unsigned int;
using ll = long long;

// suppose we want to increment n s.t the AND of the subset is target.
// let n = 1010, target = 0100.
// clearly target must be a subbset of n.
// n must be 1100.
// the idx that matters is the 1st index from the left s.t n[i] = 0 and target[i] = 1.
// here it is index 1 (from the left).
// the # of ops is 0b100 - 0b010 = 2.

// we get this by taking ~n & target, then using __builtin_clz to get the number of leading 0s.
// then we do bitshift to get the mask.
// the only 1 bit in ~n & target is at the 1st index from the left s.t n[i] = 0 and target[i] = 1.

// for the problem, we greedily try to set the largest possible bit.
// if the smallest m results is <= k, then we must set that bit to 1.
// if not is has to be 0.
// then we proceed to the next bit, keeping the result for the previous bits.

ui helper(ui n, ui target) {
    ui temp = ~n & target; 
    if (temp == 0) return 0;
    
    ui leading_0 = __builtin_clz(temp);
    ll mask = (1LL << (32 - leading_0)) - 1;
    return (target & mask) - (n & mask);
}

class Solution {
public:
    int maximumAND(vector<int>& nums, ll k, int m) {
        ll sum = 0;
        multiset<int> store;
        ui target = 0;
        
        // start from 30, not 31, because 1 << 31 is undefined, max int is (1 << 31) - 1
        for (int i = 30; i > -1; i--) {
            sum = 0;
            store.clear();
            target |= (1 << i);
            
            for (int x : nums) {
                ll res = helper(x, target);
                store.insert(res);
                sum += res;
                if (store.size() > m) {
                    ll rm = *(--store.end());
                    sum -= rm;
                    store.erase(--store.end());
                }
            }

            if (sum > k) target &= ~(1 << i);
        }

        return target;
    }
};



int main() {
    Solution sol;
    
    vector<int> nums = {17, 28, 8};
    int k = 13, m = 3;

    int ans = sol.maximumAND(nums, k, m);
    
    cout << ans << endl;

    //cout << helper(3, 1U << 31) << endl;
    
}