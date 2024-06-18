#include <vector>
#include <iostream>
#include <stdio.h>
#include <chrono>
#define DEFAULT 0xffffffff

using namespace std;


class SegTree {
public:
    vector<int> tree;
    int size;


    SegTree() {}

    SegTree(vector<int>& nums) : tree(4 * nums.size(), 0) {
        size = nums.size();

        buildTree(0, 0, size - 1, nums);
    }

    
    void buildTree(int p, int s, int e, vector<int>& array) {
        int m = (s + e) / 2;
        if (s == e) {
            tree[p] = array[s];
        } else {
            buildTree(2 * p + 1, s, m, array);
            buildTree(2 * p + 2, m + 1, e, array);
            tree[p] = tree[2 * p + 1] & tree[2 * p + 2];
        }
    }

    // find the 1st index s.t AND[i, res] <= target
    // the ans is {index, value of AND[i, index]}
    // if left call already find ans, the value will be target, not less
    // accu is AND[i ... s - 1] if  i <= s, if i == s, then accu is 0xffffffff i guess
    // at the 1st time i == s, accu = 0xffffffff
    // if cannot find when going left, return AND[i .. m]
   
    int* leftEnd(int p, int s, int e, int i, int target, int accu) {
        int m = (s + e) / 2;
        if (s == e) {
            return new int[2] {s, accu & tree[p]};
        } else if (i > m) {
            return leftEnd(2 * p + 2, m + 1, e, i, target, accu);
        } else if (i <= s) {
            int temp = tree[2 * p + 1] & accu;
            return (temp <= target) ? leftEnd(2 * p + 1, s, m, i, target, accu) : leftEnd(2 * p + 2, m + 1, e, i, target, temp);
        } else {
            int *lres = leftEnd(2 * p + 1, s, m, i, target, accu);
            return (lres[1] <= target) ? lres : leftEnd(2 * p + 2, m + 1, e, i, target, lres[1]);

        }
    }

    // return {index, AND[i .. index]} s.t index is the 1st index s.t AND[i .. index] < target
    // if cannot find when going left, will return AND[i .. m]
    int* rightEnd(int p, int s, int e, int i, int target, int accu) {
        int m = (s + e) / 2;
        if (s == e) {
            return new int[2] {s, accu & tree[p]};
        } else if (i > m) {
            return rightEnd(2 * p + 2, m + 1, e, i, target, accu);
        } else if (i <= s) {
            int temp = tree[2 * p + 1] & accu;
            return (temp >= target) ? rightEnd(2 * p + 2, m + 1, e, i, target, temp) : rightEnd(2 * p + 1, s, m, i, target, accu);
        } else {
            int *lres = rightEnd(2 * p + 1, s, m, i, target, accu);
            return (lres[1] < target) ? lres : rightEnd(2 * p + 2, m + 1, e, i, target, lres[1]);
        }
    }
};


class SegTreeMin {
public:
    vector<int> tree;
    int size;

    SegTreeMin(vector<int>& array) : tree(4 * array.size(), 0) {
        buildTree(0, 0, array.size() - 1, array);
        size = array.size();
    }

    void buildTree(int p, int s, int e, vector<int>& arr) {
        int m = (s + e) / 2;
        if (s == e) {
            tree[p] = arr[s];
        } else {
            buildTree(2 * p + 1, s, m, arr);
            buildTree(2 * p + 2, m + 1, e, arr);
            tree[p] = min(tree[2 * p + 1], tree[2 * p + 2]);
        }
    }

    int getMin(int p, int s, int e, int l, int r) {
        int m = (s + e) / 2;
        if (s == e) {
            return tree[p];
        } else if (s == l && e == r) {
            return tree[p];
        } else if (r <= m) {
            return getMin(2 * p + 1, s, m, l, r);
        } else if (l > m) {
            return getMin(2 * p + 2, m + 1, e, l, r);
        } else {
            int lmin = getMin(2 * p + 1, s, m, l, m);
            int rmin = getMin(2 * p + 2, m + 1, e, m + 1, r);
            return min(lmin, rmin);
        }
    }
};

class Solution {
public:
    vector<vector<int>> dp;

    

    
    int minimumValueSum(vector<int>& nums, vector<int>& andValues) {
        dp = vector(nums.size(), vector(andValues.size(), 0));
        SegTree st(nums);
        int store = DEFAULT;
        for (int i = nums.size() - 1; i >= 0; i --) {
            store = store & nums[i];
            dp[i][andValues.size() - 1] = (store == andValues[andValues.size() - 1]) ? nums[nums.size() - 1] : 1000000000;
        }

        for (int k = andValues.size() - 2; k >= 0; k --) {
            vector<int> arr(nums.size(), 0);
            for (int i = 1; i < nums.size(); i ++) {
                arr[i] = dp[i][k + 1] + nums[i - 1];
            }
            SegTreeMin stmin(arr);
            int target = andValues[k];
            for (int i = 0; i < nums.size(); i ++) {
                int* l = st.leftEnd(0, 0, st.size - 1, i, target, DEFAULT);
                int* r = st.rightEnd(0, 0, st.size - 1, i, target, DEFAULT);
                int start = l[0];
                int end =  r[0]; // even if right end is nums.size() - 1, we stil need to have 1 elem left
                if (l[0] == nums.size() - 1 || l[1] != target) {
                    dp[i][k] = 1000000000;
                } else {
                    dp[i][k] = stmin.getMin(0, 0, stmin.size - 1, start + 1, end);
                }
            }
        }
        return (dp[0][0] >= 1000000000) ? -1 : dp[0][0];

    }
};





/*int main() {
    vector<int> arr(1000000, 100);
    SegTree st(arr);
    assert(st.leftEnd(0, 0, st.size - 1, 5000, 10, DEFAULT)[0] == 999999);
    assert(st.rightEnd(0, 0, st.size - 1, 5000, 10, DEFAULT)[0] == 999999);

    vector<int> arr2 = {0b1111, 0b0011, 0b0111, 0b0111, 0b0111, 0b0011};
    SegTree st2(arr2);
    int * res = st2.leftEnd(0, 0, st2.size - 1, 0, 0b0111, DEFAULT);
    cout << res[0] << " " << res[1] << endl;
    int* res2 = st2.rightEnd(0, 0, st2.size - 1, 0, 0b0001, DEFAULT);
    cout << res2[0] << " " << res2[1] << endl;

    vector<int> arr3(1000000, 0b111111);
    arr3[500] = 0b111;
    SegTree st3(arr3);
    cout << st3.leftEnd(0, 0, st3.size - 1, 1, 0b111, DEFAULT)[0] << endl;

}*/

int main() {
    vector<int> arr = {2,3,5,7,7,7,5};
    vector<int> andValues = {0,7,5};
    Solution sol;
    cout << sol.minimumValueSum(arr, andValues);
}