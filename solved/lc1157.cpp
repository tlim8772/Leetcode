#include <vector>
#include <iostream>
#include <stdio.h>
#include <unordered_map>
using namespace std;

// denote majority[l, r] as m[l, r]
// m[l, r] = m[l, k] or m[k + 1, r]) i.e However, we then have to count num of times that elem appears in [l, r]. since operation is associative use segment tree to reduce 
// to logn traversal
// we do this in O(logn) by storing, for each elem, the indices it appears in, then binary search
// query is (logn)^2 as a result, still okay I guess

class MajorityChecker {
public:
    vector<vector<int>> indices;
    vector<int> tree;
    vector<int>& arr;
    
    MajorityChecker(vector<int>& arr1) : arr(arr1) {
        indices = vector(20001, vector<int>());
        for (int i = 0; i < arr.size(); i ++) {
            indices[arr[i]].push_back(i);
        }
        tree = vector(4 * arr.size(), 0);
        buildTree(0, 0, arr.size() - 1);
    }

    int query(int left, int right, int threshold) {
        int ans = helper(0, 0, arr.size() - 1, left, right);
        int cnt = findCnt(ans, left, right);
        return (cnt >= threshold) ? ans : -1;
    }

    int helper(int p, int s, int e, int l, int r) {
        int m = (s + e) / 2;
        if (s == e) {
            return tree[p];
        } else if (s == l && e == r) {
            return tree[p];
        } else if (r <= m) {
            return helper(2 * p + 1, s, m, l, r);
        } else if (l > m) {
            return helper(2 * p + 2, m + 1, e, l, r);
        } else {
            int lres = helper(2 * p + 1, s, m, l, m);
            int rres = helper(2 * p + 2, m + 1, e, m + 1, r);
            int lcnt = findCnt(lres, l, r);
            int rcnt = findCnt(rres, l, r);
            return (lcnt > rcnt) ? lres : rres;
        }
    }

    void buildTree(int p, int s, int e) {
        if (s == e) {
            tree[p] = arr[s];
        } else {
            int m = (s + e) / 2;
            buildTree(2 * p + 1, s, m);
            buildTree(2 * p + 2, m + 1, e);
            int lcnt = findCnt(tree[2 * p + 1], s, e);
            int rcnt = findCnt(tree[2 * p + 2], s, e);
            if (lcnt > rcnt) {
                tree[p] = tree[2 * p + 1];
            } else {
                tree[p] = tree[2 * p + 2];
            }
        }
    }

    
    int findCnt(int elem, int l, int r) {
        int s = 0;
        int e = 0;
        int s1 = 0;
        int e1 = indices[elem].size() - 1;
        while (s1 < e1) {
            int m1 = (s1 + e1) / 2;
            if (indices[elem][m1] >= l) {
                e1 = m1;
            } else {
                s1 = m1 + 1;
            }
        }
        s = (indices[elem][s1] >= l) ? s1 : -1;

        int s2 = 0;
        int e2 = indices[elem].size() - 1;
        while (s2 < e2) {
            int m2 = (s2 + e2) / 2 + (s2 + e2) % 2;
            if (indices[elem][m2] <= r) {
                s2 = m2;
            } else {
                e2 = m2 - 1;
            }
        }
        e = (indices[elem][s2] <= r) ? s2 : -1;
        
        return (s == -1 || e == -1) ? 0 : e - s + 1;

    }

};

void print(vector<int>& arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}


int main() {
    vector<int> arr = {1, 1, 2, 2, 1, 1};
    MajorityChecker m(arr);
    //cout << arr.size() << endl;
    cout << m.query(0, 5, 4) << endl;
    cout << m.query(0, 3, 3) << endl;
    
    cout << m.query(2, 3, 2) << endl;
}