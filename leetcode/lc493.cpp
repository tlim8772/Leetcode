#include <iostream>
#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;


class SegTree {
public:
    vector<int> tree;
    int size;

    SegTree(int n) {
        tree = vector(4 * n, 0);
        size = n;
    }


    void insert(int p, int s, int e, int i, int v) {
        int m = (s + e) / 2;
        if (s == e) {
            tree[p] += v;
        } else if (i <= m) {
            insert(2 * p + 1, s, m, i, v);
            tree[p] = tree[2 * p + 1] + tree[2 * p + 2];
        } else {
            insert(2 * p + 2, m + 1, e, i, v);
            tree[p] = tree[2 * p + 1] + tree[2 * p + 2];
        }
    }

    int queryLessThanEq(int p, int s, int e, int limit) {
        int m = (s + e) / 2;
        if (s == e) {
            return (s <= limit) ? tree[p] : 0;
        }  else if (limit <= m) {
            return queryLessThanEq(2 * p + 1, s, m, limit);
        } else {
            return tree[2 * p + 1] + queryLessThanEq(2 * p + 2, m + 1, e, limit);
        }
    }
};

class Solution {
public:
    vector<int> distinct;
    unordered_map<int, int> map;

    void process(vector<int> &nums) {
        for (int i = 0; i < nums.size(); i ++) {
            if (map.find(nums[i]) == map.end()) {
                distinct.push_back(nums[i]);
                map[nums[i]] = 1;
            }
        }
        sort(distinct.begin(), distinct.end());
        for (int i = 0; i < distinct.size(); i ++) {
            map[distinct[i]] = i;
        }
    }

    int findPair(int n) {
        int s = 0;
        int e = distinct.size() - 1;
        while (s < e) {
            int m = (s + e) / 2 + (s + e) % 2;
            if (distinct[m] > n) {
                e = m - 1;
            } else {
                s = m;
            }
        }
        return (distinct[s] <= n) ? s : -1;
    }

    int findLimit(int n) {
        if (n >= 0) {
            return n / 2 - (1 - n % 2);
        } else {
            return n / 2 - 1;
        }
    }

    int reversePairs(vector<int>& nums) {
        SegTree st(nums.size());
        process(nums);
        int sum = 0;
        for (int i = nums.size() - 1; i >= 0; i --) {
            int limit = findLimit(nums[i]);
            cout << limit << endl;
            sum += st.queryLessThanEq(0, 0, st.size - 1, findPair(limit));
            st.insert(0, 0, st.size - 1, map[nums[i]], 1);
        }
        return sum;
    }

   



};

int main() {
   cout << Solution().findLimit(-5) << endl;

}