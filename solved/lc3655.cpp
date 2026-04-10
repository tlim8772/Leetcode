#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// sqrt decomposition.
// for k > sqrt(n) just multiply the number accordingly.
// for k < sqrt(n) we use difference arrays.
// from l to end, we multiply range by v.
// from right + 1 to end we multiply range by v^-1.
// use difference arrays to do range update in O(1).
// basically is prefix multiplication.

// the bins are (k, i % k) so if limit is sqrt(n) we have n bins.
// each bin is a difference array, however to save space the len can only be ceil(n / k).

// instead of using sqrt(len), just use a nice block size (eg) 100, 200 ...

const ll MOD = 1e9 + 7;

ll pow(ll x, ll n, ll m) {
	x %= m;
	ll res = 1;
	while (n > 0) {
		if (n % 2 == 1) { res = res * x % m; }
		x = x * x % m;
		n /= 2;
	}
	return res;
}

ll mod_inverse(ll x) {
    return pow(x, 1e9 + 5, MOD);
}

int endpoint(int l, int r, int k) {
    r += 1;
    return r + (l % k - r % k + k) % k;
}

void mult_ref(int& a, int b) {
    ll _a = a;
    ll temp = (_a * b) % MOD;
    a = (int) temp;
}

const int lim = 100;
vector<int> store[lim + 1][lim + 1];

void init(int len, int limit) {
    for (int i = 1; i <= limit; i++) {
        for (int j = 0; j < i; j++) {
            store[i][j] = vector((int) ceil((float) len / i), 1);
        }
    }
}

class Solution {
public:
    //unordered_map<pair<int,int>, vector<pair<int,int>>, Hash> bins;
    
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        init(nums.size(), lim);

        for (const auto& q : queries) {
            int l = q[0], r = q[1], k = q[2], v = q[3];
            if (k > lim) {
                for (int i = l; i <= r; i += k) {
                    mult_ref(nums[i], v);
                }
            } 
            
            else {
                int end = endpoint(l, r, k);
                int inv = mod_inverse(v);
                mult_ref(store[k][l % k][l / k], v);
                if (end < nums.size()) mult_ref(store[k][l % k][end / k], inv);

            }
        }

        for (int k = 1; k <= lim; k++) {
            for (int j = 0; j < k; j++) {
                vector<int>& arr = store[k][j];
                for (int i = 1; i < arr.size(); i++) {
                    mult_ref(arr[i], arr[i - 1]);
                }
            }
        }

        int accu = 0;
        for (int i = 0; i < nums.size(); i++) {
            for (int k = 1; k <= lim; k++) {
                mult_ref(nums[i], store[k][i % k][i / k]);
            }
            //cout << nums[i] << endl;
            accu ^= nums[i];
        }

        return accu;
    }
};

int main() {
    //cout << mod_inverse(2) << endl;
    Solution sol;
    vector<int> nums = {2,3,1,5,4};
    vector<vector<int>> queries = {{1,4,2,3},{0,2,1,2}};
    int ans = sol.xorAfterQueries(nums, queries);
    cout << "Ans is: " << ans << endl;
}