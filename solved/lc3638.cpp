#include <bits/stdc++.h>
using namespace std;

// simple greedy
// start from 0, take until encounter 1st index where it is not the max
// proof suppose not (so instead of index 3, we go to index 5 and this is the optimal solution)
// then we replace [0,5] with [0,3] done

class Solution {
public:
    int maxBalancedShipments(vector<int>& weight) {
        int cnt = 0;

        int ma = -1;
        for (int i = 0; i < weight.size(); i++) {
            if (weight[i] < ma) {
                cnt++;
                ma = -1;
            } else {
                ma = weight[i];
            }
        }
        return cnt;
    }
};