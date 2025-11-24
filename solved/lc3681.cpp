#include <bits/stdc++.h>
using namespace std;

// problem reduces to finding maximum xor bby taking a subset of elements
// build a xor basis by doing gaussian elimination
// invariant of xor basis build, the vector form a triangular matrix
// eg (1,0,1,1) (0,1,1,0) (0,0,1,1) (0,0,0,1)
// when adding a new num (hence a new vector) we reduce the bits from left to right, if there is a remainder
// add it in 

// eg given the former basis add (1,1,0,0)
// after 1st vector (0,1,1,1)
// after 2nd vector (0,0,0,1)
// don't take 3rd vector as nnum will increas

// to find maximum xor, just xor from hightest valued vector 
// if value increase, take it else skip
// if decrease, mean the ith bit that this vector 'controls' is already set
// taking it will only decrease
//  we must start with the highest valued vector

class Solution {
public:
    int maxXorSubsequences(vector<int>& nums) {
        vector<int> basis = {nums[0]}; // basis is sorted in decreasing order
        for (int i = 1; i < nums.size(); i++) {
            int n = nums[i];
            for (int b : basis) {
                n = min(n, n ^ b);
            }
            if (n != 0) {
                basis.push_back(n);
                sort(basis.begin(), basis.end(), greater<int>());
            }
        }

        int ma = 0;
        for (int b : basis) {
            ma = max(ma, ma ^ b);
        }

        return ma;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {5,2};

    cout << sol.maxXorSubsequences(nums) << endl;
    
}