#include <bits/stdc++.h>
using namespace std;

// preprocess the data first. We divide 2, 4, 6, 8 ... by 2 so we can consider the sequence 1, 2, 3, ...
// then for nums, we only keep even numbers then divide by 2.
// we have to adjust the l, r indexes in the queries.

// we binary search the answer.
// let say we consider range 1...x, we find how many numbers in range [1, x] (after remove the needed numbers)
// if k is lesser then we know it is in the left half, else we know it is in the right half.
// to find out how many numbers we need to remove we also binary search in the nums array.
// to reduce the complexity, we maintain the range of to_remove numbers as we progress with the binary search
// iterations.
// so we do not need to binary search the entire to_remove numbers every iteration.


// the new queries l, r index is now [l, r).
// for easier coding, because cpp iterators need [begin, end).
pair<vector<int>, vector<vector<int>>> process(const vector<int>& nums, const vector<vector<int>>& queries) {
    vector<int> new_nums;
    vector<vector<int>> new_queries;
    for (int x : nums) {
        if (x % 2 != 0) continue;
        new_nums.push_back(x / 2);
    }

    
    for (auto& q : queries) {
        int l = ceil(nums[q[0]] / 2.0);
        int r = floor(nums[q[1]] / 2.0);
        int k = q[2];

        auto lit = lower_bound(new_nums.begin(), new_nums.end(), l);
        auto rit = upper_bound(new_nums.begin(), new_nums.end(), r);
        int ln = lit - new_nums.begin();
        int rn = rit - new_nums.begin();
        
        new_queries.push_back({ln, rn, k});
    }

    return {new_nums, new_queries};
}

int solve(const vector<int>& nums, const vector<int>& q) {
    int l = q[0], r = q[1], k = q[2];
    auto front = nums.begin() + l;
    auto lit = front;
    auto rit = nums.begin() + r;
    int s = 1, e = 2e9;

    while (s < e) {
        
        int m = s + ((e - s) >> 1);
        auto mit = upper_bound(lit, rit, m);
        int cnt = m - (mit - front);

        if (k <= cnt) {
            e = m;
            rit = mit;
        } else {
            s = m + 1;
            lit = mit;
        }
    }

    return s;
}

class Solution {
public:
    vector<int> kthRemainingInteger(vector<int>& nums, vector<vector<int>>& queries) {
        auto [new_nums, new_queries] = process(nums, queries);
        
        /*for (int x : new_nums) cout << x << " ";
        cout << endl;

        for (auto q : new_queries) {
            for (int x : q) cout << x << " ";
            cout << endl;
        }
        cout << endl;*/

        vector<int> out;
        for (const auto& q : new_queries) {
            out.push_back(solve(new_nums, q) * 2);
        }

        return out;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {2,5,8};
    vector<vector<int>> queries = {{0,2,4}};

    auto ans = sol.kthRemainingInteger(nums, queries);

    for (int x : ans) cout << x << ' ';
    cout << endl;
}