#include <bits/stdc++.h> 
using namespace std;

class Solution {
public:

    vector<vector<int>>* compress(string s) {
        vector<vector<int>>* out = new vector(0, vector(0, 0));
        int curr = s[0] - 'a';
        int count = 0;
        for (int i = 0; i < s.size(); i ++) {
            if (s[i] - 'a' == curr) {
                count += 1;
            } else {
                vector<int> res = {curr, count};
                out->push_back(res);
                curr = s[i] - 'a';
                count = 1;
            }
        }
        vector<int> res = {curr, count};
        out->push_back(res);
        return out;
    }

    int maximumLength(string s) {
        vector<vector<int>>* store = compress(s);
        unordered_map<int, unordered_map<int, int>> map;
        int maxRes = -1;
        for (int i = 0; i < store->size(); i ++) {
            vector<int>& curr = store->at(i);
            int c = curr[0];
            int count = curr[1];
            for (int i = count; i >= 1; i --) {
                map[c][i] += count - i + 1;
                if (map[c][i] >= 3) {
                    maxRes = max(maxRes, i);
                }
            }
        }
        return maxRes;
    }


};

int main() {
    Solution s;
    string ss = "abcaba";
    /*vector<vector<int>>* test = s.compress(ss);
    for (int i = 0; i < test->size(); i ++) {
        cout << test->at(i).at(0) << " " << test->at(i).at(1) << endl;
    }*/

    cout << s.maximumLength(ss) << endl;

    return 0;
}