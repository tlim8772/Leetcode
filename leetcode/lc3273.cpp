#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// we only need to know the time to kill, which is ceil(health / damage)
// for (ti, di) (ti+1, di+1) i.e we kill person (ti, di) then kill person (ti+1, di+1)
// what happens when we flip the 2, the diff in damage is -(di+1)(ti) + (ti+1)(di)
// = (ti+1)(ti)(di / ti - di+1 / ti+1)
// so if di / ti < di+1 / ti+1 (ti, di) swapping the 2 will reduce damage
// this shows di / ti is a non-increasing sequence
// hence greedy choice is to take largest di / ti as 1st to kill
// suppose not, and sequence is still optimal, whatever position largest di / ti is, we can swap it to the front
// and damage taken can only decrease

struct Pair {
    ll p0, p1;
    Pair(ll x, ll y): p0(x), p1(y) {}
};

class Solution {
public:
    long long minDamage(int power, vector<int>& damage, vector<int>& health) {
        vector<Pair> arr;
        for (int i = 0; i < damage.size(); i ++) {
            arr.push_back(Pair((ll) ceil((double) health[i] / power), damage[i]));
        }
        
        sort(arr.begin(), arr.end(), [] (Pair& a, Pair& b) -> bool {
            return (double) a.p1 / (double) a.p0 > (double) b.p1 / (double) b.p0;
        });

        ll sum = 0;
        ll prefix = 0;
        for (Pair& p : arr) {
            //cout << p.p0 << " " << p.p1 << endl;
            prefix += p.p0;
            sum += p.p1 * prefix;
        }
        return sum;
    }

};

int main() {
    int power = 4;
    vector<int> damage = {1,2,3,4};
    vector<int> health = {4,5,6,8};
    cout << Solution().minDamage(power, damage, health);
}