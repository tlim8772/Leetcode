#include <bits/stdc++.h>
using namespace std;

// just LIS with strings instead, 
// new_str1 = s0[0] + s1[0] ... sN-1[0]
// new_str2 = s0[1] + s1[1] ... sN-1[1]

// can only jump from new_str_i to new_str_j if for all indices, new_str_i[k] <= new_str_j[k]/

class Solution {
public:
    vector<string> arr;
    vector<int> store;

    bool comp(const string& s1, const string& s2) {
        for (int i = 0; i < s1.size(); i++) {
            if (s1[i] > s2[i]) return false;
        }
        return true;
    }

    void process_strings(vector<string>& strs) {
        for (int i = 0; i < strs[0].size(); i++) {
            string s;
            for (auto& str : strs) s += str[i];
            arr.push_back(s);
        }   
    }

    int dp(int i) {
        if (store[i] != -1) return store[i];
        if (i == arr.size() - 1) return 1;

        int best = 1;
        for (int j = i + 1; j < arr.size(); j++) {
            if (comp(arr[i], arr[j])) best = max(best, 1 + dp(j));
        }
        return store[i] = best;
    }


    int minDeletionSize(vector<string>& strs) {
        process_strings(strs);
        store = vector(strs[0].size(), -1);
        
        int best = 0;
        for (int i = 0; i < strs[0].size(); i++) best = max(best, dp(i));
        return strs[0].size() - best;
    }
};

int main() {
    Solution sol;
    vector<string> strs = {"baabab"};
    cout << sol.minDeletionSize(strs) << endl;
}