#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ignore indices that we do not need to change.
// count the pairs we need to change, let type a = (s[i] = 1, t[i] = 0), type b = (s[i] = 0, t[i] = 1)
// if a, b > 0, each swap can clear off 1 a and 1 b. So if swap < 2 * flip, take min(a, b) swaps
// now let say only type a pairs left.
// for the remaining type a, we can use cross, which is to covert type a to type b,
// then use a swap, or we can just flip
// in this case, a cross + wap removes 2 pairs.
// so if cross + swap < 2 * flip, take as many cross + swap
// for the last single type a, use a flip.

// if swap is >= 2 * flip, cross + swap is dead already, in this case just flip.

class Solution {
public:
    long long minimumCost(string s, string t, ll flipCost, ll swapCost, ll crossCost) {
        int type_a = 0, type_b = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '1' && t[i] == '0') type_a++;
            else if (s[i] == '0' && t[i] == '1') type_b++;
        }

        ll sum = 0;
        if (swapCost >= 2 * flipCost) {
            return flipCost * (type_a + type_b);
        }

        ll gone = min(type_a, type_b);
        sum += gone * swapCost;
        type_a -= gone; // one of type_a, type_b is 0
        type_b -= gone;

        if (crossCost + swapCost >= 2 * flipCost) {
            return sum + (type_a + type_b) * flipCost;
        }

        sum += ((type_a + type_b) / 2) * (crossCost + swapCost);
        if ((type_a + type_b) % 2) sum += flipCost;
           
        return sum;
    }
};

int main() {
    Solution sol;
    int flipCost = 2, swapCost = 100, crossCost = 100;
    string s = "001";
    string t = "110";

    cout << sol.minimumCost(s, t, flipCost, swapCost, crossCost) << endl;
}


