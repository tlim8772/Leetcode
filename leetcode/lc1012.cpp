#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    long long factorial(int n) {
        return (n == 0) ? 1 : n * factorial(n - 1);
    }

    long long nPr(int n, int r) {
        long long a = factorial(n);
        long long b = factorial(n - r);
        //long long c = factorial(r);
        return a / b;
    }

    //long long count(int numDigits, int digit)

    long long helper(int index, string& num, int used, int digitsLeft) {
        if (index == num.size()) {
            return 1;
        } else if (index == 0) {
            int currDigit = num[index] - '0';
            long long lesser = (currDigit - 1) * nPr(digitsLeft - 1, num.size() - index - 1);
            long long same = helper(index + 1, num, used - (1 << currDigit), digitsLeft - 1);
            return same + lesser;
        } else {
            int currDigit = num[index] - '0';
            int possDigits = 0;
            for (int i = 0; i < currDigit; i ++) {
                possDigits += (used >> i) & 1;
            }
            //cout << possDigits << endl;
            
            long long lesser = possDigits * nPr(digitsLeft - 1, num.size() - index - 1);
            long long same = ((used >> currDigit) & 1) ? helper(index + 1, num, used - (1 << currDigit), digitsLeft - 1) : 0;
            //cout << ((used >> currDigit) & 1) << endl;
            return same + lesser;
        }
    }
    
    int numDupDigitsAtMostN(int n) {
        long long c = 0;
        string num = to_string(n);
        for (int i = 1; i < num.size(); i ++) {
            c += 9 * nPr(9, i - 1);
        }
        //cout << c << endl;    
        c += helper(0, num, (1 << 10) - 1, 10);
        //cout << c << endl;
        return n - (int) c;
    }
};

int main() {
    //cout << (new Solution)->nPr(10, 0) << endl;
    cout << (new Solution)->numDupDigitsAtMostN(19) << endl;
}