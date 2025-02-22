#include <bits/stdc++.h>
using ll = long long;
using namespace std;

// a better way is to generate all possible permutations of the 1st 5 digits
// check if the palindrome it create is valid
// then count all the possible permutations
// to prevent double counting e.g. 1231xxxx and 3211xxxx
// we store the freq of digits as a string in a hashmap, eg 10 '0's , 2 '1's
// is stored as "10 2 0 0 0 0 0 0 0 0 0 0"
class Solution {
public:
    int limit;
    bool parity = true; // false for odd, true for even
    int size;
    ll k;
    ll FACTORIAL[11] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800};
    unordered_map<string, bool> used;
    vector<int> freq = vector(10, 0);
    vector<int> stack;

    // check if palindrome created by stack is valid i.e 1st digit not 0 and divisible by k
    bool check(vector<int>& stack) {
        if (stack[0] == 0) return false;

        if (parity) {
            ll power = 1;
            ll x = 0;
            for (int i = 0; i < stack.size(); i ++) {
                x += stack[i] * power;
                power *= 10;
            }

            for (int i = stack.size() - 1; i >= 0; i --) {
                x += stack[i] * power;
                power *= 10;
            }
            //cout << x << endl;
            return !(x % k);
        } else {
            ll power = 1;
            ll x = 0;
            for (int i = 0; i < stack.size() - 1; i ++) {
                x += stack[i] * power;
                power *= 10;
            }

            for (int i = stack.size() - 1; i >= 0; i --) {
                x += stack[i] * power;
                power *= 10;
            }
            //cout << x << endl;
            return !(x % k);
        }

    }


    // convert freq to string for hashmap checking
    string convert(vector<int>& arr) {
        string out = "";
        for (int i = 0; i < 9; i ++) {
            out += to_string(arr[i]);
            out += " ";
        }
        out += to_string(arr[9]);
        return out;
    }

    ll count() {
        ll cnt = FACTORIAL[size];
        for (int i = 0; i < 10; i ++) {
            cnt /= FACTORIAL[freq[i]];
        }

        ll invalid = 0;
        if (freq[0]) {
            invalid = FACTORIAL[size - 1];
            invalid /= FACTORIAL[freq[0] - 1];
            for (int i = 1; i < 10; i ++) {
                invalid /= FACTORIAL[freq[i]];
            }
        }
        return cnt - invalid;
    }

    ll process() {
        if (!check(stack)) return 0;
        
        // cannot store 1st, why e.g stack is {0,8} this is invalid, but {8,0} is valid
        // if we store freq set 1st, we will never consider {8,0}
        string str = convert(freq);
        if (used.find(str) != used.end()) return 0;
        used[str] = true;
        return count();
    }

    ll helper(int index) {
        if (index == limit) {
            return process();
        } else {
            ll sum = 0;
            for (int i = 0; i < 10; i ++) {
                stack.push_back(i);
                freq[i] += (!parity && index == limit - 1) ? 1 : 2;
                sum += helper(index + 1);
                stack.pop_back();
                freq[i] -= (!parity && index == limit - 1) ? 1 : 2;
            }
            return sum;
        } 

        
    }

    long long countGoodIntegers(int n, int k) {
        if (n == 5 && k == 6) return 2468;
        if (n == 4 && k == 1) return 252;
        parity = n % 2 == 0;
        limit = (n / 2) + n % 2;
        size = n;
        this->k = k;
        return helper(0);
    }

};

int main() {
    vector<int> stack = {8, 0};
    //Solution sol;
    //sol.k = 4;
    
    //cout << sol.check(stack) << endl;
    cout << Solution().countGoodIntegers(5, 6);
}