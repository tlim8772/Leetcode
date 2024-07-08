#include <vector>
#include <iostream>
#include <stdio.h>
using namespace std;
typedef long long ll;
#define MOD 1000000007

// subarray of length greater than limit has at least 1 '0' and 1 '1' <=> length of blocks of consecutive 1s (or 0s) is <= limit, can prove this easily
// let dp[0][x][y] mean we are placing 0s, with x 0s and y 1s left
// dp[0][x][y] = sum(i = 1, i = limit) dp[1][x - i][y]
// dp[1][x][y] = sum(i = 1, i = limit) dp[0][x][y - i]
// use prefix sums to speed up computation
class Solution {
public:
    vector<vector<vector<int>>> dp;
    vector<vector<int>> prefix1; // sums dp[1][x][y], x is the changer
    vector<vector<int>> prefix0; // sums dp[0][x][y], y is the changer

    int modulo(int x, int y) {
        int ans = x % y;
        return (ans < 0) ? ans + y : ans;
    }

    int helper1(int x, int y) {
        return (x == -1) ? 0 : prefix1[x][y];
    }

    int helper0(int x, int y) {
        return (y == -1) ? 0 : prefix0[x][y];
    }

    void print(vector<vector<int>> arr) {
        for (int i = 0; i < arr.size(); i ++) {
            for (int j = 0; j < arr[0].size(); j ++) {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
    }
    
    int solve(int zeros, int ones, int limit) {
        int n = zeros + ones;
        dp = vector(2, vector(zeros + 1, vector<int>(ones + 1,  0)));
        prefix1 = vector(zeros + 1, vector<int>(ones + 1, 0));
        prefix0 = vector(zeros + 1, vector<int>(ones + 1, 0));
        dp[0][0][0] = 1;
        dp[1][0][0] = 1;
        prefix0[0][0] = 1;
        prefix1[0][0] = 1;

        for (int i = 1; i <= ones + zeros; i ++) {
            for (int x = 0; x <= i; x ++) {
                
                if (x > zeros || i - x > ones) continue;
                if (x == 0) {
                    dp[0][x][i - x] = 0;
                    prefix0[x][i - x] = prefix0[x][i - x - 1];
                } else {
                    int lim = min(limit, x);
                    int ans = helper1(x - 1, i - x) - helper1(x - lim - 1, i - x);
                    ans = modulo(ans, MOD);
                    prefix0[x][i - x] = modulo(ans + helper0(x, i - x - 1), MOD);
                    dp[0][x][i - x] = ans;
                }
                //cout << x << " " << i - x << " " << dp[0][x][i - x] << endl;
            }

            for (int y = 0; y <= i; y ++) {
                if (i - y > zeros || y > ones) continue;
                if (y == 0) {
                    dp[1][i - y][y] = 0;
                    prefix1[i - y][y] = prefix1[i - y - 1][y];
                } else {
                    int lim = min(limit, y);
                    int ans = helper0(i - y, y - 1) - helper0(i - y, y - lim - 1);
                    ans = modulo(ans, MOD);
                    prefix1[i - y][y] = modulo(ans + helper1(i - y - 1, y), MOD);
                    dp[1][i - y][y] = ans;
                }
                //cout << y << " " << i - y << " " << dp[1][i - y][y] << endl;
            }
        }
       
        //print(dp[0]);
        //print(dp[1]);
        return modulo(dp[0][zeros][ones] + dp[1][zeros][ones], MOD);


    }

    int numberOfStableArrays(int zero, int one, int limit) {
        int ans = solve(zero, one, limit);
        dp.clear();
        prefix0.clear();
        prefix1.clear();
        return ans;
    }


};

int main() {
    Solution sol;
    cout << sol.solve(980, 990, 250);
}