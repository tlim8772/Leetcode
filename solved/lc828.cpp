#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// basically for each char, we want to know how much 'count' it contributes to all substrings
// eg ABC, A contributes 3, in A, AB, ABC
// we do this by, for each character, store the indexes where it appears
// suppose str len is 10 and A appears at 0,4,5,7
// so the gaps are A [1,3] A A [6,6] A [8,9], do some maths to count the num of subtrings 
// where A appears once

class Solution {
public:
    vector<vector<int>> store = vector(26, vector<int>());
    ll total;

    ll helper(int s, int e) {
        if (s > e) return 0;
        
        ll len = e - s + 1;
        return len * (len - 1) / 2 + len;
    }

    int helper(int len, vector<int>& arr) {
        if (arr.size() == 0) return 0;
        int cnt = arr.size();
        
        // count back
        for (int i = 0; i < arr.size(); i ++) {
            if (i == arr.size() - 1) {
                cnt += len - 1 - arr[i];
            } else {
                int s = arr[i] + 1;
                int e = arr[i + 1] - 1;
                if (s <= e) cnt += e - s + 1;
            }
        }

        // count front
        for (int i = 0; i < arr.size(); i ++) {
            if (i == 0) {
                cnt += arr[i];
            } else {
                int s = arr[i - 1] + 1;
                int e = arr[i] - 1;
                if (s <= e) cnt += e - s + 1;
            }
        }

        for (int i = 0; i < arr.size(); i ++) {
            int left, right;
            if (arr.size() == 1) {
                left = arr[i];
                right = len - arr[i] - 1;
            } else if (i == 0) {
                left = arr[i];
                right = arr[i + 1] - 1 - arr[i] - 1 + 1;
            } else if (i == arr.size() - 1) {
                left = arr[i] - 1 - arr[i - 1] - 1 + 1;
                right = len - arr[i] - 1;
            } else {
                left = arr[i] - 1 - arr[i - 1] - 1 + 1;
                right = arr[i + 1] - 1 - arr[i] - 1 + 1;
            }
            int sum = left * right;
            if (sum > 0) cnt += sum;
        }

        //cout << cnt << endl;
        return cnt; 
    }

    int uniqueLetterString(string s) {
        for (int i = 0; i < s.size(); i ++) {
            store[s[i] - 'A'].push_back(i);
        }

        return accumulate(store.begin(), store.end(), 0, [&](int res, vector<int>& arr) {return res + helper(s.size(), arr);});

      

      

        
    }


};

int main() {
    string s = "LEETCODE";
    vector<int> arr = {1};
    cout << Solution().uniqueLetterString(s) << endl;
}