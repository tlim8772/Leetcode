#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// simple stack problem.
// insert new element, then while can merge the top 2 elems, pop the 2 elems and insert the new one.

class Solution {
public:
    vector<long long> mergeAdjacent(vector<int>& nums) {
        vector<ll> stack;
        for (int x : nums) {
            stack.push_back(x);
            while (stack.size() >= 2) {
                ll a = stack[stack.size() - 2], b = stack[stack.size() - 1];
                if (a != b) break;
                stack.pop_back();
                stack.pop_back();
                stack.push_back((ll) a * 2);
            }
        }
        return stack;
    }
};