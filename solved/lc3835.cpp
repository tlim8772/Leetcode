#include <bits/stdc++.h>
#include <bit>
using namespace std;
using ll = long long;

// cost = (max(nums[l..r]) - min(nums[l..r])) * (r - l + 1)
// fix l, and increase r to the right, cost function is strictly increasing.
// for each l, use binary search to find r.
// use sparse table to find max(nums[l..r]) in O(1).

template <typename T, typename R>
struct SparseTable {
    int LEN, MAX_POW;
    vector<vector<T>> table;
    R reducer;

    SparseTable(const vector<T> arr): SparseTable(arr, R()) {}

    SparseTable(const vector<T> arr, R reducer): 
        LEN(arr.size()),
        MAX_POW(std::bit_width(uint32_t (arr.size()) - 1)),
        table(LEN, vector<T>(MAX_POW + 1, T())),
        reducer(reducer) 
    {
        for (int i = 0; i < LEN; i++) {
            table[i][0] = arr[i];
        }

        for (int p = 1; p <= MAX_POW; p++) {
            for (int i = 0; i < LEN; i++) {
                int next = i + (1 << (p - 1));
                table[i][p] = (next >= LEN) ? table[i][p - 1] : reducer(table[i][p - 1], table[next][p - 1]);
            }
        }
    }

    T query(int l, int r) {
        int max_p = std::bit_width(uint32_t (r - l + 1)) - 1;
        return reducer(table[l][max_p], table[r - (1 << max_p) + 1][max_p]);
    }
};

struct Min {
    int operator()(const int& x1, const int& x2) const {
        return min(x1, x2);
    }
};

struct Max {
    int operator()(const int& x1, const int& x2) const {
        return max(x1, x2);
    }
};

void testSparseTable() {
    SparseTable<int, Min> st({3,1,2,4,5,6,0});
    assert(st.query(0, 0) == 3);
    assert(st.query(1, 3) == 1);
    assert(st.query(2, 6) == 0);
    
    SparseTable<int, function<int(int,int)>> st2({1,2,3,4,5}, [] (int x, int y) { return max(x, y); });
    assert(st2.query(0, 0) == 1);
    assert(st2.query(0, 4) == 5);
}

// f(start, mid) returns true if <= k, else false.
int binary_search(int l, int r, function<bool(int,int)> f) {
    int start = l;
    while (l < r) {
        int m = (l + r + 1) >> 1;
        bool ans = f(start, m);
        if (ans) {
            l = m;
        } else {
            r = m - 1;
        }
    }
    return f(start, l) ? l : -1;
}

class Solution {
public:
    long long countSubarrays(vector<int>& nums, long long k) {
        SparseTable<int, Min> stmin(nums);
        SparseTable<int, Max> stmax(nums);
        function<bool(int,int)> f = [&stmin, &stmax, k] (int start, int i) -> bool {
            return (stmax.query(start, i) - stmin.query(start, i)) * (ll) (i - start + 1) <= k;
        };

        ll sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            int lim = binary_search(i, nums.size() - 1, f);
            if (lim == -1) continue;
            sum += (lim - i + 1);
        }
        return sum;
    }
};


int main() {
    //testSparseTable();
    Solution sol;
    vector<int> nums = {1,3,2};
    int k = 4;
    ll ans = sol.countSubarrays(nums, k);
    cout << ans << endl;
}
