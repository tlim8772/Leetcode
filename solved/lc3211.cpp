#include <bits/stdc++.h>
using namespace std;

class Solution {
    vector<string> store;
    string stack;

    void helper(int n, int num0) {
        if (n == 0) store.push_back(stack);
        else if (num0 == 1) {
            stack.push_back('1');
            helper(n - 1, 0);
            stack.pop_back();
        } else {
            stack.push_back('0');
            helper(n - 1, num0 + 1);
            stack.pop_back();

            stack.push_back('1');
            helper(n - 1, 0);
            stack.pop_back();
        }
    }

    vector<string> validStrings(int n) {
        helper(n, 0);
        return store;
    }
};