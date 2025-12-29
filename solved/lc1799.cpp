#include <bits/stdc++.h>
using namespace std;

// simple backtracking problem.
// just enumerate all possible n pairs from 2n numbers.
// start with index 0, pair with index i, 
// move to index 1, if taken skip, else pair with index k,
// and so on.
// after that, get the gcd of the pairs, sort in increasing order
class Solution {
public:
    int helper2(const vector<int>& pairs) {
        vector<int> temp = pairs;
        sort(temp.begin(), temp.end());
        int sum = 0;
        for (int i = 1; i <= pairs.size(); i++) sum += i * temp[i - 1];
        return sum;
    }

    int helper(int idx, int bm, vector<int>& pairs, const vector<int>& nums) {
        if (pairs.size() == nums.size() / 2) return helper2(pairs);
        
        bool used = (bm >> idx) & 1;
        if (used) return helper(idx + 1, bm, pairs, nums);

        int best = 0;
        for (int i = idx + 1; i < nums.size(); i++) {
            if ((bm >> i) & 1) continue;
            pairs.push_back(gcd(nums[idx], nums[i]));
            int res = helper(idx + 1, bm + (1 << idx) + (1 << i), pairs, nums);
            best = max(best, res);
            pairs.pop_back();
        }

        return best;
    }

    int maxScore(vector<int>& nums) {
        vector<int> pairs;
        return helper(0, 0, pairs, nums);
    }
};



int main() {
    Solution sol;
    vector<int> nums = {109497,983516,698308,409009,310455,528595,524079,18036,341150,641864,913962,421869,943382,295019};
    cout << sol.maxScore(nums) << endl;
}