#include <bits/stdc++.h>
using namespace std;

vector<bool> sieve(int n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = false, isPrime[1] = false;

    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }

    return isPrime;
}

struct Res {
    int mi = 999999;
    int ma = 0;
    int cnt = 0; //store how many primes in the range

    static Res merge(const Res& r1, const Res& r2) {
        return Res{min(r1.mi, r2.mi), max(r1.ma, r2.ma), r1.cnt + r2.cnt};
    }

    void print() {
        cout << mi << " " << ma << " " << cnt << endl;
    }
};

struct SegTree {
    int len;
    vector<Res> tree;

    SegTree(const vector<int>& nums, const vector<bool>& isPrime): len(nums.size()), tree(4 * len, Res{}) {
        build(0, 0, len - 1, nums, isPrime);
    }

    void build(int p, int s, int e, const vector<int>& nums, const vector<bool>& isPrime) {
        if (s == e) {
            if (isPrime[nums[s]]) {
                tree[p] = Res{nums[s], nums[s], 1};
            }
            return;
        }

        int m = (s + e) >> 1;
        build((p << 1) + 1, s, m, nums, isPrime);
        build((p << 1) + 2, m + 1, e, nums, isPrime);
        tree[p] = Res::merge(tree[(p << 1) + 1], tree[(p << 1) + 2]);
    }

    Res queryRange(int p, int s, int e, int l, int r) {
        if (s == e || (s == l && e == r)) {
            return tree[p];
        }

        int m = (s + e) >> 1;
        if (r <= m) {
            return queryRange((p << 1) + 1, s, m, l, r);
        } else if (l > m) {
            return queryRange((p << 1) + 2, m + 1, e, l, r);
        } else {
            Res left = queryRange((p << 1) + 1, s, m, l, m);
            Res right = queryRange((p << 1) + 2, m + 1, e, m + 1, r);
            return Res::merge(left, right);
        }
    }
};



class Solution {
public:
    // for index i, let [start, end] means [i, j] is a valid subarray for all j, start <= j < end
    // key idea is that [start, end] increases as i (the beginning index) moves right
    // suppose for index 0, [start, end] = [3, 5]
    // then for index 1, to find start, we can start from index 3
    // for end, see the new start, anyway we begin from end = max(end, start + 1)

    // it can be that for index i, we dont have any valid subarray
    // eg [2, P1, P2] Pi is some big primes
    // then start is the index where we for sure cannot continue anymore
    // hence for index i + 1, there are no primes in [i + 1, start)
    // so we can continue from start
    int primeSubarray(vector<int>& nums, int k) {
        vector<bool> isPrime = sieve(50000);
        SegTree st(nums, isPrime);

        int ans = 0;
        int start = 0, end = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            bool haveStart = true;
            while (start < nums.size()) {
                Res res = st.queryRange(0, 0, st.len - 1, i, start);
                if (res.cnt >= 2 && (res.ma - res.mi) <= k) {
                    break;
                } else if (res.cnt >=2 && (res.ma - res.mi) > k) {
                    // no point continuing
                    haveStart = false;
                    break;
                } else {
                    start++;
                }
            }

           
            if (haveStart) {
                end = max(end, start + 1);
                while (end < nums.size()) {
                    Res res = st.queryRange(0, 0, st.len - 1, i, end);
                    if (res.cnt >= 2 && (res.ma - res.mi) > k) {
                        break;
                    } else  {
                        end++;
                    }
                }
            }
           

            if (haveStart && start < nums.size()) {
                ans += end - start;
            }

        }

        return ans;
    }
};

int main() {
    Solution sol;

    vector<int> arr = {139,26863,4817};
    int k = 24583;
    cout << sol.primeSubarray(arr, k) << endl;

    
}