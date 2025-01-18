#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct PrefixSum {
    vector<ll> prefixSums;

    PrefixSum(vector<int>& arr): prefixSums(arr.size()) {
        build(arr);
    }

    void build(vector<int>& arr) {
        ll sum = 0;
        for (int i = 0; i < arr.size(); i ++) {
            sum += arr[i];
            prefixSums[i] = sum;
        }
    }

    ll query(int l, int r) {
        ll lsum = (l == 0) ? 0 : prefixSums[l - 1];
        return prefixSums[r] - lsum;
    }

};

int main() {
    vector<int> arr = {1,2,3,4,5,1,2,3,4,5};
    PrefixSum psum(arr);
    cout << psum.query(0, 5) << endl;
    cout << psum.query(3, 4) << endl;
}