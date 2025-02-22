#include <bits/stdc++.h>
using namespace std;

// basically check for all ordered pairs, c1 and c2
// at each index, we store cntC1 - cntC2, where cntCi is the # of ci in array [0, i]
// for freq[c1] - freq[c2] of array[i, j] it is just prefix[j] - prefix[i - 1]
// so at index j, we want to find the minimum result[i], so that we get the maximum freq[c1] - freq[c2]
// we can store thr result of index j - 1, and then process additional results to get optimal result for j

// however, we need to take care of parities, so we need to store oo, oe, eo, ee, where (#c1, #c2) is odd/even
// also note that for subarray to be valid, #c1, #c2 >= 1, and length >= k
struct Res {
    int oo, oe, eo, ee;
};

struct Store {
    int cnt1, cnt2, sum;
};

class Solution {
public:
   


    int findMaxDiff(string& s, int k, int c1, int c2) {
        int best = -999999;
        Res res = {999999, 999999, 999999, 999999}; // min result of [0, l - 1]
        int latestC1 = -1;
        int latestC2 = -1;
        int cntC1 = 0, cntC2 = 0;
        vector<Store> prefixSums;

        int l = 0;


        for (int i = 0; i < s.size(); i ++) {
            if (s[i] - '0' == c1) {
                cntC1 ++;
                latestC1 = i;
            } else if (s[i] - '0' == c2) {
                cntC2 ++;
                latestC2 = i;
            }
            prefixSums.push_back({cntC1, cntC2, cntC1 - cntC2});
            //if (c1 == 0 && c2 == 1) cout << cntC1 << " " << cntC2 << endl;
            
            // we need to consider the subarray [0, i] too
            if (cntC1 % 2 && !(cntC2 % 2) && latestC1 != -1 && latestC2 != -1 && i >= k - 1) {
                best = max(best, cntC1 - cntC2);
            }

            int leftLim = min({i - k + 1, latestC1, latestC2});
            // l has to be lesser, as if leftmost valid index is n, i.e for all m <= n, [m, j] is valid
            // then we can only substract from prefix[l] and left, l < n
            while (l < leftLim) {
                Store& store = prefixSums[l];
                if (store.cnt1 % 2 && store.cnt2 % 2) {
                    // oo
                    res.oo = min(res.oo, store.sum);
                } else if (store.cnt1 % 2 && !(store.cnt2 % 2)) {
                    // oe
                    res.oe = min(res.oe, store.sum);
                } else if (!(store.cnt1 % 2) && store.cnt2 % 2) {
                    // eo
                    res.eo = min(res.eo, store.sum);
                } else if (!(store.cnt1 % 2) && !(store.cnt2 % 2)) {
                    // ee
                    res.ee = min(res.ee, store.sum);
                }
                l ++;
            }

            // now time to get best result
            int sum = cntC1 - cntC2;
            if (cntC1 % 2 && cntC2 % 2) {
                // oo, so get eo
                best = max(best, sum - res.eo);
            } else if (cntC1 % 2 && !(cntC2 % 2)) {
                // oe, so get ee
                best = max(best, sum - res.ee);
            } else if (!(cntC1 % 2) && cntC2 % 2) {
                // eo, so get oo
                best = max(best, sum - res.oo);
            } else if (!(cntC1 % 2) && !(cntC2 % 2)) {
                // ee, so get oe
                best = max(best, sum - res.oe);
            }
            
        }

        return best;



    }

    int maxDifference(string s, int k) {
        int best = -999999;
        for (int i = 0; i < 5; i ++) {
            for (int j = 0; j < 5; j ++) {
                if (i == j) continue;
                int ans = findMaxDiff(s, k, i, j);
                best = max(best, ans);
                //cout << i << " " << j << " " << ans << endl;
            }
        }
        return best;
    }
};

int main() {
    Solution sol;
    string s = "111320214";
    int k = 9;
    cout << sol.maxDifference(s, k) << endl;
}