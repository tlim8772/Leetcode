#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<int>* prefix;
    vector<vector<int>>* dp;

    void prefixSum(string& nums) {
        prefix = new vector(nums.size(), 0);
        int sum = 0;
        for (int i = 0; i < nums.size(); i ++) {
            sum += nums[i] - '0';
            (*prefix)[i] = sum;
        }
    }

    int rangeSum(int s, int e, int limit) {
        if (e > limit) {
            e = limit;
        }
        
        return (s == 0) ? (*prefix)[e] : (*prefix)[e] - (*prefix)[s - 1];
    }

    int helper(string& floor, int index, int numCarpets, int carpetLen) {
        if (index >= floor.size()) {
            return 0;
        } else if (numCarpets == 0) {
            return 0;
        } 
        
        else if ((*dp)[index][numCarpets] != -1) {
            return (*dp)[index][numCarpets];
        } else if (floor[index] == '0') {
            int ans = helper(floor, index + 1, numCarpets, carpetLen);
            (*dp)[index][numCarpets] = ans;
            return ans;
        } else {
            int whiteCovered = rangeSum(index, index + carpetLen - 1, floor.size() - 1);
            int nextIndex = min(index + carpetLen, (int) floor.size());
            int cover = whiteCovered + helper(floor, nextIndex, numCarpets - 1, carpetLen);
            int noCover = helper(floor, index + 1, numCarpets, carpetLen);
            int ans = max(cover, noCover);
            (*dp)[index][numCarpets] = ans;
            //cout << ans << " " << index << " " << numCarpets << endl;
            return ans;
        }
    }

    int minimumWhiteTiles(string floor, int numCarpets, int carpetLen) {
        dp = new vector(floor.size(), vector(numCarpets + 1, -1));
        prefixSum(floor);
        int covered = helper(floor, 0, numCarpets, carpetLen);
        return (*prefix)[floor.size() - 1] - covered;
    }

    void print(vector<int> x) {
        for (int i = 0; i < x.size(); i ++) {
            cout << x[i] << " ";
        }
        cout << endl;
    }


};

int main() {
    string f = "10110101";
    Solution s;
    cout << s.minimumWhiteTiles(f, 2, 2) << endl;
}