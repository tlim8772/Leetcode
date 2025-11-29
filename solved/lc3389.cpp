#include <bits/stdc++.h>
using namespace std;

/*
dp(target, i, carry) = min cost to make all chars i, i + 1 ... z have frequency target.
carry means whether we can use the previous char to convert to char i.

carrying is only possible if freq[i - 1] > target.
not optimal to add more char i - 1 just to convert to char i, we can just add to char i.
not optimal to convert twice, eg char i - 1 to char i to char i + 1.
just delete excess char i - 1 and add char i + 1 as needed, the cost is the same.

suppose we delete all of char c to make it 0, we have to consider the case we can give it
to char c + 1
*/

class Solution {
public:
    vector<int> store;
    vector<int> char_freqs = vector(26, 0);

    int get_pos(int target, int i, int carry) {
        return target * 26 * 2 + i * 2 + carry;
    }

    int dp(int target, int i, int carry) {
        if (i == 26) return 0;
        int pos = get_pos(target, i, carry);
        if (store[pos] != -1) return store[pos];

        int ans;
        if (carry == 0) {
            if (char_freqs[i] == target) {
                ans = dp(target, i + 1, 0);
            } else if (char_freqs[i] > target) {
                ans = char_freqs[i] - target + dp(target, i + 1, 1);
            } else {
                int del_all = char_freqs[i] + dp(target, i + 1, 1);
                int add = target - char_freqs[i] + dp(target, i + 1, 0);
                ans = min(del_all, add);
            }
        } else {
            int diff = (char_freqs[i - 1] > target) ? char_freqs[i - 1] - target : char_freqs[i - 1];
            if (char_freqs[i] == target) {
                ans = dp(target, i + 1, 0);
            } else if (char_freqs[i] > target) {
                ans = char_freqs[i] - target + dp(target, i + 1, 1);
            } else {
                int del_all = char_freqs[i] + dp(target, i + 1, 1);
                int add_rem = max(0, target - char_freqs[i] - diff) + dp(target, i + 1, 0);
                ans = min(del_all, add_rem);
            }
        }
        return store[pos] = ans;
    }

    int makeStringGood(string s) {
        for (char c : s) char_freqs[c - 'a']++;
        int max_val = *max_element(char_freqs.begin(), char_freqs.end());
        store = vector((max_val + 1) * 26 * 2, -1);

        int best = 999999999;
        for (int target = 1; target <= max_val; target++) {
            int ans = dp(target, 0, 0);
            best = min(best, ans);
        }
        return best;
    }
};

int main() {
    Solution sol;
    string s = "gggggggiijjjj";
    cout << sol.makeStringGood(s) << endl;
}