#include <bits/stdc++.h>
using namespace std;

// sort prices, then binary search the maximum gap. gap here is the minimum of the absolute difference between
// prices chosen, when prices are sorted in increasing order
class Solution {
public:

    bool canMake(vector<int>& price, int k, int gap) {
        // always choose price[0]
        int prev = price[0];
        int p = 1;
        k--;

        while (p < price.size() && k > 0) {
            if (price[p] - prev >= gap) {
                k--;
                prev = price[p];
            }
            p++;
        }

        return k == 0;
    }
    
    
    int maximumTastiness(vector<int>& price, int k) {
        sort(price.begin(), price.end());

        int s = 0, e = 999999999;
        while (s < e) {
            int m = s + ((e - s + 1) >> 1);

            if (canMake(price, k, m)) {
                s = m;
            } else {
                e = m - 1;
            }
        }

        return s;
    }
};