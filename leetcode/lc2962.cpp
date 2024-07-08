#include <bits/stdc++.h> 
using namespace std;

// if find_increasing and find_decreasing intersect, then entire array is strictly increasing
class Solution {
    public:
        int find_increasing(vector<int>& nums) {
            for (int i = 1; i < nums.size(); i ++) {
                if (nums[i] <= nums[i - 1]) {
                    return i - 1;
                }
            }
            return nums.size() - 1;
        }

        int find_decreasing(vector<int>& nums) {
            for (int i = nums.size() - 2; i >= 0; i --) {
                if (nums[i] >= nums[i + 1]) {
                    return i + 1;
                }
            }
            return 0;
        }

        int binary_search(vector<int>& nums, int start, int end, int key) {
            // if outside return nums.size()
            if (start == end) {
                if (start == nums.size() - 1 && nums[start] <= key) {
                    return nums.size();
                } else {
                    return start;
                }
            } else {
                int mid = (end + start) / 2;
                if (nums[mid] <= key) {
                    return binary_search(nums, mid + 1, end, key);
                } else {
                    return binary_search(nums, start, mid, key);
                }
            }
        }

        long long helper(int x) {
            long long ans = (x + 2) * (x + 1) / 2;
            ans -= (x + 1);
            return ans;
        }

        long long incremovableSubarrayCount(vector<int>& nums) {
            int first = find_increasing(nums);
            int last = find_decreasing(nums);
            if (last <= first) {
                return helper(nums.size());
            }
            long long count = 0;
            
            // 2 pointer approach
            // since first < last
            // p1, p2 will never intersect, and last > 0
            int p1 = first;
            int p2 = nums.size();
            while (p1 >= -1) {
                if (p1 == -1) {
                    count += nums.size() - last + 1;
                    break;
                } else {
                    while (p2 > last) {
                        if (nums[p1] < nums[p2 - 1]) {
                            p2 -= 1;
                        } else {
                            break;
                        }
                    }
                    count += nums.size() - p2 + 1;
                    p1 --;
                }
            }
            return count;
        }
};




int main() {
    vector<int> x = {27,39,32,30,38,41,28,26,49,49};
    Solution s;
    cout << s.incremovableSubarrayCount(x);
    return 0;
}