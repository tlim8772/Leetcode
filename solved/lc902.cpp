#include <bits/stdc++.h>
using namespace std;

// suppose number n has k digits.
// we can make any digit with 1, 2 ... k - 1 digits.
// # of ways for d digits is l^d, l = # of digits we have.
// for k digits, we have to be careful not to exceed n.

// let helper(string n, int i, digits) 
// be number of numbers of k digits, with the same prefix[0..i - 1].
// for index i, if n[i] is not in digits, no point checking for the case prefix[0..i].

int get_num_of_digits(int n) {
    int cnt = 0;
    while (n > 0) {
        cnt += 1;
        n %= 10;
    }
    return cnt;
}

class Solution {
public:

    int helper(string n, int i, const vector<string>& digits) {
        if (i == n.size()) return 0;

        char d = n[i];
        int p = 0;
        for (; p < digits.size() && digits[p][0] < d; p++);
        bool inside = (p < digits.size() && digits[p][0] == d);

        int less = p * pow(digits.size(), n.size() - i - 1);
        int next = (!inside) ? 0 : helper(n, i + 1, digits);
        return less + next;


    }


    int atMostNGivenDigitSet(vector<string>& digits, int n) {
        string num = to_string(n);
        int cnt = 0;

        for (int l = 1; l < num.size(); l++) {
            cnt += pow(digits.size(), l);
        }

        //println("{}", cnt);

        cnt += helper(num, 0, digits);

        unordered_set<string> store(digits.begin(), digits.end());

        bool inside = true;
        for (char c : num) inside = inside && store.contains(string(1, c));
        //println("{}", inside);
        if (inside) cnt++;

        return cnt;
    }
};

int main() {
    Solution sol;
    vector<string> digits = {"5", "7"};
    int n = 19;
    int ans = sol.atMostNGivenDigitSet(digits, n);
    println("{}", ans);
}