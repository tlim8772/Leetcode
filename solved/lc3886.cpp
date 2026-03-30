#include <bits/stdc++.h>
using namespace std;


// to check whether range [l, r] is cyclic sortable.
// find index i where arr[i] < arr[i + 1].
// then check whether arr[l, i], arr[i + 1, r] are sorted
// and that arr[r] <= arr[l].
// of course, if dont have, means arr[l, r] is sorted already.


// checks whether range [l, r] is cyclic sortable
tuple<bool, int, int> is_cyclic_sortable(int l, int r, const vector<int>& nums) {
    if (r == l) return {true, nums[l], nums[l]};

    int mismatch_cnt = 0;
    int split = -1;
    for (int i = l; i < r; i++) {
        if (nums[i] > nums[i + 1]) {
            mismatch_cnt++;
            if (split == -1) split = i;
        }
    }
    
    if (split == -1) return {true, nums[l], nums[r]};
    if (mismatch_cnt > 1 || nums[r] > nums[l]) return {false, -1, -1};

    return {true, nums[split + 1], nums[split]};
    

}

bool can(int k, const vector<int>& nums) {
    int prev_ma = -1;
    for (int i = 0; i < nums.size(); i += k) {
        auto [b, mi, ma] = is_cyclic_sortable(i, i + k - 1, nums);
        if (!b) return false;

        if (i == 0) {
            prev_ma = ma;
        } else {
            if (prev_ma > mi) {
                return false;
            }
            prev_ma = ma;
        }
    }
    return true;
}

class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int cnt = 0;
        int len = nums.size();
        int lim = (int) floor(sqrt(len));

        for (int i = 1; i <= lim; i++) {
            if (len % i != 0) continue;
            bool b1 = can(i, nums);
            bool b2 = can(len / i, nums);
            //cout << b1 << " " << b2 << endl;

            if (b1) cnt += i;
            if (b2 && i != len / i) cnt += len / i;
        }
        return cnt;
    }
};

int main() {
    Solution sol;

    vector<int> nums = {1,2,3};
    int ans = sol.sortableIntegers(nums);
    cout << ans << endl;
}
