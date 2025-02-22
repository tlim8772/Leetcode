#include <bits/stdc++.h> 
using namespace std;

class Solution {
    public:
        vector<vector<int>>* dp;


        string to_binary(int val) {
            if (val == 1) {
                return "1";
            } else if (val % 2 == 1) {
                return to_binary(val / 2) + "1";
            } else {
                return to_binary(val / 2) + "0";
            }
        }

        // invariant is that at this stage, we have taken eaxtly the first index_k digits of k in s
        
        int helper(string s, string k, int index_s, int index_k) {
            if (index_k == k.size()) {
                return 0;
            } else if (index_s == s.size()) {
                return 0;
            } else if ((*dp)[index_s][index_k] != -1) {
                return (*dp)[index_s][index_k];
            } else {
                char curr_k = k[index_k];
                char curr_s = s[index_s];
                if (curr_k == '1') {
                    if (curr_s == '0') {
                        int take = min(s.size() - index_s, k.size() - index_k);
                        int no_take = helper(s, k, index_s + 1, index_k);
                        int ans = max(take, no_take);
                        (*dp)[index_s][index_k] = ans;
                        return ans;
                    } else {
                        int take = 1 + helper(s, k, index_s + 1, index_k + 1);
                        int no_take = helper(s, k, index_s + 1, index_k);
                        int ans = max(take, no_take);
                        (*dp)[index_s][index_k] = ans;
                        return ans;
                    }
                } else {
                    if (curr_s == '0') {
                        int take = 1 + helper(s, k, index_s + 1, index_k + 1);
                        //int no_take = helper(s, k, index_s + 1, index_k);
                        int ans = take;
                        (*dp)[index_s][index_k] = ans;
                        return ans;
                    } else {
                        // can take "1" when curr_k is "0", in this case can take a max of digits left in k - 1
                        int take = min(s.size() - index_s, k.size() - index_k - 1);
                        int no_take = helper(s, k, index_s + 1, index_k);
                        int ans = max(take, no_take);
                        (*dp)[index_s][index_k] = ans;
                        return ans;
                    }
                }
            }
        }

        int helper2(string s, string k, int index) {
            if (index == s.size()) {
                return 0;
            } else if (s[index] == '0') {
                return 1 + helper2(s, k, index + 1);
            } else {
                int take = 1 + helper(s, k, index + 1, 1);
                int no_take = helper2(s, k, index + 1);
                if (index == 0) {
                    //cout << take << endl;
                    //cout << no_take << endl;
                }
                int ans = max(take, no_take);
                return ans;
            }
        }

         int longestSubsequence(string s, int k) {
            string k_new = to_binary(k);
            dp = new vector(s.size(), vector(k_new.size(), -1));
            int ans = helper2(s, k_new, 0);
            return ans;
        }

};

int main() {
    Solution s;
    int ans = s.longestSubsequence("00011", 72257365);
    cout << ans << endl;
    cout << s.to_binary(9) << endl;
    for (int i = 0; i < (s.dp)->size(); i ++) {
        for (int j = 0; j < (*(s.dp))[0].size(); j ++) {
            cout << (*(s.dp))[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
