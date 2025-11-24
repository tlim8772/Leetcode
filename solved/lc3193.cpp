#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// HINT: consider the relative ordering of elements
// we can currently choose


template <typename T>
void print(vector<T> arr) {
    for (T t: arr) {
        cout << t << " ";
    }
    cout << endl;
}

class Solution {
public:
    const ll MOD = 1000000007;
    
    int N, CNT = 401;
    vector<ll> store;

    inline int coor(int i, int cnt) {
        return i * CNT + cnt;
    }

    // i: index we are currently choosing for range is [0, n-1]
    // cnt: number of inversions we want 
    // dp(i, cnt): num of permutations from index [0..i] with cnt inversions
    // 
    // we go from the back
    // let say we are at index 3 of len 4 (means last index)
    // if we choose 0, we have 3 inversions 1,0 2,0, 3,0
    // if choose 2, we have 1 inversion 3,2
    ll dp(int i, int cnt, const vector<int>& limits) {
        if (i == -1) {
            return (cnt == 0) ? 1 : 0;
        } else if (limits[i] != -1 && limits[i] != cnt) {
            return 0;
        } 

        int pos = coor(i, cnt);
        if (store[pos] != -1) return store[pos];

        ll sum = 0;
        for (int n = 0; n <= i; n++) {
            int newCnt = cnt - (i - n);
            if (newCnt < 0) continue;

            ll ans = dp(i - 1, newCnt, limits);
            
            sum = (sum + ans) % MOD;
        }

        store[pos] = sum;
        return sum;
    }

    int numberOfPermutations(int n, vector<vector<int>>& requirements) {
        vector<int> limits(n, -1);
        for (vector<int>& r : requirements) {
            limits[r[0]] = r[1];
        }
       
        N = n;
        store = vector<ll>(n * CNT, -1);
        //print(limits);
        ll ans = dp(n - 1, limits[n - 1], limits);
        
        return ans;
    }

};

int main() {
    Solution sol;

    int n = 3;
    vector<vector<int>> requirements = {{2,2},{0,1}};
    cout << sol.numberOfPermutations(n, requirements) << endl;
}