#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// binary search
// put elements to the left as much as possible;
// so 1st element goes to pos start[0]
// for 2nd element, check if prev + d <= start[1] + d, if yes, put element leftmost as possible

class Solution {
public:
   
    
    bool possible(vector<int>& start, int d, int interval) {
        ll prev = start[0];
        for (int i = 1; i < start.size(); i ++) {
            if ((ll) start[i] + d < (ll) prev + interval) return false;
            prev = max((ll) start[i], (ll) prev + interval);
        }
        return true;
    }


    int binarySearch(vector<int>& start, int d, ll s, ll e) {
        while (s < e) {
            ll m = ((s + e) >> 1) + 1 - ((e - s + 1) & 1);
            if (possible(start, d, m)) {
                s = m;
            } else {
                e = m - 1;
            }
        }
        return s;
    }

    int maxPossibleScore(vector<int>& start, int d) {
        sort(start.begin(), start.end());
        return binarySearch(start, d, 0, 2000000000);
    }

};

int main() {
    Solution sol;
    vector<int> start = {0, 3, 6};
    int d = 2;
    cout << sol.maxPossibleScore(start, d) << endl;
}