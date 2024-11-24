#include <bits/stdc++.h>
using namespace std;

// to solve this problem, sort the ranges in increasing l and then decreasing r
// start from index 0, if arr[0] == 0 move to arr[1]
// find range with biggest r with l <= 0
// range decrement
// find index of next elem > 0 asnd repeat
// so e.g index of next elem is 5, find range with biggest r with l <= 5

// we want to use the least number of ranges to 0 the entire array
// so if left most index of elem not 0 is L, we take the range with l <= L and largest R first as greedy choice

// 1. range add
// 2. for a given value, find leftmost index >= value
class ST1 {
public:
    int sz;
    vector<int> tree;
    vector<int> accu;

    ST1(vector<int>& arr): sz(arr.size()), tree(4 * sz, 0), accu(4 * sz, 0) {
        build(0, 0, sz - 1, arr);
    }

    void build(int p, int s, int e, vector<int>& arr) {
        if (s == e) {
            tree[p] = arr[s];
            return;
        }

        int m = (s + e) >> 1;
        build((p << 1) + 1, s, m, arr);
        build((p << 1) + 2, m + 1, e, arr);
        tree[p] = max(tree[(p << 1) + 1], tree[(p << 1) + 2]);
    }

    // returns the real max value in [s, e] after range adding [l, r]
    int rangeAdd(int p, int s, int e, int l, int r, int acc, int val) {
        if (s == e || (s == l && e == r)) {
            int real = tree[p] + acc + val;
            tree[p] += val;
            accu[p] += val;
            return real;
        }

        int m = (s + e) >> 1;
        int lres;
        int rres;

        if (r <= m) {
            lres = rangeAdd((p << 1) + 1, s, m, l, r, acc + accu[p], val);
            rres = acc + accu[p] + tree[(p << 1) + 2];
        } else if (l > m) {
            lres = acc + accu[p] + tree[(p << 1) + 1];
            rres = rangeAdd((p << 1) + 2, m + 1, e, l, r, acc + accu[p], val);
        } else {
            lres = rangeAdd((p << 1) + 1, s, m, l, m, acc + accu[p], val);
            rres = rangeAdd((p << 1) + 2, m + 1, e, m + 1, r, acc + accu[p], val);
        }

        int real = max(lres, rres);
        tree[p] = real - acc;
        return real;
    }

    // find the leftmost index s.t arr[idx] >= key
    // return arr.size() if not found
    int findLMIndex(int p, int s, int e, int acc, int key) {
        if (s == e) {
            int real = acc + tree[p];
            return (real >= key) ? s : s + 1;
        }

        int m = (s + e) >> 1;
        int lmax = acc + accu[p] + tree[(p << 1) + 1];
        return (lmax >= key) ? findLMIndex((p << 1) + 1, s, m, acc + accu[p], key)
            : findLMIndex((p << 1) + 2, m + 1, e, acc + accu[p], key);

    }


};


class ST2 {
public:
    int sz;
    vector<vector<int>> tree; // {idx of max elem in [s, e], value of max elem in [s, e]}

    ST2(int sz): sz(sz), tree(4 * sz, {0,0}) {}


   
    void updatePoint(int p, int s, int e, int i, int val) {
        if (s == e) {
            tree[p] = {s, val};
            return;
        }

        int m = (s + e) >> 1;
        if (i <= m) updatePoint((p << 1) + 1, s, m, i, val);
        else updatePoint((p << 1) + 2, m + 1, e, i, val);

        tree[p] = (tree[(p << 1) + 1][1] < tree[(p << 1) + 2][1]) ? tree[(p << 1) + 2]
            : tree[(p << 1) + 1];
    }

    // returm {idx of largest elem found, value of largest elem found}
    vector<int> rangeMax(int p, int s, int e, int l, int r) {
        if (s == e|| (s == l && e == r)) return tree[p];

        int m = (s + e) >> 1;
        if (r <= m) return rangeMax((p << 1) + 1, s, m, l, r);
        else if (l > m) return rangeMax((p << 1) + 2, m + 1, e, l, r);
        else {
            vector<int> lres = rangeMax((p << 1) + 1, s, m, l, m);
            vector<int> rres = rangeMax((p << 1) + 2, m + 1, e, m + 1, r);
            return (lres[1] < rres[1]) ? rres : lres;
        }
    }

    
};


class Solution {
public:

    vector<vector<int>> sortAndCollect(int n, vector<vector<int>>& queries) {
        vector<vector<int>> store(n, vector<int>());
        for (vector<int>& q : queries) {
            store[q[0]].push_back(q[1]);
        }

        for (vector<int>& s : store) {
            sort(s.begin(), s.end());
        }

        return store;
    }

    int maxRemoval(vector<int>& nums, vector<vector<int>>& queries) {
        ST1 st1(nums);
        ST2 st2(nums.size());
        vector<vector<int>> store = sortAndCollect(nums.size(), queries);

        // fill st2
        for (int i = 0; i < nums.size(); i ++) {
            vector<int>& curr = store[i];
            if (curr.empty()) {
                st2.updatePoint(0, 0, st2.sz - 1, i, -1);
            } else {
                int rval = curr.back();
                curr.pop_back();
                st2.updatePoint(0, 0, st2.sz - 1, i, rval);
            } 
        }
        
        int queryUsedCnt = 0;
        while (true) {
            int leftMostIdx = st1.findLMIndex(0, 0, st1.sz - 1, 0, 1);
            
            // all elems are 0 already
            if (leftMostIdx == st1.sz) break;

            // find range with longest r
            vector<int> res = st2.rangeMax(0, 0, st2.sz - 1, 0, leftMostIdx);
            
            // no ranges left that can decrement leftMostIdx, so it is impossible anyway
            if (res[1] == -1) break;

            queryUsedCnt ++;
            st1.rangeAdd(0, 0, st1.sz - 1, res[0], res[1], 0, -1);
            
           
            if (store[res[0]].empty()) {
                st2.updatePoint(0, 0, st2.sz - 1, res[0], -1);
            } else {
                st2.updatePoint(0, 0, st2.sz - 1, res[0], store[res[0]].back());
                store[res[0]].pop_back();
            }

        }
       
        
        int check = st1.findLMIndex(0, 0, st1.sz - 1, 0, 1);
        if (check == nums.size()) {
            return queries.size() - queryUsedCnt;
        } else {
            return -1;
        }
    }
};

/*int main() {
    vector<int> arr = {4,4,4,4,100,100,100,100};
    ST1 st(arr);
    cout << st.findLMIndex(0, 0, st.sz - 1, 0, 100) << endl;
    st.rangeAdd(0, 0, st.sz - 1, 2, 3, 0, 100);
    cout << st.findLMIndex(0, 0, st.sz - 1, 0, 100) << endl;
    st.rangeAdd(0, 0, st.sz - 1, 2, 3, 0, -100);
    cout << st.findLMIndex(0, 0, st.sz - 1, 0, 100) << endl;
    st.rangeAdd(0, 0, st.sz - 1, 4, 7, 0, -9999);
    cout << st.findLMIndex(0, 0, st.sz - 1, 0, 100) << endl;
}*/

int main() {
    Solution sol;
    vector<int> nums = {0,0,3};
    vector<vector<int>> queries = {{0,2}, {1,1}, {0,0}, {0,0}};

    cout << sol.maxRemoval(nums, queries) << endl;
}


