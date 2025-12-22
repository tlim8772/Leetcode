#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// very simple.
// let index i be the neg bal.
// do it greedily, start from the immediate neighbors, if can add until >= 0, done.
// if not move on to the next neighbor

class Solution {
public:

    int get_left(int i, int n) {
        return (i - 1 < 0) ? n - 1 : i - 1;
    }

    int get_right(int i, int n) {
        return (i + 1 >= n) ? 0 : i + 1;
    }
    long long minMoves(vector<int>& balance) {
        int n = balance.size();
        if (n == 1) return (balance[0] >= 0) ? 0 : -1;
        
        auto min_elem = min_element(balance.begin(), balance.end());
        if (*min_elem >= 0) return 0;

        int min_idx = min_elem - balance.begin();
        int bal = *min_elem;
        int l = get_left(min_idx, n), r = get_right(min_idx, n);
        int dist = 1;
        ll sum = 0;
        vector<bool> visited(balance.size(), false);
        while (bal < 0) {
            visited[l] = visited[r] = 1;
            
            int v = (l == r) ? balance[l] : balance[l] + balance[r];
            int to_add = min(v, -bal);
            sum += to_add * (ll) dist;
            bal += to_add;

            if (l == r) break;
            l = get_left(l, n), r = get_right(r, n);
            if (visited[l] || visited[r]) break;
            dist++;
        }

        return (bal < 0) ? -1 : sum;
    }
};

int main() {
    vector<double> x = {3,1,-1,2,3};
    int idx = (min_element(x.begin(), x.end()) - x.begin());
    cout << idx << endl;
}