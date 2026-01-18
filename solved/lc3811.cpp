#include <bits/stdc++.h>
using namespace std;
using state = tuple<int,int,int>;
using ll = long long;
const ll MOD = 1e9 + 7;

// a simple O(n^2) solution is to use dp(i, target)
// where i is the index we are starting at, and target is the xor val we want to get
// we iterate i to n - 1, if xor[i, j] = target, we add dp(j + 1, target2).

// to get O(n), note that a xor block consist of the minimal block and
// consectuive xor blocks that xor to 0.
// so at index i, we go to the smallest j, j > i, s.t xor[i..j] = target
// from there we either go to 0, or go to target2.

// basically we want to find # of ways to partition nums into eg
// t1 t2 t1 t2
// t1 0 t2 0 0 t1 t2 0
// here the blocks are the minium blocks s.t xor[block_start, block_end] = target,
// i.e block_end is the 1st index s.t xor[block_start, block_end] = target

// let dp(i, curr_t, next_t) = # ways to partition s.t
// we want to achieve target curr_t.
// next_t is for when curr_t = 0.
// if dp = (i, 0, 2) means we want to achieve xor block of 0, next target is target2
// if dp = (i, 1, 0) means we have to get a xor block of target1,
// and the next state we can go to is dp(j, 0, 2) or dp(j, 2, 0)

class Solution {
public:
    vector<int> nums;
    int target1, target2;
    vector<int> prefix_xor;
    vector<array<int, 3>> infos;
    vector<ll> store;

    int pos(int idx, int curr_t, int next_t) {
        return idx * 9 + curr_t * 3 + next_t;
    }

    void make_prefix_xor(const vector<int>& nums) {
        prefix_xor = vector(nums.size(), 0);
        int accu = 0;
        for (int i = 0; i < nums.size(); i++) {
            prefix_xor[i] = accu ^= nums[i];
        }
    }

    void make_info(const vector<int>& nums) {
        infos = vector<array<int,3>>(nums.size(), {0, 0, 0});
        
        unordered_map<int, int> store;
        array<int, 3> targets = {0, target1, target2};
       
        for (int i = nums.size() - 1; i > -1; i--) {
            int back = (i == 0) ? 0 : prefix_xor[i - 1];
            array<int, 3>& my_info = infos[i];
            
            for (int j = 0; j < 3; j++) {
                int t = targets[j];
                if (nums[i] == t) {
                    my_info[j] = i;
                } else if (!store.contains(back ^ t)) {
                    my_info[j] = -1;
                } else {
                    my_info[j] = store[back ^ t];
                }
            }

            store[prefix_xor[i]] = i;
        }
    }

    ll dp(int i, int curr_t, int next_t) {
        int s = pos(i, curr_t, next_t);
        
        if (store[s] != -1) return store[s];
        if (i == nums.size()) return 1;

        auto& [t0, t1, t2] = infos[i];
        ll &sum = store[s];
        sum = 0;

        if (curr_t == 1 && t1 != -1) {
            if (t1 + 1 == nums.size()) return sum = 1;
            int go_0 = dp(t1 + 1, 0, 2);
            int go_2 = dp(t1 + 1, 2, 0);
            sum = (sum + go_0 + go_2) % MOD;
        }

        else if (curr_t == 2 && t2 != -1) {
            if (t2 + 1 == nums.size()) return sum = 1;
            int go_0 = dp(t2 + 1, 0, 1);
            int go_1 = dp(t2 + 1, 1, 0);
            sum = (sum + go_0 + go_1) % MOD;
        }

        else if (curr_t == 0 && t0 != -1) {
            if (t0 + 1 == nums.size()) return sum = 1;
            int go_0 = dp(t0 + 1, 0, next_t);
            int go_next = dp(t0 + 1, next_t, 0);
            sum = (sum + go_0 + go_next) % MOD;
        }

        return sum;
    }


    int alternatingXOR(vector<int>& nums, int target1, int target2) {
        this->nums = nums;
        this->target1 = target1;
        this->target2 = target2;
        make_prefix_xor(nums);
        make_info(nums);
        store = vector<ll>(9 * nums.size(), -1);

        /*for (auto& arr : infos) {
            cout << arr[0] << " " << arr[1] << " " << arr[2] << endl;
        }*/

        int ans = dp(0, 1, 0);
        //cout << ans << endl;
        
        return ans;
    }
};

int main() {
    Solution sol;

    vector<int> nums(200000, 0);
    int target1 = 0, target2 = 1;

    sol.alternatingXOR(nums, target1, target2);
}