#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// key here is to realise that product of digits only have prime factors of 2,3,5,7
// so that state is (currProd, currSum, idx, end, start)
// currently product is 2^a * 3^b * 5^c * 7^d, idx is the position of the num we are processing
// sum is the current sum
// for 2, max we can add is 3 2^3 = 8
// for 3 max we can add is 2 3^2 = 9
// for 5 and 7 is only 1
// the number of possible products is very limited, bounded by 28 * 19 * 10 * 10 = 53200  
// checking manually, it is 3026 in range [1, 1e10 - 1]    

unordered_map<ll, int> dp;

const ll MAX_START = 2, MAX_IDX = 10, MAX_END = 11, MAX_PROD = 387420490, MAX_SUM = 82;

inline ll coor(int start, int idx, int end, int prod, int sum) {
    return start * MAX_IDX * MAX_END * MAX_PROD * MAX_SUM
        + idx * MAX_END * MAX_PROD * MAX_SUM
        + end * MAX_PROD * MAX_SUM
        + prod * MAX_SUM
        + sum;
}

inline void reset() {
    dp.clear();
}

// end is always 10
// if we want 2 digit numbers, we put idx = 8
// start == true means we must start, i.e we must put a non-zero digit
int helper(int start, int idx, int end, int prod, int sum) {
    int pos = coor(start, idx, end, prod, sum);

    if (idx == end) {
        return prod % sum == 0;
    } else if (dp.count(pos) > 0) {
        return dp[pos];
    } else if (start) {
        // 1st digit cannot be a 0. initial prod = 1, initial sum = 0
        int total = 0;
        for (int i = 1; i <= 9; i ++) {
            int res = helper(false, idx + 1, end, i, i);
            total += res;
        }

        dp[pos] = total;
        return total;
    } else if (prod == 0) {
        // some digit (not 1st) is 0, means we are free to put any digit for remaining positions
        int left = end - idx;
        int res = (int) pow(10, left);
        
        dp[pos] = res;
        return res;
    } else {
        int total = 0;
        for (int i = 0; i <= 9; i ++) {
            int res = helper(false, idx + 1, end, prod * i, sum + i);
            total += res;
        }

        dp[pos] = total;
        return total;
    }
}

// if idx == 2, means we have match num[0], num[1]
// num cannot have leading 0s
int findBeautNum(const string& num, int idx, int prod, int sum) {
    if (idx == num.size()) {
        
        int total = (prod % sum == 0);
        
        // find all beautiful num with lesser digits than num
        for (int i = 1; i < num.size(); i ++) {
            total += helper(true, 9 - i, 9, 1, 0);
        }

        return total;
    } else if (idx == 0) {
        int digit = num[idx] - '0';
        int match = findBeautNum(num, idx + 1, digit, digit);

        int noMatch = 0;
        for (int i = 1; i < digit; i ++) {
            noMatch += helper(false, 9 - (num.size() - 1), 9, i, i);
        }

        return match + noMatch;

    } else {
        int digit = num[idx] - '0';
        int match = findBeautNum(num, idx + 1, prod * digit, sum + digit);
        

        int noMatch = 0;
        for (int i = 0; i < digit; i ++) {
            noMatch += helper(false, 9 - (num.size() - idx - 1), 9, prod * i, sum + i);
        }

        return match + noMatch;
    }
        
}


class Solution {
public:
    int beautifulNumbers(int l, int r) {
        reset();
        int rRes = findBeautNum(to_string(r), 0, 1, 0);
        int lRes = (l == 1) ? 0 : findBeautNum(to_string(l - 1), 0, 1, 0);
        return rRes - lRes;
        
    }
};

int main() {
    reset();
    //cout << helper(false, 9, 9, 64, 16) << endl;
    cout << findBeautNum("1234567", 0, 1, 0) << endl;
}


