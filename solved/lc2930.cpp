#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<vector<vector<vector<int>>>>* dp;
    int MOD = 1000000007;

    int helper(int l, int e, int t, int n) {
        if (n == 0) {
            return (l == 0 && e == 0 && t == 0) ? 1 : 0;
        } else if ((*dp)[l][e][t][n] != -1) {
            return (*dp)[l][e][t][n];
        } else {
            int count = 0;
            // 1st letter is l
            count += helper(0, e, t, n - 1);
            count = count % MOD;

            // 1st letter is e
            if (e > 0) {
                count += helper(l, e - 1, t, n - 1);
                count = count % MOD;
            } else {
                count += helper(l, 0, t, n - 1);
                count = count % MOD;
            }

            // 1st letter is t
            count += helper(l, e, 0, n - 1);
            count = count % MOD;

            long long rest = helper(l, e, t, n - 1);
            rest *= 23;
            rest = rest % MOD;
            count += rest;
            count = count % MOD;
            
            (*dp)[l][e][t][n] = count;
            //cout << count << endl;
            return count;
        }
    }

    int stringCount(int n) {
        dp = new vector(2, vector(3, vector(2, vector(n + 1, -1))));
        return helper(1, 2, 1, n);
    }
};

int main() {
    Solution s;
    cout << s.stringCount(10) << endl;
    return 0;
}