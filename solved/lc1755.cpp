#include <bits/stdc++.h>
using namespace std;

// split nums into 2 sets of 20 elems each.
// for each set generate all possible sums (all possible subsets).
// then use a map for 1 of the set to get the closest sum (something like 2 sum).

void generate_all_sums(int p, int sum, vector<int>& store, const vector<int>& nums) {
    if (p == nums.size()) {
        store.push_back(sum);
        return;
    }
    generate_all_sums(p + 1, sum + nums[p], store, nums);
    generate_all_sums(p + 1, sum, store, nums);

}


class Solution {
public:
    int minAbsDifference(vector<int>& nums, int goal) {
        if (nums.size() == 1) return min(abs(goal), abs(nums[0] - goal));

        int m = nums.size() / 2;
        vector<int> half1(nums.begin(), nums.begin() + m), half2(nums.begin() + m, nums.end());
        vector<int> store1, store2;
        generate_all_sums(0, 0, store1, half1);
        generate_all_sums(0, 0, store2, half2);

        /*
        for (int x : store1) cout << x << " ";
        cout << endl;
        for (int x : store2) cout << x << " ";
        cout << endl;
        */

        set<int> set2(store2.begin(), store2.end());
        int best = (int) 2e9;
        for (int h1 : store1) {
            int diff = goal - h1;
            auto it = set2.lower_bound(diff);
            if (it != set2.end()) {
                int res = abs(*it + h1 - goal);
                best = min(best, res);
            }
            if (it != set2.begin()) {
                int res = abs(*--it + h1 - goal);
                best = min(best, res);
            }
        }
        return best;

    }
};

int main() {
    Solution sol;
    vector<int> nums = {5,-7,3,5};
    int goal = 6;
    int ans = sol.minAbsDifference(nums, goal);
    println("Ans is {}", ans);
}