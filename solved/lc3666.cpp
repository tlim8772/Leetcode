#include <bits/stdc++.h>
using namespace std;

// the same old trick, use a treemap to avoid revisting states.
// let i = # of 1s. # of 0s is n - i
// we can go to i - k, i - k + 2, i - k + 4 ... i + k.
// let left be the smallest possible next state and right be the largest possible next state.
// use a set to find lower bound of left.

tuple<int, int> find_bounds(int state, int n, int k) {
    int l_temp = min(state, k);
    int left = state - l_temp + (k - l_temp);

    int r_temp = min(n - state, k);
    int right = state + r_temp - (k - r_temp);

    return {left, right};
}

class Solution {
public:
    int minOperations(string s, int k) {
        int start = 0;
        for (char c : s) {
            if (c == '1') start++;
        }

        vector<int> dists(s.size() + 1, -1);
        set<int> even, odd;

        for (int i = 0; i <= s.size(); i++) {
            if (i == start) continue;
            (i % 2 == 0) ? even.insert(i): odd.insert(i);
        }

        
        int lvl = 0;
        deque<int> q;
        
        q.push_back(start);

        while (!q.empty()) {
           
            for (int len = q.size(); len > 0; len--) {
                int state = q.front(); q.pop_front();
                dists[state] = lvl;

                auto [left, right] = find_bounds(state, s.size(), k);
            
                set<int>& mySet = (left % 2 == 0) ? even : odd;
                
                while (!mySet.empty()) {
                    auto it = mySet.lower_bound(left);
                    if (it == mySet.end() || *it > right) break;
                    q.push_back(*it);
                    mySet.erase(it);
                }
            }
            lvl++;
        }

        return dists[s.size()];
    }
};

int main() {
    Solution sol;
    string s = "001";
    int k = 3;
    int ans = sol.minOperations(s, k);
    cout << ans << endl;
}