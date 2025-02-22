#include <vector>
#include <iostream>
#include <algorithm> 

using namespace std;


class Solution {
    public:
        vector<vector<vector<int>>>* dp;

        vector<vector<int>>* collect(vector<int> nums) {
            sort(nums.begin(), nums.end());
            vector<int> a = vector({0, 0});
            vector<vector<int>>* out = new vector(0, vector(0, 0));
            int curr = nums[0];
            int sum = 0;
            for (int i = 0; i < nums.size(); i ++) {
                if (nums[i] == curr) {
                    sum += nums[i];
                } else {
                   a[0] = curr;
                   a[1] = sum;
                   (*out).push_back(a);
                   a = vector({0, 0});
                   curr = nums[i];
                   sum = nums[i];
                }
            }
            a[0] = curr;
            a[1] = sum;
            (*out).push_back(a);
            return out;
        }

        int helper(int prev, int direc, int index, vector<vector<int>>* nums) {
            if (index <= -1 || index >= (*nums).size()) {
                return 0;
            } else {
                //cout << prev;
                int canUse = (prev == 999999999) ? 1 : abs((*nums)[prev][0] - (*nums)[index][0]) != 1;
                //cout << canUse << endl;
                if ((*dp)[canUse][direc][index] != -1) {
                    return (*dp)[canUse][direc][index];
                } else if (canUse == 1) {
                    if (direc == 1) {
                        int use = (*nums)[index][1] + helper(index, direc, index + 1, nums);
                        int noUse = helper(prev, direc, index + 1, nums);
                        (*dp)[canUse][direc][index] = max(use, noUse);
                        return max(use, noUse);
                    } else {
                        int use = (*nums)[index][1] + helper(index, direc, index - 1, nums);
                        int noUse = helper(prev, direc, index - 1, nums);
                        (*dp)[canUse][direc][index] = max(use, noUse);
                        return max(use, noUse);
                    }
                } else {
                    if (direc == 1) {
                        int noUse = helper(prev, direc, index + 1, nums);
                        (*dp)[canUse][direc][index] = noUse;
                        //cout << noUse << endl;
                        return noUse;
                    } else {
                        int noUse = helper(prev, direc, index - 1, nums);
                        (*dp)[canUse][direc][index] = noUse;
                        return noUse;
                    }
                }
            }
        }

        int deleteAndEarn(vector<int>& nums) {
            vector<vector<int>>* collected = collect(nums);
            /*for (int i = 0; i < collected.size(); i ++) {
                cout << collected[i][0] << " " << collected[i][1];
                cout << endl;
            }*/
            
            dp = new vector(2, vector(2, vector((*collected).size(), -1)));
            int use1st = (*collected)[0][1] + helper(0, 1, 1, collected);
            int noUse = helper(999999999, 1, 1, collected);
            return max(use1st, noUse);
            
        }
};

int main() {
    Solution s;
    vector<int> lst = vector(100000, 0);
    for (int i = 0; i < lst.size(); i ++) {
        lst[i] = i / 10;
    }
    
    int ans = s.deleteAndEarn(lst);
    //cout << s.dp[0][1][1];
    cout << ans << endl;
    //cout << max(10, -78) << endl;
    return 0;

}