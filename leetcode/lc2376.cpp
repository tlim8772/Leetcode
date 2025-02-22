/*#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>*/
#include <bits/stdc++.h> 
using namespace std;

class Solution {
    public: 
        vector<int> array;
        int size;

        Solution(int n): size(n) {
            array = vector(0, size);
        }

        int digit_find(int index, int limit, int digits_left) {
            if (index == limit) {
                return 1;
            } else if (index == 0) {
                return 9 * digit_find(index + 1, limit, digits_left - 1);
            } else {
                return digits_left * digit_find(index + 1, limit, digits_left - 1);
            }
        }

        int dp(int index, int used, string num, int digits_left) {
            if (index == num.size()) {
                return 1;
            } else if (index == 0) {
                int curr = num.at(index) - '0';
                int sum = 0;
                for (int i = 1; i <= 9; i ++) {
                    if (((used >> i) & 1) == 0) {
                        if (i < curr) {
                            sum += digit_find(index + 1, num.size(), digits_left - 1);
                        } else if (i == curr) {
                            used += (1 << i);
                            sum += dp(index + 1, used, num, digits_left - 1);
                            used -= (1 << i);
                        }
                    }
                }
                return sum;
            } 
            
            else {
                int curr = num.at(index) - '0';
                int sum = 0;
                for (int i = 0; i <= 9; i ++) {
                    if (((used >> i) & 1) == 0) {
                        if (i < curr) {
                            sum += digit_find(index + 1, num.size(), digits_left - 1);
                        } else if (i == curr) {
                            used += (1 << i);
                            sum += dp(index + 1, used, num, digits_left - 1);
                            used -= (1 << i);
                        }
                    }
                }
                return sum;
            }
        }

        int countSpecialNumbers(int n) {
            string int_string = to_string(n);
            int sum = 0;
            for (int i = 1; i < int_string.size(); i ++) {
                sum += digit_find(0, i, 10);
            }
            sum += dp(0, 0, int_string, 10);
            return sum;

        }

};



int main() {
    Solution s = Solution(10);
    cout << s.countSpecialNumbers(100) << endl;
    
    return 0;


}