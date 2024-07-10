#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

class Solution {
// dp[prev][index] min operations needed to remove adjacent almost equal characters, given prev char is prev, cannot change
public:
    vector<vector<int>>* dp;

    bool checkValid(int c, int prev, int next) {
        return abs(c - prev) > 1;
    }

    int helper(string& word, int index, int prev) {
        if (index == word.size()) {
            return 0;
        } else if ((*dp)[prev][index] != -1) {
            return (*dp)[prev][index];
        } else {
            int next = (index != word.size() - 1) ? word[index] - 'a' : 27;
            int res = 999999999;
            for (int i = 0; i < 26; i ++) {
                if (i != word[index] - 'a' && checkValid(i, prev, next)) {
                    int ans = 1 + helper(word, index + 1, i);
                    res = min(res, ans);
                } else if (i == word[index] - 'a' && checkValid(i, prev, next)) {
                    int ans = helper(word, index + 1, i);
                    res = min(res, ans);
                }
            }
            (*dp)[prev][index] = res;
            return res;
        }
    }
    int removeAlmostEqualCharacters(string word) {
        dp = new vector(28, vector(word.size(), -1));
        int ans = helper(word, 0, 27);
        return ans;

    }

};

int main() {
    Solution s;
    string word = "zyxyxyz";
    cout << s.removeAlmostEqualCharacters(word) << endl;
}