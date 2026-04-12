#include <bits/stdc++.h>
using namespace std;

// at most 1 swap and it must swap 0, 1. (i.e cannot swap 2 index with the same element).
// let key of index i be b - a, where b = # of 1s in arr[0:i+1] and a = # of 0s in arr[0:i+1]

// case 1: no swaps needed.
// then the best result is the max - min of of elems with the same key

// case 2: swap needed.
// then 1 index must have its key changed, either b - a + 2 or b - a - 2.
// we can matched with the leftmost or rightmost same key value, then check if there exists a 1 and a 0
// in the respective left, right ranges

// O(nlogn) still cannot pass.
// to check if a 1 or a 0 exist in [l, r],
// we do not need a set,
// we just store for index i, the latest index at which 1 or 0 is seen

bool helper(const set<int>& elems, int l, int r) {
    auto it_left = elems.lower_bound(l);
    auto it_right = elems.upper_bound(r);
    return it_right != it_left;
}

bool helper(const vector<int>& elem, int l, int r) {
    //cout << l << " " << r << endl;
    return r != -1 && elem[r] >= l;
}

class Solution {
public:
    int longestBalanced(string s) {
        unordered_map<int, vector<int>> bins;
        vector<int> ones(s.size(), -1);
        vector<int> zeros(s.size(), -1);
        vector<int> my_key(s.size(), 0);

        int one_cnt = 0, zero_cnt = 0;
        bins[0].push_back(-1);

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '1') {
                one_cnt++;
                ones[i] = i;
                zeros[i] = (i == 0) ? -1 : zeros[i - 1];
                bins[one_cnt - zero_cnt].push_back(i);
            } else {
                zero_cnt++;
                zeros[i] = i;
                ones[i] = (i == 0) ? -1 : ones[i - 1];
                bins[one_cnt - zero_cnt].push_back(i);
            }
            my_key[i] = one_cnt - zero_cnt;
        }

        int best = 0;
        for (auto& [key, arr] : bins) {
            best = max(best, arr.back() - arr.front());
        }

        for (int i = 0; i < s.size(); i++) {
            // 0 -> 1
            {
                int new_key = my_key[i] + 2;
                auto& arr = bins[new_key];
            
                int has_right_one = helper(ones, i + 1, s.size() - 1);
                if (has_right_one && !arr.empty()) {
                    int ileft = arr[0];
                    if (helper(zeros, ileft + 1, i)) {
                        best = max(best, i - ileft);
                    }
                }

                int has_left_zero = helper(zeros, 0, i);
                if (has_left_zero && !arr.empty()) {
                    int iright = arr.back();
                    if (helper(ones, i + 1, iright)) {
                        best = max(best, iright - i);
                    }
                }
            }

            // 1 -> 0
            {
                int new_key = my_key[i] - 2;
                auto& arr = bins[new_key];

                int has_right_zero = helper(zeros, i + 1, s.size() - 1);
                if (has_right_zero && !arr.empty()) {
                    int ileft = arr[0];
                    if (helper(ones, ileft + 1, i)) best = max(best, i - ileft);
                }

                int has_left_one = helper(ones, 0, i);
                if (has_left_one && !arr.empty()) {
                    int iright = arr.back();
                    if (helper(zeros, i + 1, iright)) best = max(best, iright - i);
                }
            }
        }

        return best;

    }
};


int main() {
    Solution sol;
    string s = "111";

    int ans = sol.longestBalanced(s);
    cout << ans << endl;
}
