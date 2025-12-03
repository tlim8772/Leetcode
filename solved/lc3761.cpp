#include <bits/stdc++.h>
using namespace std;

/*
use a hashmap to s.t hashmap[num] = set<int>, i.e a set containing all the indices s.t arr[idx] = num.
reverse the number, query the hashmap and set to find the closest indice.
*/

int reverse(int x) {
    string s = to_string(x);
    reverse(s.begin(), s.end());
    
    int out = 0, p = 0;
    for (int i = s.size() - 1; i > -1; i--) {
        int d = s[i] - '0';
        out += d * (int) pow(10, p);
        p++;
    }

    return out;
}

class Solution {
public:
    int minMirrorPairDistance(vector<int>& nums) {
        unordered_map<int, set<int>> indices;
        int best = 999999999;
        for (int i = 0; i < nums.size(); i++) {
            auto& s = indices[nums[i]];
            if (nums[i] == reverse(nums[i]) && s.size() > 0) {
                int last = *--s.end();
                best = min(best, i - last);
            }
            s.insert(i);
        }

        
        for (int i = 0; i < nums.size(); i++) {
            int r = reverse(nums[i]);
            if (!indices.contains(r) || r == nums[i]) continue;

            auto& s = indices[r];
            auto it = s.lower_bound(i);
                
            if (it != s.end()) {
                best = min(best, *it - i);
            }

        }

        return (best == 999999999) ? -1 : best;
    }
};

int main() {
    vector<int> arr = {21,120};
    Solution sol;
    cout << sol.minMirrorPairDistance(arr) << endl;
}