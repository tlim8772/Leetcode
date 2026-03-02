#include <bits/stdc++.h>
using namespace std;

// 2 cases:: even, odd and odd, even.
// if no need to change elem, then must not change.
// else we must +1 or -1.
// gather all no need to change elem and need to change elem.
// have 2 cases, min, max of no need to change is the same or different (i.e diff of >= 1)
// for the latter, +1 to all elem < min and -1 to all elems > min. 
// no need to change elems in between, as they will be in [min_res, max_res] anyway.
// for the former it is more complicated.
// for example, min_res is 1, and we have 1, 4. the best result is to (+1 to 1) and -1 to 4
// if min_res = 4, and we have 1, 4, the best result is to +1 to 1 and (-1 to 4)

int helper1(int min_res, const vector<int>& sorted) {
    vector<int> temp = sorted;
    int mi = *min_element(temp.begin(), temp.end());
    int ma = *max_element(temp.begin(), temp.end());

    if (min_res == mi) {
        return (ma == mi) ? 1 : max(ma - 1, mi + 1) - min_res;
    } else if (min_res == ma) {
        return (ma == mi) ? 1 : min_res - min(mi + 1, ma - 1);
    }

    for (int &x : temp) {
        if (x < min_res) x++;
        else x--;
    }

    mi = *min_element(temp.begin(), temp.end());
    ma = *max_element(temp.begin(), temp.end());

    return abs(max(ma, min_res) - min(mi, min_res));
}

int helper2(int min_res, int max_res, const vector<int>& sorted) {
    vector<int> temp = sorted;
    for (int &x : temp) {
        if (x < min_res) x++;
        else if (x > max_res) x--;
    }
    int mi = *min_element(temp.begin(), temp.end());
    int ma = *max_element(temp.begin(), temp.end());
    return abs(max(ma, max_res) - min(mi, min_res));
}

// 0 is even, 1 is odd.
pair<int, int> helper(const vector<int>& nums, int parity) {
    int min_res = (int) 2e9, max_res = (int) -2e9;
    vector<int> store;
    for (int i = 0; i < nums.size(); i++) {
        int x = nums[i];
        int x_p = (x % 2 + 2) % 2;
        int p = (parity == 0) ? i % 2 : ((i + 1) % 2);
        if (x_p == p) {
            min_res = min(x, min_res);
            max_res = max(x, max_res);
        } else {
            store.push_back(x);
        }
    }

    if (store.size() == 0) {
        return {0,  max_res - min_res};
    }

    int ans;
    if (min_res == max_res) {
        ans = helper1(min_res, store);
    } else {
        ans = helper2(min_res, max_res, store);
    }

    return {store.size(), ans};
   
}

class Solution {
public:
    vector<int> makeParityAlternating(vector<int>& nums) {
        auto [a, b] = helper(nums, 0);
        auto [c, d] = helper(nums, 1);
        if (a < c) {
            return {a, b};
        } else if (c < a) {
            return {c, d};
        } else if (b < d) {
            return {a, b};
        } else {
            return {c, d};
        }
    }
};

int main() {
    Solution sol;
    vector<int> nums = {-5, -5, -7, -5, -7, -5};
    vector<int> ans = sol.makeParityAlternating(nums);
    println("Ans: [{} {}]", ans[0], ans[1]);
}