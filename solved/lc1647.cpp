#include <bits/stdc++.h>
using namespace std;
/*
get the frequency of each character, then sort in increasing order.
if the frequency val is not seen before, keep it, else change it to the highest available number.
suppose not, and we delete more than neccessary. 
the closest value must be used by another char otherwise not optimal.
we can swap the 2 values. the # of deletions will remain the same.
*/

class Solution {
public:
    int minDeletions(string s) {
        unordered_set<int> used;
        unordered_map<char,int> char_freqs;
        for (char c : s) char_freqs[c]++;

        vector<pair<char,int>> values(char_freqs.begin(), char_freqs.end());
        sort(values.begin(), values.end(), [](auto p1, auto p2) {return p1.second < p2.second;});
        
        set<int> free;
        for (int i = 1; i <= values.back().second; i++) free.insert(i);
        
        int sum = 0;
        for (auto [k, v] : values) {
            if (!used.contains(v)) {
                free.erase(v);
                used.insert(v);
            } else {
                auto it = free.lower_bound(v);
                if (it == free.begin()) {
                    sum += v;
                } else {
                    it--;
                    sum += (v - *it);
                    used.insert(v - *it);
                    free.erase(it);
                }
            }
        }

        return sum;
    }
};

int main() {
    Solution sol;
    string s = "aaabbbcc";
    cout << sol.minDeletions(s) << endl;
}