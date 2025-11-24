#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;


// we can freely distribute characters
// in the optimal # of palindromes, let say k, the palindromes formed are the k smallest length words
// because if we can form a palindrome of length n + 1, (n + 1) is even or odd does not matter, we can form a palindrome of length n

// iterate from smallest length onwards
// if length is even, take as much characters you want starting from a, b, c ... z
// even if we dont, suppose the char we are using is a, if it is used elsewhere can switch with whatever char we choose instead of a, if it is not used, can just use now.

// if length is odd, first take 1 char from any characters with odd remaining count
// if does not exist, just take 1 char from any characters, clearly this char will be used for other odd length, even if we do not use the 1st available char now
// and this results in optimal solution, we can switch the chars
class Solution {
public:
    vector<int> sorter(vector<string>& words) {
        vector<int> out;
        for (int i = 0; i < words.size(); i ++) {
            out.push_back(words[i].size());
        }
        sort(out.begin(), out.end());
        return out;
    }

    vector<int> collect(vector<string>& words) {
        vector<int> out = vector(26, 0);
        for (int i = 0; i < words.size(); i ++) {
            string& s = words[i];
            for (int j = 0; j < s.size(); j ++) {
                out[s[j] - 'a'] += 1;
            }
        }
        return out;
    }

    int findOdd(vector<int>& letters) {
        for (int i = 0; i < letters.size(); i ++) {
            if (letters[i] % 2 != 0) {
                return i;
            }
        }
        return -1;
    }

    int fill(vector<int>& letters, int len) {
        if (len % 2 == 0) {
            for (int i = 0; i < letters.size(); i ++) {
                if (letters[i] >= len) {
                    letters[i] -= len;
                    return 1;
                } else {
                    len -= 2 * (letters[i] / 2);
                    letters[i] -= 2 * (letters[i] / 2);
                }
            }
            return (len == 0) ? 1 : 0;
        } else {
            int odd = findOdd(letters);
            if (odd != -1) {
                letters[odd] -= 1;
                return fill(letters, len - 1);
            } else {
                for (int i = 0; i < letters.size(); i ++) {
                    if (letters[i] != 0) {
                        letters[i] -= 1;
                        return fill(letters, len - 1);
                    }
                }
                return 0;
            }
        }
    }
    
    
    int maxPalindromesAfterOperations(vector<string>& words) {
        vector<int>&& sorted = sorter(words);
        vector<int>&& chars = collect(words);
        for (int i = 0; i < sorted.size();i ++) {
            int can = fill(chars, sorted[i]);
            if (can == 0) {
                return i;
            }
        }
        return sorted.size();
    }
};

int main() {
    Solution sol;
    vector<string> words = {"cd","ef","a"};
    cout << sol.maxPalindromesAfterOperations(words);
}