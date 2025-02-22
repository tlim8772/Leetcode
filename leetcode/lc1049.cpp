#include <bits/stdc++.h> 
using namespace std;

// partitioning stones into 2 groups + and -
// minimise the difference between the 2 groups, actually the + and - are just names

class Solution {
    public:
        vector<vector<int>>* dp;

        int helper(int index, int diff, vector<int> stones) {
            if (index == stones.size()) {
                return abs(diff);
            } else if ((*dp)[diff + 3000][index] != -1) {
                return (*dp)[diff + 3000][index];
            } else {
                // stone goes to group A
                int option1 = helper(index + 1, diff + stones[index], stones);
                //go to group B
                int option2 = helper(index + 1, diff - stones[index], stones);
                (*dp)[diff+ 3000][index] = min(option1, option2);
                return min(option1, option2);
            }
        }

        int lastStoneWeightII(vector<int>& stones) {
            dp = new vector(6001, vector(stones.size(), -1));
            return helper(0, 0, stones);
        }
};


int main() {
    Solution s;
    vector<int> lst = {31,26,33,21,40};
    cout << s.lastStoneWeightII(lst) << endl;
}