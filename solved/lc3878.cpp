#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// for a subarray, we only need to check the OR results of all elems in subarray with the max element,
// because the OR result is >= max elem of subarray.
// so for every element, we want to find the left, right index, 
// such that r is the 1st element to the right that is not a subset of arr[i]
// and l is the 1st element to the left that is not a subset of arr[i].

// suppose when processing nums[i], we found the 1st right not subset index of nums[i + 1] at index r
// then we can check nums[r], instead of going from nums[i + 1], nums[i + 2]... 

// must be careful of double counting. 
// eg. Consider [6, 6].
// for i = 0, (0, 1) is added
// for i = 1, (0, 1) is also added.
// key here is that if nums[next] = nums[i], then indices will be double counted.
// to prevent this for the right (limits) array, we stop if nums[i] = nums[next].
// suppose the offending indices are i, j.
// this prevents (x, y) x <= i, y >= j from being counted twice.

// time complexity is hard to figure out, but is very fast already.

class Solution {
public:
    long long countGoodSubarrays(vector<int>& nums) {
        vector<int> right(nums.size(), -1), left(nums.size(), -1);
        
        for (int i = nums.size() - 1; i > -1; i--) {
            if (i == nums.size() - 1) {
                right[i] = nums.size();
                continue;
            }

            int next = i + 1;
            while (1) {
                if (next == nums.size() || nums[i] == nums[next] || (nums[i] | nums[next]) != nums[i]) {
                    right[i] = next;
                    break;
                }
                next = right[next];
            }
        }

        for (int i = 0; i < nums.size(); i++) {
            if (i == 0) {
                left[i] = -1;
                continue;
            }

            int next = i - 1;
            while (1) {
                if (next == -1 || (nums[i] | nums[next]) != nums[i]) {
                    left[i] = next;
                    break;
                }
                next = left[next];
            }
        }

        /*for (int i = 0; i < nums.size(); i++) {
            println("{}: {} {}", i, left[i], right[i]);
        }*/

        ll sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            ll l = i - left[i], r = right[i] - i;
            sum += l * r;

            /*if (i > 0 && nums[i] == nums[i - 1]) {
                sum -= 1;
            }*/
        }

        return sum;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {4, 2, 3};
    int ans = sol.countGoodSubarrays(nums);
    cout << ans << endl;
}
