#include <vector>
#include <iostream>
using namespace std;

class SegmentTree {
// 1 means true for range, 0 means false
public:
    vector<int> tree;
    int size;

    SegmentTree(int n) {
        size = n;
        tree = vector(4 * n, 0);
    }

    //update the sum of true(s) in range[s, e]
    int updatePoint(int p, int s, int e, int i, int add) {
        int m = (s + e) / 2;
        if (s == e) {
            tree[p] = add;
            return add;
        } else if (i <= m) {
            int left = updatePoint(2 * p + 1, s, m, i, add);
            int right = tree[2 * p + 1];
            tree[p] = left + right;
            return left + right;
        } else {
            int left = tree[2 * p + 1];
            int right = updatePoint(2 * p + 2, m + 1, e, i, add);
            tree[p] = left + right;
            return left + right;
        }
    }

    int rangeSum(int p, int s, int e, int l, int r) {
        int m = (s + e) / 2;
        if (s == e) {
            return tree[p];
        } else if (l == s && r == e) {
            return tree[p];
        } else if (r <= m) {
            return rangeSum(2 * p + 1, s, m, l, r);
        } else if (l > m) {
            return rangeSum(2 * p + 2, m + 1, e, l, r);
        } else {
            return rangeSum(2 * p + 1, s, m, l, m) + rangeSum(2 * p + 2, m + 1, e, m + 1, r);
        }
        
        
    }
};

class Solution {
public:
    SegmentTree* st;

    vector<int>* compress(string& s) {
        vector<int>* out = new vector(0, 0);
        for (int i = 0; i < s.size(); i ++) {
            if (s[i] == '0') {
                (*out).push_back(i);
            }
        }
        return out;

    }

    bool canReach(string s, int minJump, int maxJump) {
        if (s[s.size() - 1] == '1') {
            return false;
        }
        
        st = new SegmentTree(s.size());
        int n = s.size();
        (*st).updatePoint(0, 0, n - 1, n - 1, 1);
        vector<int>* compressed = compress(s);
        for (int i = (*compressed).size() - 2; i >= 0; i --) {
            int index = (*compressed)[i];
            int s = index + minJump;
            if (s >= n) {
                continue;
            }
            int e = min(index + maxJump, n - 1);
            int possible = (*st).rangeSum(0, 0, n - 1, s, e);
            if (possible > 0) {
                (*st).updatePoint(0, 0, n - 1, index, 1);
            }
        }
        return ((*st).rangeSum(0, 0, n - 1, 0, 0) == 1) ? true : false;
    }
};

int main() {
    Solution s;
    string ss = "00001";
    cout << s.canReach(ss, 1, 99999);
}