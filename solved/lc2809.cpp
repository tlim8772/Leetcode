/*
some lemmas:
1. every second, we must set an elem to 0.

2. the second we get all elems to 0 is also a second where we set an elem to 0

3. we only set an elem to 0 once. Suppose we do it twice for the elem. The 1st time we set that elem
   to 0, it is redundant, we remove at operation, shift all operations to the right by 1, then set the
   elem to 0 at the 2nd time - 1.

4. let (si, ai) means initial value of elem, and the val to add every second.
   for elems which are set to 0, ai is in increasing order.
   suppose not, we set si to 0 1st, and sj to 0 later and aj < ai.
   then we can set sj to 0 1st, and si to 0 later, because once you set an elem to 0, its 
   initial value does not matter, only ai. we will only decrease total sum by swapping

let f(arr, k) = min total sum we can achieve using k set to 0 operations.
unfortunately, this function is not monotonic non-increasing, so we cannot binary search on k.
so basically, we have to search for every k in [1, len(nums)]

let dp(i, num_set_0) = max amount we can save if we do num_set_0 ops in arr[0:i].
this is indepedent of total_num_set ops we do.
from (1), we amount we save is simply nums1[i] + num_set_0 * nums2[i], because we have num_set_0 - 1 seconds
behind us.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int L;
    vector<int> store;
    vector<pair<int,int>> start_and_add;

    int dp(int i, int num_set_0) {
        if (num_set_0 == 0) {
            return 0;
        } else if (i == -1) {
            return -2000000000;
        }
        int pos = i * L + num_set_0;
        if (store[pos] != -1) {
            return store[pos];
        }

        int no_set = dp(i - 1, num_set_0);
        int set = start_and_add[i].first + num_set_0 * start_and_add[i].second + dp(i - 1, num_set_0 - 1);
        return store[pos] = max(no_set, set);


    }
    int minimumTime(vector<int>& nums1, vector<int>& nums2, int x) {
        L = nums1.size() + 1;
        store = vector(L * (L - 1), -1);

        for (int i = 0; i < nums1.size(); i++) {
            start_and_add.emplace_back(nums1[i], nums2[i]);
        }
        sort(start_and_add.begin(), start_and_add.end(), [](auto& p1, auto& p2) {return p1.second < p2.second;});
        
        int sum1 = accumulate(nums1.begin(), nums1.end(), 0), sum2 = accumulate(nums2.begin(), nums2.end(), 0);
        for (int i = 0; i <= nums1.size(); i++) {
            //printf("%d %d\n", i, sum1 + i * sum2 - dp(nums1.size() - 1, i));
            if (sum1 + i * sum2 - dp(nums1.size() - 1, i) <= x) return i;
        }
        return -1;
    }
};

int main() {
    Solution sol;
    vector<int> nums1 = {1,2,3};
    vector<int> nums2 = {1,2,3};
    int x = 4;
    cout << sol.minimumTime(nums1, nums2, x) << endl;

}