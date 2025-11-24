#include <bits/stdc++.h>
using namespace std;

// let n be representable in k bits
// then we can make every number from 1 to (1 << (k + 1)) - 1
// as long we have a number that is 2^(k - 1), easy to prove
// 1st number is (1 << k)
// now check each bit, if it is 1, 2nd num bit is 1, 3rd num bit is 0,
// if it is 0, both 2nd num and 3rd nu bit is 1
// we can also make 0 by choosing 3 of the same value

class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();
        int bits = (int) floor(log2(n)) + 1;

        if (n == 1) {
            return 1;
        } else if (n == 2) {
            return 2;
        } else {
            return 1 << bits;
        }
    }
};