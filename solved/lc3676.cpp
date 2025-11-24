#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// monotone stack, but I can't really explain
// we want a monotone decreasing stack
// we process from left to right
// for current elem, we pop elem that are < curr elem until we encounter an elem > curr elem
// ans for this elem is popCount - 1 + !stack.empty()

// why ? suppose we are at index curr
// for every elem in the stack, it is the maximum elem from [its index, curr - 1], (remember all elems are distinct)
// so if elem < curr elem it is a valid end, except for the 1st one and it is directly next to curr 
// (why? because we just added it)
// once we find an elem > curr elem we can stop, this is the final valid left index
// then push curr elem inside

class Solution {
public:
    long long bowlSubarrays(vector<int>& nums) {
        ll cnt = 0;
        vector<int> stack;

        for (int n : nums) {
            int popCount = 0;
            while (!stack.empty() && stack.back() < n) {
                stack.pop_back();
                popCount++;
            }

            if (popCount > 0) {
                //cout << stack.size() << endl;
                cnt += popCount - 1 + !stack.empty();  // at this point, stack size is the number of valid left endings
            }
            stack.push_back(n);

        }

        return cnt;
        
    }

    
};

int main() {
    Solution sol;
    vector<int> nums = {2,5,3,1,4};
    cout << sol.bowlSubarrays(nums) << endl;
}