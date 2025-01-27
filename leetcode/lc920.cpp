#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// dp(i, j): i is index, j is num of colors not used
// the k songs before a song can be replayed is just a red herring
// lemma: for any contigous subarray of size k in final playlist, no song is repeated
// suppose we are at index i, i >>> k
// the num of songs available is n - k, and obviously we have used >= k songs
// so either we use a song that is not played before, or we used a song that is played before
// dp(i, j) = j * dp(i + 1, max(0, j - 1)) + (n - k - j) * dp(i + 1, j)

// if i is <= k, then obviously songs available is n - i (i here is  0 index)
// dp(i, j) = j * dp(i + 1, max(0, j -1)) + (n - i - j) * dp(i + 1, j)

class Solution {
public:
    ll MOD = 1e9 + 7;
    int n, goal, k;
    vector<vector<ll>> dp;

    ll mult(ll a, ll b) {
        return (a * b) % MOD;
    }

    ll add(ll a, ll b) {
        return (a + b) % MOD;
    }

    ll helper(int i, int j) {
        if (i == goal) {
            return (j == 0) ? 1 : 0;
        } else if (dp[i][j] != -1) {
            return dp[i][j];
        } else if (i <= k) {
            ll c = n - i;
            ll opt1 = mult(j, helper(i + 1, max(0, j - 1)));
            ll opt2 = mult(c - j, helper(i + 1, j));
            ll res = add(opt1, opt2);
            dp[i][j] = res;
            return res;
        } else {
            ll c = n - k;
            ll opt1 = mult(j, helper(i + 1, max(0, j - 1)));
            ll opt2 = mult(c - j, helper(i + 1, j));
            ll res = add(opt1, opt2);
            dp[i][j] = res;
            return res;
        }
    }

    int numMusicPlaylists(int n, int goal, int k) {
        this->n = n;
        this->goal = goal;
        this->k = k;

        dp = vector(goal, vector<ll>(n + 1, -1));
        return helper(0, n);
    }



};

int main() {
    Solution sol;
    cout << sol.numMusicPlaylists(2, 3, 1) << endl;
}