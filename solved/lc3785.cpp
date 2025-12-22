#include <bits/stdc++.h>
using namespace std;

// we want to find all bad pairs, i.e nums[i] = forbidden[i]
// bin them accordingly to nums[i]

// case 1
// if the freq of the most frequent bad pair is <= total # of bad pairs / 2, 
// and total # of bad pairs is even, then # of swaps is total # of bad pairs / 2.
// proof, consider perfect matching and use Hall's marriage theorem.

// case 2
// if freq of the most frequent bad pair is <= total # of bad pairs / 2
// and total # of bad pairs is odd,
// we can swap within bad pairs only.
// remove 1 pair from the least freq pairs
// match the remaining pairs
// difficult to proof, intuition is that after remove 1 from the least freq pair
// least freq pair < (total bad pair - 1) / 2
// we match the remaining bad pairs.
// the invalid pairs are the ones with same first val or same second val (the forbidden val)
// for each case, only have < (total bad pair - 1) / 2, so can find 1 compatible pair to swap
// i.e cannot be that same first take exactly half, same second take exactly half, so no
// compatible pair to swap with.


// case 3
// if freq of most frequent bad pair is > total # of bad pairs / 2,
// then for freq of most frequent bad pair - total # of remaining bad pairs pairs
// must be swap with a good pair

// to get # of good compatible pairs, take complement, use PIE to find # of complement pairs

struct PairHash {
    size_t operator()(const pair<int,int>& p) const {
        return ((size_t)p.first << 32) + p.second;
    }
};

class Solution {
public:
    int n, bad_pairs;
    unordered_map<pair<int,int>, int, PairHash> combine;
    unordered_map<int, int> first_map, second_map;

    void make_hash_maps(vector<int>& nums, vector<int>& forbidden) {
        n = nums.size();
        for (int i = 0; i < n; i++) {
            int a = nums[i], b = forbidden[i];
            if (a == b) continue; // dont count bad pairs !!
            first_map[a]++;
            second_map[b]++;
            combine[{a, b}]++;
        }
    }

    int get_compatible_pairs(int a, int b) {
        return n - bad_pairs - (second_map[a] + first_map[b] - combine[{a, b}]);
    }

    // return {total_cnt, most_freq_val, most_freq_cnt, store}
    tuple<int, int, int, vector<pair<int,int>>> get_bad_pairs(vector<int>& nums, vector<int>& forbidden) {
        int n = nums.size();
        unordered_map<int,int> store;
        
        for (int i = 0; i < n; i++) {
            int a = nums[i], b = forbidden[i];
            if (a != b) continue;
            store[a]++;
        }

        vector<pair<int,int>> out(store.begin(), store.end());
        int total_cnt = accumulate(out.begin(), out.end(), 0, [](int acc, auto& p) { return acc + p.second; });
        auto it = max_element(out.begin(), out.end(), [] (auto& p1, auto& p2) { return p1.second < p2.second; });
        
        if (store.size() == 0) return {0, -1, -1, out};

        return {total_cnt, (*it).first, (*it).second, out};
    }
    
    int minSwaps(vector<int>& nums, vector<int>& forbidden) {
        make_hash_maps(nums, forbidden);
        const auto& [total_cnt, most_freq_val, most_freq_cnt, store] = get_bad_pairs(nums, forbidden);
        bad_pairs = total_cnt;

        // no bad pairs
        if (total_cnt == 0) {
            return 0;
        }

        // case 1
        if (total_cnt % 2 == 0 && most_freq_cnt <= total_cnt / 2) {
            return total_cnt / 2;
        }

        // case 2
        if (total_cnt % 2 == 1 && most_freq_cnt <= total_cnt / 2) {
            return total_cnt / 2 + 1;

            /*for (auto [v, c] : store) {
                int num_compatible = get_compatible_pairs(v, v);
                if (num_compatible) return total_cnt / 2 + 1;
            }
            return -1;*/
        }

        // case 3
        if (most_freq_cnt > total_cnt / 2) {
            int remainder = most_freq_cnt - (total_cnt - most_freq_cnt);
            int num_compatible = get_compatible_pairs(most_freq_val, most_freq_val);
            if (num_compatible >= remainder) {
                return total_cnt - most_freq_cnt + remainder;
            } else {
                return -1;
            }
        }

        return -1;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1,4,8};
    vector<int> forbidden = {1,4,8};

    int ans = sol.minSwaps(nums, forbidden);
    cout << ans << endl;
}