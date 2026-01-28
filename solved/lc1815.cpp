#include <bits/stdc++.h>
using namespace std;

/*
maximise number of partitions such that sum of group size in partition is 0 mod batchSize 
except for the last group.
for each group, all that matters is groupSize % batchSize.
then the dp state is (remainder, tuple where tuple[i] = # of groups left with groupSize % batchSize == i)

1 optimisation, we can immediately remove all groups whose size % batchSize = 0. 
we never combine them, if we combine them, we can extract a new partition.
the # of dp states is around 2 * 9 * 3.75**8 < 10**6.
trasition is 9, so total time complexity is 10**7.
*/

class Solution {
public:
    int D;
    unordered_map<size_t, int> store;

    size_t make_key(int rm, int has_taken, const vector<int>& left) {
        size_t key = (rm << 4) + has_taken;
        for (int x : left) {
            key = (key << 4) + x;
        }
        return key;
    }

    int dp(int rm, int has_taken, vector<int>& left, int cnt) {
        size_t key = make_key(rm, has_taken, left);
        
        if (store.contains(key)) {
            return store[key];
        } else if (!has_taken && cnt == 0) {
            return 0;
        } 

        int best = 1;
        if (has_taken && rm == 0) {
            best = max(best, 1 + dp(0, false, left, cnt));
        } else {
            for (int i = 1; i < left.size(); i++) {
                if (left[i] == 0) continue;
                left[i]--;
                best = max(best, dp((rm + i) % D, true, left, cnt - 1));
                left[i]++;
            }
        }
        return store[key] = best;
    }
    
    int maxHappyGroups(int batchSize, vector<int>& groups) {
        D = batchSize;
        
        auto left = vector<int>(batchSize, 0);
        for (int g : groups) left[g % D]++;

        int num_mod_0 = left[0];
        int cnt = accumulate(left.begin() + 1, left.end(), 0);
        return num_mod_0 + dp(0, false, left, cnt);
    }
};


int main() {
    Solution sol;
    int batchSize = 9;
    vector<int> groups = {1,8,1,8,1,8,1,8,2,7,2,7,2,7,2,7,3,6,3,6,3,6,3,6,4,5,4,5,4,5};
    
    int ans = sol.maxHappyGroups(batchSize, groups);
    cout << ans << endl;
}