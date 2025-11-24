#include <bits/stdc++.h>
using namespace std;

// dp with greedy
// dp(prev, i): min num of operations to make suffix starting at index i increasing, with arr1[i - 1] = prev
// if we change arr1[i], we always take the smallest elem in arr2 that is > prev

class Solution {
public:
    unordered_map<int, unordered_map<int, int>> dp;

    bool contains(int i, int j) {
        return dp.contains(i) && dp[i].contains(j);
    }

    // returns smallet val > k
    int binarySearch(vector<int>& arr, int v) {
        int s = 0, e = arr.size() - 1;
        while (s < e) {
            int m = (s + e) >> 1;
            
            if (arr[m] > v) {
                e = m;
            } else {
                s = m + 1;
            }
        }   
        return (arr[s] > v) ? arr[s] : -1;
    }

    int helper(int prev, int i, vector<int>& arr1, vector<int>& arr2) {
        if (i == arr1.size()) {
            return 0;
        } else if (contains(prev, i)) {
            return dp[prev][i];
        }

        int noTake = (arr1[i] > prev) ? helper(arr1[i], i + 1, arr1, arr2) : 999999;
        
        int take = 999999;
        int newPrev = binarySearch(arr2, prev);
        if (newPrev != -1) {
            take = 1 + helper(newPrev, i + 1, arr1, arr2);
        }

       

        int ans = min(noTake, take);
        if (i == 0) cout << take << endl;
        dp[prev][i] = ans;
        return ans;
    }

    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        sort(arr2.begin(), arr2.end());
        int ans = helper(-1, 0, arr1, arr2);
        return (ans > 2000) ? -1 : ans;
    }
};

int main() {
    Solution sol;

    vector<int> arr1 = {1,5,3,6,7};
    vector<int> arr2 = {1,3,2,4};

    cout << sol.makeArrayIncreasing(arr1, arr2) << endl;
}

