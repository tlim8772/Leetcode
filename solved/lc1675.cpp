#include <bits/stdc++.h>
using namespace std;

// for each number we keep dividing until it is odd
// if num is originally odd -> pair{num, 1}
// if num is eveb -> pair{num divided until is odd, how many 2 as prime factors}
// now we can only increase num
// we always increase the smallest number
// we store the number of times we can x2
// put in priority queue.
// the total sum of the number of times we can times 2 is nlog(10^9)
// worse case we go through all and keep x2 until cannot so time complexity is n*logn*log(10^9)

class Solution {
public:
    pair<int,int> helper(int x) {
        if (x & 1) {
            return pair{x, 1};
        } else {
            int cnt = 0;
            while ((x & 1) == 0) {
                x >>= 1;
                cnt++;
            }
            return pair{x, cnt};
        }
    }


    int minimumDeviation(vector<int>& nums) {
        vector<pair<int,int>> store;
        int ma = 0;
        int cnt = 0;
        for (int x : nums) {
            pair<int,int> res = helper(x);
            ma = max(ma, res.first);
            cnt += res.second;
            store.push_back(res);
        }

        auto cmp = [] (const pair<int,int>& p1, const pair<int,int>& p2) { return p1.first > p2.first; };

        make_heap(store.begin(), store.end(), cmp);

        int best = 999999999;
        // invariant: we only increase the values
        while (cnt > 0) {
            pop_heap(store.begin(), store.end(), cmp);
            pair<int,int> next = store.back(); store.pop_back();

            best = min(best, ma - next.first);

            if (next.second > 0) {
                next.first <<= 1;
                next.second--;

                ma = max(ma, next.first);
                cnt--;
                
                store.push_back(next);
                push_heap(store.begin(), store.end(), cmp);
            } else {
                // we cannot *2 anymore, and this is the smallest val, means we can safely return
                // no point continuing anymore
                return best;
            }
        }

        return best;

    }
};

int main() {
    Solution sol;

    vector<int> arr = {2,8,10};
    cout << sol.minimumDeviation(arr) << endl;
}