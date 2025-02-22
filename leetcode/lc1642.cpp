#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;


// for each i, check if we can reach i
// how? we sum all the bricks needed to reach i, for the ladders, we use ladders for the top k bricks needed, k = #ladders
template <typename T>
class PQ {
public:
    priority_queue<T, vector<T>, greater<T>> pq;
    int size;
    long long sum;
    int limit;

    PQ(int limit) {
        size = 0;
        sum = 0;
        this->limit = limit;
    }

    void push(long long x) {
        if (limit == 0) {
            return;
        } else if (size < limit) {
            pq.push(x);
            size += 1;
            sum += x;
        } else {
            long long min = pq.top();
            if (x > min) {
                pq.pop();
                pq.push(x);
                sum += x - min;
            }
        }
    }
};


class Solution {
public:
     int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        PQ<long long> pqLimited(ladders);
        long long brickSum = 0;
        int best = 0;
        for (int i = 1; i < heights.size(); i ++) {
            long long  diff = heights[i] - heights[i - 1];
            brickSum += (diff > 0) ? diff : 0;
            if (diff > 0) {
                pqLimited.push(diff);
            }
            if (brickSum - pqLimited.sum <= bricks) {
                best = i;
            }
        }
        return best;
    }
};

int main() {
    Solution sol;
    vector<int> h({14,3,19,3});
    cout << sol.furthestBuilding(h, 17, 3);
}