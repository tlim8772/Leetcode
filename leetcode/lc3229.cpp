#include <vector>
#include <iostream>
#include <set>
using namespace std;

void print(vector<int> arr) {
    for (int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}



// use ordered set to find the rightmost valid index
// 1st we apply hint1, get target[i] - nums[i], find min num of operations to make all elems 0
// consider the optimal set of operations, the order does not matter, consider op as [l, r, + or -]
// we order by increasing l, then by decreasing r
// we can also modify op
// modification 1, if 2 + op or 2 - op intersect (or touch in this case can reduce num of op), 
// can be changed into 2 op such that one op completely 
// overlaps the other. eg [1, 5, +] and [3, 6, +] -> [1, 6, +] and [3, 5, +]
// modification 2 if 1 + op and 1 - op intersect, (can be overlap), can be changed to 2 ops that are disjoint in range
// eg [1, 5, +] and [2, 4, -] -> [1, 1, +] and [5, 5, +]

// apply modification 1 and 2 until cannot, then order the ops as stated
// notice that the +ve op and -ve op are disjoint, so we seprate the array into disjoint subarrays of 
// +ve and -ve nums, we only consider analysing +ve num array, for -ve num array, negate all nums, same thing

// for the 0th element, we only have arr[0] op covering it, otherwise if have extra, we need to minus, not possible,
// cannot have +ve and -ve op overlapping
// for 0th element, we go all the way to until find an element that is 0 at r, then for range [0, r - 1] minus until the
// smallest elem become 0
// why we go past an elem that is 0, if not we will have +ve op and -ve op contradiction
// and we greedily go and (minus) as much elem as possible, if not we have 2 touching ops
// eg [5 4 1 2 3 2] we minus from [0, 1] but there will exist an op to minus 1 from idx 1

// so we use set to get rightmost idx that is not 0
// use segment tree for addRange and findMinRange (and the index)



class SegTree {
public:
    vector<int> lazy; // lazy[p] values only applies to child node 
    vector<int> minTree; 
    vector<int> minIdxTree;
    int size;

    SegTree(vector<int>& arr) : size(arr.size()), minTree(4 * arr.size(), 0), minIdxTree(4 * arr.size(), 0), lazy(4 * arr.size(), 0) {
        build(arr, 0, 0, size - 1);
    }

    void build(vector<int>& arr, int p, int s, int e) {
        if (s == e) {
            minIdxTree[p] = s;
            minTree[p] = arr[s];
        } else {
            int m = (s + e) / 2;
            build(arr, 2 * p + 1, s, m);
            build(arr, 2 * p + 2, m + 1, e);
            if (minTree[2 * p + 1] < minTree[2 * p + 2]) {
                minTree[p] = minTree[2 * p + 1];
                minIdxTree[p] = minIdxTree[2 * p + 1];
            } else {
                minTree[p] = minTree[2 * p + 2];
                minIdxTree[p] = minIdxTree[2 * p + 2];
            }
        }
    } 
    
    // returns the min value and the index, after addding val to every elem in range [l, r]
    vector<int> addRange(int p, int s, int e, int l, int r, int val, int accu) {
        int m = (s + e) / 2;
        if (s == e || (s == l && e == r)) {
            lazy[p] += val;
            minTree[p] += val;
            return {accu + minTree[p], minIdxTree[p]};
        } 
        
        vector<int> left;
        vector<int>right;
        if (r <= m) {
            left = addRange(2 * p + 1, s, m, l, r, val, accu + lazy[p]);
            right = {accu + lazy[p] + minTree[2 * p + 2], minIdxTree[2 * p + 2]};
        } else if (l > m) {
            left = {accu + lazy[p] + minTree[2 * p + 1], minIdxTree[2 * p + 1]};
            right = addRange(2 * p + 2, m + 1, e, l, r, val, accu + lazy[p]);
        } else {
            left = addRange(2 * p + 1, s, m, l, m, val, accu + lazy[p]);
            right = addRange(2 * p + 2, m + 1, e, m + 1, r, val, accu + lazy[p]);
        }

        if (left[0] < right[0]) {
            minTree[p] = left[0] - accu;
            minIdxTree[p] = left[1];
            return left;
        } else {
            minTree[p] = right[0] - accu;
            minIdxTree[p] = right[1];
            return right;
        }
    }

    // returns min value and the index
    vector<int> minRange(int p, int s, int e, int l, int r, int accu) {
        int m = (s + e) / 2;
        if (s == e || (s == l && e == r)) {
            return {accu + minTree[p], minIdxTree[p]};
        } else if (r <= m) {
            return minRange(2 * p + 1, s, m, l, r, accu + lazy[p]);
        } else if (l > m) {
            return minRange(2 * p + 2, m + 1, e, l, r, accu + lazy[p]);
        } else {
            vector<int>&& left = minRange(2 * p + 1, s, m, l, m, accu + lazy[p]);
            vector<int>&& right = minRange(2 * p + 2, m + 1, e, m + 1, r, accu + lazy[p]);
            return (left[0] < right[0]) ? left : right;
        }
    }
};

class Solution {
public:

    long long helper(set<int>& used, vector<int>& arr) {
        long long store = 0;
        SegTree segtree(arr);
        for (int i = 0; i < arr.size(); i ++) {
            if (used.count(i) == 1) continue;
            
            int num = segtree.minRange(0, 0, segtree.size - 1, i, i, 0)[0];
            while (num > 0) {
                auto it = used.lower_bound(i);
                int last = (it == used.end()) ? arr.size() - 1 : (*it) - 1;
                vector<int>&& minElem = segtree.minRange(0, 0, segtree.size - 1, i, last, 0);
                
                segtree.addRange(0, 0, segtree.size - 1, i, last, -minElem[0], 0);
                num -= minElem[0];
                store += minElem[0];
                used.insert(minElem[1]);
            }
            used.insert(i);
        }
        return store;
    }

    long long minimumOperations(vector<int>& nums, vector<int>& target) {
        set<int> used1; // for +ve delta
        set<int> used2; // for -ve delta
        vector<int> arr1(nums.size(), 0);
        vector<int> arr2(nums.size(), 0);

        for (int i = 0; i < nums.size(); i ++) {
            int delta = target[i] - nums[i];
            if (delta > 0) {
                used2.insert(i);
                arr1[i] = delta;
            } else if (delta < 0) {
                used1.insert(i);
                arr2[i] = -delta;
            } else {
                used1.insert(i);
                used2.insert(i);
            }
        }

        long long pos = helper(used1, arr1);
        long long neg = helper(used2, arr2);
        return pos + neg;
    }
};



int main() {
    vector<int> nums = {1,3,2};
    vector<int> target = {2,1,4};
    Solution sol;
    cout << sol.minimumOperations(nums, target);
}


/*int main() {
    vector<int> arr = {1,1,1,2};
    SegTree segtree(arr);
    segtree.addRange(0, 0, 3, 0, 3, -1, 0);
    print(segtree.minRange(0, 0, 3, 3, 3, 0));
}*/