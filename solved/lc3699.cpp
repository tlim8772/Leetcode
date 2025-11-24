#include <bits/stdc++.h>
using namespace std;

// [l, r] -> [0, r - l]
// dp(start number, dir, index)
// 0 means need to go up (i.e choose a higher number than prev)
// 1 means need to go down
// take or no take dp
// suppose we can choose 2,3,4,5, prev is 1
// we take 2 good, dont take 2, assume we prev is 2 so we only 3,4,5
// this way we dont need a for loop and check 2,3,4,5

class Solution {
public:
    int MOD = 1e9 + 7;
    int C, DIR = 2, N;
    vector<int> store;

    inline int coor(int c, int dir, int idx) {
        return c * DIR * N + dir * N + idx;
    }

    int dp(int c, int dir, int idx) {
        //printf("%d %d %d\n", c, dir, idx);
        int pos = coor(c, dir, idx);
        if (idx == N) {
            return 1;
        } else if (store[pos] != -1) {
            return store[pos];
        }

        int take = dp(c + (dir == 0 ? -1 : 1), !dir, idx + 1);
        int notake = 0;
        if ((dir == 0 && c == C - 1) || (dir == 1 && c == 0)) {
            notake = 0;
        } else {
            notake = dp(c + (dir == 0 ? 1 : -1), dir, idx);
        }
        
        
        
        return store[pos] = (take + notake) % MOD;
    }

    int zigZagArrays(int n, int l, int r) {
        C = r - l + 1, N = n;
        store = vector(C * DIR * N, -1);

        int sum = 0;
        for (int i = 0; i <= r - l; i++) {
            int startUp = (i == r - l) ? 0 : dp(i + 1, 0, 1);
            int startDown = (i == 0) ? 0 : dp(i - 1, 1, 1);
            int total = (startUp + startDown) % MOD;
            sum = (sum + total) % MOD;
        }
        return sum;
    }
};

int main() {
    int n = 3, l = 1, r = 3;
    Solution sol;
    cout << sol.zigZagArrays(n, l, r) << endl;
}