// min num of intervals to cover a range, greedy solution
// for the leftmost range, take the range that covers the leftmost and is the longest among all ranges that cover leftmost, then recurse
#include <vector>
#include <iostream>
#include <queue>
#include <functional>
#include <stdio.h>
using namespace std;

class Solution {
public:
    function<bool(vector<int>& a, vector<int>& b)> cmp = [](vector<int>& a, vector<int>& b) -> bool {return a[0] > b[0];};

    vector<vector<int>> process(vector<int>& nums) {
        vector<vector<int>> out;
        for (int i = 0; i < nums.size(); i ++) {
            out.push_back({i - nums[i], i + nums[i]});
        }
        return out;
    }

    int minTaps(int n, vector<int>& ranges) {
        vector<vector<int>>&& taps = process(ranges);
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(taps.begin(), taps.end(), cmp);
        int cnt = 0;
        int curr = 0;
        int best = -1;
        while (!pq.empty() && curr < n) {
            const vector<int>& r = pq.top();
            
            if (r[0] > curr) {
                // either next start or no ranges found
                if (best == -1) {
                    break;
                } else {
                    cnt ++;
                    curr = best;
                    best = -1;
                }
            } else if (r[1] < curr) {
                pq.pop();
            } else {
                best = max(best, r[1]);
                pq.pop();
                cout << pq.size() << endl;
            }
            if (pq.size() == 0) {
                curr = best;
                cnt ++;
            }    
        }
        
        return (curr < n) ? -1 : cnt;
    }
};

int main() {
    int n = 25;
    vector<int> t = {3,0,1,5,4,1,4,2,4,4,3,3,3,0,3,2,5,1,5,5,2,3,1,0,2,4};
    cout << Solution().minTaps(n, t);
}

