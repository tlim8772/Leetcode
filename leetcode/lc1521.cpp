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

    int rangeQuery(int p, int s, int e, int l, int r) {
        int m = (s + e) / 2;
        if (s == e) {
            return tree[p];
        } else if (s == l && e == r) {
            return tree[p];
        } else if (r <= m) {
            return rangeQuery(2 * p + 1, s, m, l, r);
        } else if (l > m) {
            return rangeQuery(2 * p + 2, m + 1, e, l, r);
        } else {
            return rangeQuery(2 * p + 1, s, m, l, m) & rangeQuery(2 * p + 2, m + 1, e, m + 1, r);
        }
    }
};

class Solution {
public:
    int closestToTarget(vector<int>& arr, int target) {
        SegTree st(arr);
        int ans = 1000000000;
        for (int i = 0; i < arr.size(); i ++) {
            int* res = st.leftEnd(0, 0, st.size - 1, i, target, DEFAULT);
            int l1 = res[1];
            int l2 = (res[0] == 0) ? -1000000000 : st.rangeQuery(0, 0, st.size - 1, i, res[0] - 1);
            if (abs(target - l1) < ans) ans = abs(target - l1);
            if (abs(target - l2) < ans) ans = abs(target - l2);
        }
        return ans;
        
    }
};

int main() {
    vector<int> arr = {1,3,7,15,31};
    int target = 0;
    Solution sol;
    cout << sol.closestToTarget(arr, target);

}
