#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> matrix;
    vector<vector<int>> dp;
    vector<vector<int>> routing;

    int mostBack(string& s1, string& s2) {
        for (int i = 0; i < s1.size(); i ++) {
            int p1 = i;
            int p2 = 0;
            int flag = 1;
            while (p1 < s1.size() && p2 < s2.size()) {
                if (s1[p1] == s2[p2]) {
                    p1 ++;
                    p2 ++;
                } else {
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                return s1.size() - i;
            }
        }
        return 0;
    }

    void process(vector<string>& words) {
        matrix = vector(words.size(), vector(words.size(), -1));
        for (int i = 0; i < words.size(); i ++) {
            for (int j = 0; j < words.size(); j ++) {
                if (i != j) {
                    matrix[i][j] = mostBack(words[i], words[j]);
                }
            }
        }
    }

    int helper(int lastWordIndex, int notUsed, vector<string>& words) {
        if (notUsed == ((1 << words.size()) - 1)) {
            return words[lastWordIndex].size();
        } else if (dp[lastWordIndex][notUsed] != -1) {
            return dp[lastWordIndex][notUsed];
        } else {
            int minLen = 5000;
            int next = -1;
            for (int i = 0; i < words.size(); i ++) {
                if (((notUsed >> i) & 1) == 0) {
                    int back = matrix[lastWordIndex][i];
                    int ans = words[lastWordIndex].size() - back + helper(i, notUsed + (1 << i), words);
                    if (ans < minLen) {
                        next = i;
                        minLen = ans;
                    }
                }
            }
            dp[lastWordIndex][notUsed] = minLen;
            routing[lastWordIndex][notUsed] = next;
            return minLen;
        }
    }

    string shortestSuperstring(vector<string>& words) {
        dp = vector(words.size(), vector((1 << words.size()), -1));
        routing = vector(words.size(), vector((1 << words.size()), -1));
        process(words);
        int start = -1;
        int minLen = 9999;
        for (int i = 0; i < words.size(); i ++) {
            int res = helper(i, 1 << i, words);
            if (res < minLen) {
                minLen = res;
                start = i;
            }
        }
        //cout << minLen << endl;
        string out = words[start];
        int used = 1 << start;
        //cout << start << endl;
        while (true) {
            int next = routing[start][used];
            //cout << next << endl;
            if (next == -1) {
                break;
            } else {
                //cout << next << endl;
                int back = matrix[start][next];
                int len = words[next].size();
                out += words[next].substr(back, len - back);
                used += (1 << next);
                start = next;
            }
        }
        return out;


    }


};

int main() {
    Solution s;
    string s1 = "ttcatg";
    string s2 = "atgcatc";
    //cout << s.mostBack(s1, s2) << endl;
    vector<string> words = {"alex", "loves", "leetcode"};
    cout << s.shortestSuperstring(words);
}