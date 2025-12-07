#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// we process elems from right to left.
// suppose we are processing elem i.
// idea: we want a priority queue to store indexes s.t hp - sum(dmg[i + 1, j]) - req[j], and only the positive ones.
// due to lazy substraction, we need to store offset = sum(dmg[i + 1, n - 1])

// invariant: elems in the pq are hp + sum(dmg[j + 1, n - 1]) - req[j] for dmg[i]
// at index i, we substract sum(dmg[i, n - 1]), so we get hp - sum(dmg[i, j]) - req[j]

// so at elem i, we pop all elems in pq util pq.top() - offset - dmg[i] >= 0
// then if hp - dmg[i] - req[i] >= 0, we insert into pq hp + sum(dmg[i + 1, n - 1]) - req[i].

class Solution {
public:
    long long totalScore(int hp, vector<int>& damage, vector<int>& requirement) {
        priority_queue<int, vector<int>, greater<int>> pq;
        ll offset = 0;
        ll res = 0;

        for (int i = damage.size() - 1; i > -1; i--) {
            int dmg = damage[i], req = requirement[i];
            while (!pq.empty() && pq.top() - offset - dmg < 0) pq.pop();
            
            ll ans;
            if (hp - dmg - req >= 0) {
                ans = pq.size() + 1;
                pq.push(hp + offset - req);
            } else {
                ans = pq.size();
            }
            res += ans;

            offset += dmg;
        }

        return res;
    }
};

int main() {
    Solution sol;
    int hp = 2;
    vector<int> damage = {100000, 1};
    vector<int> requirement = {1,1};

    cout << sol.totalScore(hp, damage, requirement) << endl;
}