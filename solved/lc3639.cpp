#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// simple problem
// add how many new substrings created as we change characters into *
// we find the the greatest * to the left (or 0 if none) and smallest * to the right
// (or len - 1 if none) and calculate accordingly

class Solution {
public:
    

    // l <= i <= r
    inline ll numSubStringsCreated(int i, int l, int r) {
        int left = i - l, right = r - i;
        return 1 + left + right + (ll) left * right;
    }
    
    int minTime(string s, vector<int>& order, int k) {
        set<int> mySet;
        ll cnt = 0;

        for (int i = 0; i < order.size(); i++) {
            int pos = order[i];
            
            // strictly less than is the annoying part
            auto lptr = mySet.lower_bound(pos);
            int l = 0;
            if (lptr == mySet.begin()) {
                l = 0;
            } else {
                // *--it means decrement first then get the value
                l = *--lptr + 1;
            }
 
            auto rptr = mySet.upper_bound(pos);
            int r = (rptr == mySet.end()) ? s.size() - 1 : *rptr - 1;

            ll res = numSubStringsCreated(pos, l, r);
            //cout << l << " " << pos << " " << r << endl;
            //cout << res << endl;
            cnt += res;

            mySet.insert(pos);

            if (cnt >= k) return i;
        }

        return -1;
    }
};

int main() {
    Solution sol;

    string s = "cat";
    vector<int> order = {2,1,0};
    int k = 6;

    cout << sol.minTime(s, order, k) << endl;
}