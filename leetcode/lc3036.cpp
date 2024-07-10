#include <string>
#include <vector>
#include <iostream>
using namespace std;

// basically we create the 'comparison array'
// eg array = [1,2,10,4,2,1,1,4,2]
// comparison array = [10, 1, 1, -1, -1, -1, 0, 1, -1]
// c[i] = 1 if a[i] > a[i - 1]
// c[i] = 0 if a[i] == a[i - 1]
// c[i] = -1 if a[i] < a[i - 1]
// then we do string matching of pattern eg [1, 0, -1] on the comparison array

vector<int> zAlgo(vector<int>& s) {
    vector<int> out = vector(s.size(), -1);
    out[0] = s.size();
    int l = 1;
    int r = 0;
    // invariant: [l, r] is matched i.e s[l, r] is equal to s[0, r - l + 1]
    for (int i = 1; i < s.size(); i ++) {
        if (i > r) {
            l = i;
            r = i; // r now points to the index we are checking, not confirm s[r] == s[r - l]
            while (r < s.size() && s[r] == s[r - l]) {
                r ++;
            }
            out[i] = r - l; // r is the 1st index s[r] != s[r - l];
            r --;
        } else {
            int k = out[i - l];
            if (i + k - 1 < r) {
                out[i] = k;
            } else {
                l = i;
                // no need to +1 to r, the 1st iteration s[r] == s[r - l]
                while (r < s.size() && s[r] == s[r - l]) {
                    r ++;
                }
                out[i] = r - l;
                r --;
            }
        }
    }
    return out;
}

void print(vector<int> a) {
    for (int x : a) {
        cout << x << " ";
    }
    cout << "\n";
}


class Solution {
public:
    vector<int> comparsionArrayPlusPattern(vector<int>& nums, vector<int>& pattern) {
        vector<int> out;
        for (int i = 0; i < pattern.size(); i ++) {
            out.push_back(pattern[i]);
        }
        for (int i = 0; i < nums.size(); i ++) {
            if (i == 0) {
                out.push_back(10);
            } else {
                if (nums[i] > nums[i - 1]) {
                    out.push_back(1);
                } else if (nums[i] == nums[i - 1]) {
                    out.push_back(0);
                } else {
                    out.push_back(-1);
                }
            }
        }
        return out;
    }

    int countMatchingSubarrays(vector<int>& nums, vector<int>& pattern) {
        vector<int>&& concated = comparsionArrayPlusPattern(nums, pattern);
        vector<int>&& res = zAlgo(concated);
        print(concated);
        print(res);
        int c = 0;
        for (int i = 0; i < nums.size(); i ++) {
            if (res[i + pattern.size()] >= pattern.size()) {
                c ++;
            }
        }
        return c;
    }


};

int main() {
    Solution sol;
    vector<int> nums = {1,4,4,1,3,5,5,3};
    vector<int> pat = {1,0, -1};
    cout << sol.countMatchingSubarrays(nums, pat);

    
}