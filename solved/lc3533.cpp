#include <bits/stdc++.h>
using namespace std;

// dynamic programming
// dp(m, bm) bm: numbers not used, m: mod of digits used (dont forget the 0s at the back)
// to get lexicographically smallest when considered as list of integers, e.g [12,3,45]
// 3,12,45 is smaller than 12,3,45 as 3 < 12, we sort nums first

// return (a^b) % m
int pow(int a, int b, int m) {
    assert(b >= 0);
    
    if (b == 0) {
        return 1 % m;
    } else if (b & 1) {
        return ((a % m) * pow(a, b - 1, m)) % m;
    } else {
        int ans = pow(a, b >> 1, m);
        return (ans * ans) % m;
    }
}

struct Res {
    int can = -1, nextPos = -1, nextElem = -1;
};

class Solution {
public:
    int N, k, LEN, totalDigits = 0;
    vector<pair<int, int>> arr;

    
    vector<Res> dp;

    inline int coor(int m, int bm) {
        return m * LEN + bm;
    }

    void process(vector<int>& nums, int k) {
        N = nums.size();
        this->k = k;
        LEN = 1 << N;
        dp = vector(k * LEN, Res());

        for (int n : nums) {
            int cnt = 0;
            int curr = n;
            while (curr > 0) {
                cnt++;
                curr = curr / 10;
            }

            arr.push_back({n, cnt});
            totalDigits += cnt;
        }
    }

    Res helper(int m, int bm, int digitLeft) {
        int pos = coor(m, bm);
        
        if (dp[pos].can != -1) {
            return dp[pos];
        } else if (bm == 0) {
           dp[pos] = (m == 0) ? Res{1, -1, -1} : Res{0, -1, -1};
           return dp[pos];
        }

        for (int i = 0; i < N; i++) {
            if (((bm >> i) & 1) == 0) continue;

            int a = arr[i].first % k;
            int b = pow(10, digitLeft - arr[i].second, k);
            int res = (a * b) % k;

            int newM = (m + res) % k;
            int newBm = bm - (1 << i);
            int nextPos = coor(newM, newBm);

            Res ans = helper(newM, newBm, digitLeft - arr[i].second);
            if  (ans.can) {
                dp[pos] = {1, nextPos, i};
                return dp[pos];
            }
        }

        dp[pos] = {0, -1, -1};
        return dp[pos];
    }

    vector<int> rebuild(vector<int>& nums) {
        Res start = dp[coor(0, (1 << N) - 1)];
        if (!start.can) return vector<int>();

        vector<int> out;
        while (start.nextElem != -1) {
            out.push_back(nums[start.nextElem]);
            start = dp[start.nextPos];
        }

        return out;
    }

    vector<int> concatenatedDivisibility(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        process(nums, k);
        //cout << totalDigits << endl;
        //for (pair<int, int> p : arr) cout << p.first << " " << p.second << endl;
        helper(0, (1 << N) - 1, totalDigits);
        return rebuild(nums);
    }



    
};

int main() {
    Solution sol;

    vector<int> nums = {6,3};
    int k = 1;

    vector<int> ans = sol.concatenatedDivisibility(nums, k);
    for (int x : ans) cout << x << endl;
}