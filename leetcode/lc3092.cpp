#include <vector>
#include <iostream>
using namespace std;

//use segment tree;

class SegTree {
public:
    vector<long long> tree;
    int size;

    SegTree(int n) {
        tree = vector<long long>(4 * n, 0L);
        size = n - 1;
    }

    void update(int p, int s, int e, int i, int val) {
        int m = (s + e) / 2;
        if (s == e) {
            tree[p] += (long long) val;
        } else {
            if (i <= m) {
                update(2 * p + 1, s, m, i, val);
            } else {
                update(2 * p + 2, m + 1, e, i, val);
            }
            tree[p] = max(tree[2 * p + 1], tree[2 * p + 2]);
        }
    }

    long long maxFreq() {
        return tree[0];
    }
};

class Solution {
public:
    vector<long long> mostFrequentIDs(vector<int>& nums, vector<int>& freq) {
        SegTree st(100000);
        vector<long long> res;
        for (int i = 0; i < freq.size(); i ++) {
            st.update(0, 0, st.size, nums[i] - 1, freq[i]);
            res.push_back(st.maxFreq());
        }
        //res.push_back(st.maxFreq());
        return res;
    }
};

void print(vector<long long> l) {
    for (long long x : l) {
        cout << x << endl;
    }
}

int main() {
    vector<int> nums = {5,5,3};
    vector<int> freq = {2,-2,1};
    print(Solution().mostFrequentIDs(nums, freq));    
}