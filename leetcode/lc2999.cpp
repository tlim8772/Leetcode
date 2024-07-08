#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Counter {
public:
    //vector<int>* dp;

    long long numWays(int digitsLeft, string& s, int first, int limit) {
        if (digitsLeft < s.size())  {
            return 0;
        } else if (digitsLeft == s.size()) {
            return 1;
        } else if (first == 1) {
            return limit * numWays(digitsLeft - 1, s, 0, limit);
        } else {
            return (limit + 1) * numWays(digitsLeft - 1, s, 0, limit);
        }
    }

    
    // range [0, index - 1] is equal to range[0, index -1] of target
    long long helper(int index, string& target, string& s, int limit) {
        if (target.size() - index < s.size()) {
            return 0;
        } else if (target.size() - index == s.size())  {
           string left = target.substr(index, target.size() - index);
           long long num = stoll(left);
           return (stoll(s) <= num) ? 1 : 0;
        } else {
            int currDigit = target[index] - '0';
            int newLimit = min(currDigit, limit);
            long long lesser = 0;
            if (index == 0) {
                lesser = (newLimit == currDigit) ? (newLimit - 1) * numWays(target.size() - index - 1, s, 0, limit)
                                                 : newLimit * numWays(target.size() - 1, s, 0, limit);
            } else {
                lesser = (newLimit == currDigit) ? newLimit * numWays(target.size() - index - 1, s, 0, limit)
                                                 : (newLimit + 1) * numWays(target.size() - index - 1, s, 0, limit);
            }
            long long same = (currDigit <= limit) ? helper(index + 1, target, s, limit) : 0;
            return same + lesser;

        }
    }

    long long countPowerfulIntegers(long long finish, string suffix, int limit) {
        string finishString = to_string(finish);
        long long count = 0;
        for (int i = suffix.size(); i < finishString.size(); i ++) {
            count += numWays(i, suffix, 1, limit);
        }
        cout << count << endl;
        count += helper(0, finishString, suffix, limit);
        return count;
    }

};

class Solution {
public:
    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s) {
        Counter c1;
        return c1.countPowerfulIntegers(finish, s, limit) - c1.countPowerfulIntegers(start - 1, s, limit);
    }
};


int main() {
    /*Solution sol;
    cout << sol.numberOfPowerfulInt(141, 148, 9, "9");*/
    Counter c1;
    cout << c1.countPowerfulIntegers(1844, "12", 5);
}