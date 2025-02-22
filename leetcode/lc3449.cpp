#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// binary search, greedy
// let x be the min score each game must get, for each game we count min number of times it must be played
// a valid sequence is like 0 1 2 1 0 1 2 (consective elem diff is 1)
// we greedily fill the 1st game by flipping back and forth e.g 0 1 0 1
// suppose not, 0 1 ... and 0 appears somewhere else. 
// case 1: 0 is last then we have ... 1 0, take the (1, 0) put it like this 0 1 0 1 ...
// case 2: 0 is not last elem, then we have 1 0 1 ..., take (1, 0), put it 0 1 0 1 ... 1 ...

// however, we can add more moves if needed. For the last element, we have to use more2nd last elem
// for the rest, use more of the next elem. The elems added does not matter, only the num of elems added

class Solution {
public:
    bool isValid(vector<ll>& nums, int extra) {
        //vector<ll> temp = nums;
        for (int i = 0; i < nums.size(); i ++) {
            if (i == nums.size() - 1) {
                if (nums[i] < 0) {
                    extra -= abs(nums[i]);
                    if (extra < 0) return false;
                } else if (nums[i] == 0 || nums[i] == 1) {
                    return true;
                } else {
                    extra -= (nums[i] - 1);
                    if (extra < 0) return false;
                }
            } else {
                if (nums[i] <= 0) {
                    extra -= (abs(nums[i]) + 1);
                    if (extra < 0) return false;
                } else {
                    nums[i + 1] -= (nums[i] - 1);
                }
            }
        }
        return true;
    }

    long long maxScore(vector<int>& points, int m) {
        vector<ll> movesNeeded(points.size(), 0);
        ll s = 0, e = 1e15;

        while (s < e) {
            ll mid = (s + e) >> 1;
            if ((e - s + 1) % 2 == 0) mid ++;

            ll sum = 0;
            for (int i = 0; i < points.size(); i ++) {
                movesNeeded[i] = (ll) ceil(mid / (double) points[i]);
                sum += movesNeeded[i];

                if (sum > m) break; // break early to prevent long long overflow
            }

            bool canMake = sum <= (ll) m && isValid(movesNeeded, m - sum);
            if (canMake) s = mid;
            else e = mid - 1;
        }

        return s;
    }



};

int main() {
    vector<int> score = {2,4};
    int m = 3;    
    Solution sol;
    cout << sol.maxScore(score, m);
}