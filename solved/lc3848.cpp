#include <bits/stdc++.h>
using namespace std;

// have to generate all possible digit permutations of n.
// we store the frequency of each digit.
// then we use recursion to generate all possible permutations of n.
// to handle repeated digits, we use helper(d, cnt, i, num, len, used).
// we place the digits 0, and digits 1 and so on.
// so we do not compute repeated permuations (eg. 0 at idx 1, 0 at idx 2 and then 0 at idx 2, 0 at idx 1)

// actually we don't need to generate all permuations dumbass.
// but i guess my backtracking works.

int factorial(int n) {
    return n == 0 ? 1 : n * factorial(n - 1);
}

class Solution {
public:
    array<int, 10> digit_counts{0};
    unordered_set<int> store;

    // i is the index and is from the right (i.e from the least significant position).
    void helper(int d, int cnt, int i, int num, int len, bitset<10>& used) {
        if (cnt == 0) {
            if (d == 9) {
                store.insert(num);
            } else {
                helper(d + 1, digit_counts[d + 1], 0, num, len, used);
            }
        } else if (i == len) {
            return; // invalid we have reached the end but have not placed all digits d
        } else if (used[i]) {
            helper(d, cnt, i + 1, num, len, used);
        } else {
            // place
            if (!(d == 0 && i == len - 1)) {
                used[i] = true;
                helper(d, cnt - 1, i + 1, num + d * (int) pow(10, i), len, used);
                used[i] = false;
            }

            // no place
            helper(d, cnt, i + 1, num, len, used);
        }
    }


    bool isDigitorialPermutation(int n) {
        bitset<10> used;
        int len = 0;
        int temp = n;
        int factorial_sum = 0;
        
        while (temp > 0) {
            len++;
            digit_counts[temp % 10]++;
            factorial_sum += factorial(temp % 10);
            temp /= 10;
        }

        while (factorial_sum > 0) {
            int d = factorial_sum % 10;
            if (digit_counts[d] == 0) return false;
            digit_counts[d]--;
            factorial_sum /= 10;
        }

        for (int c : digit_counts) {
            if (c > 0) return false;
        }
        return true;
    }
};

int main() {
    Solution sol;
    int n = 10;
    bool ans = sol.isDigitorialPermutation(n);
    cout << ans << endl;
}