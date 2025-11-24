#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// n <= 10^15, so at most only 16 digits used
// this can be done with digits 8,6,2
// not may special palindromes
// 15: 8, 7
// 14: 8, 6
// 13: 8, 5
// 12: 8, 4
// 11: 8, 3
// 10: 8, 2
// 9, 8, 7 ... 2: just use the digit itself
// we cannot have digit 0

// so if we have n digits, only need to check special palindrome with n, n + 1 digits
// generate all special palindroms, all of them in a set then use upper_bound


template <typename T, size_t N> 
void print(array<T, N> arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

class Solution {
public: 
    vector<array<bool, 10>> configStore;
    set<ll> specialPalindromeStore;
    
    int numDigits(ll n) {
        return to_string(n).size();
    }

    void generateConfig(int currDigit, bool hasOdd, int totalDigits, int n, array<bool, 10>& store) {
        if (currDigit == 10) return;

        if (currDigit % 2 == 1) {
            if (hasOdd) {
                if (totalDigits + currDigit <= n) {
                    generateConfig(currDigit + 1, true, totalDigits, n, store);
                }
            } else { 
                int newTotalDigits = totalDigits + currDigit;
                if (newTotalDigits <= n + 1) {
                    store[currDigit] = true;
                    
                    if (newTotalDigits >= n) {
                        configStore.push_back(store);
                    }

                    if (newTotalDigits <= n) {
                        generateConfig(currDigit + 1, true, newTotalDigits, n, store);
                    }

                    store[currDigit] = false;
                    generateConfig(currDigit + 1, false, totalDigits, n, store);
                }
            }
        } else {
            int newTotalDigits = totalDigits + currDigit;
            if (newTotalDigits <= n + 1) {
                store[currDigit] = true;

                if (newTotalDigits >= n) {
                    configStore.push_back(store);
                }

                if (newTotalDigits <= n) {
                    generateConfig(currDigit + 1, hasOdd, newTotalDigits, n, store);
                }

                store[currDigit] = false;
                generateConfig(currDigit + 1, hasOdd, totalDigits, n, store);
            }
        }
    }

    // digits only store the number of digits for the 1st half 
    // and does not include the middle if palindrome length is odd
    void helper(vector<int>& digits, char oddDigit, string& store) {
       
        
        bool hasLeft = false;
        for (int i = 1; i <= 9; i++) {
            if (digits[i] == 0) continue;
            hasLeft = true;
            
            digits[i]--;
            store.push_back('0' + i);
            
            helper(digits, oddDigit, store);

            digits[i]++;
            store.pop_back();
        }

         if (!hasLeft) {
            string ans = store;
            
            string right = store;
            reverse(right.begin(), right.end());
            
            if (oddDigit != '0') ans.push_back(oddDigit);
            ans += right;
            
            ll palindrome = stoll(ans);
            specialPalindromeStore.insert(palindrome);
            
            return;
        } 
    }

    void generateSpecialPalindromes() {
        char oddDigit = '0';
        vector<int> digits(10, 0);
        string store = "";
        
        for (const array<bool, 10>& arr : configStore) {
            char oddDigit = '0';
            vector<int> digits(10, 0);
            string store = "";
            
            for (int i = 1; i < 10; i++) {
                if (arr[i]) {
                    digits[i] = i >> 1;

                    if (i % 2 == 1) {
                        oddDigit = '0' + i;
                    }
                }
            }

            helper(digits, oddDigit, store);
        }
    }

    long long specialPalindrome(long long n) {
        int digits = numDigits(n);

        array<bool, 10> store = {false};
        generateConfig(1, false, 0, digits, store);

        generateSpecialPalindromes();

        /*for (const array<bool, 10> arr : configStore) {
            print(arr);
        }*/

        /*for (const ll& num : specialPalindromeStore) {
            cout << num << endl;
        }*/

        auto it = specialPalindromeStore.upper_bound(n);
        ll ans = (it == specialPalindromeStore.end()) ? -1 : *it;

        return ans;
    }

};

int main() {
    Solution sol;

    ll n = 22;

    cout << sol.specialPalindrome(n) << endl;
}
