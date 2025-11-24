#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Sum of Subsets dp
// but here instead of sum, we take the max

// let dp(x, i) be the sum of subsets whose bits from 0..i - 1 (FROM THE LEFT) are the same
// if ith bit from the left == 0
// dp(x, i) = dp(x, i + 1)
// else
// we  can set the ith bit to 0, get the result,
// set it to 1, get the result
class Solution {
public:
    int MAX_BITS = 0, LEN = 0, LIMIT;
    
    vector<int> store;

    inline int coor(int bm, int i) {
        return bm * (MAX_BITS + 1) + i;
    }

    int findMaxBit(int n) {
        int cnt = 0;
        while (n > 0) {
            cnt++;
            n >>= 1;
        }
        return cnt;
    }

    long long maxProduct(vector<int>& nums) {
        int MAX = 0;
        for (int x : nums) MAX = max(x, MAX);
        MAX_BITS = findMaxBit(MAX);
        LEN = (MAX_BITS + 1) * (1 << MAX_BITS);
        LIMIT = (1 << MAX_BITS);
        store = vector(LEN, 0);

        unordered_set<int> set(nums.begin(), nums.end());

        for (int bm = 0; bm < LIMIT; bm++) {
            for (int i = MAX_BITS; i >= 0; i--) {
                int pos = coor(bm, i);

                if (i == MAX_BITS) {
                   store[pos] = (set.contains(bm)) ? bm : 0;
                } else {
                    int d = MAX_BITS - i - 1;
                    bool isSet = bm & (1 << d);
                    if (!isSet) {
                        store[pos] = store[coor(bm, i + 1)];
                    } else {
                        int zero = store[coor(bm & ~(1 << d), i + 1)];
                        int one = store[coor(bm, i + 1)];
                        store[pos] = max(zero, one);
                    }
                }
            }
        }

        ll best = 0;
        for (int x : nums) {
            int complement = ~x & ((1 << MAX_BITS) - 1);
            int ans = store[coor(complement, 0)];
            best = max((ll) x * ans, best);
        }

        return best;

    }
};

int main() {
    Solution sol;

    vector<int> nums = {5,6,4};
    cout << sol.maxProduct(nums);
}