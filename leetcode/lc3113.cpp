#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

// collect all indices s.t array[i] = x, then use sliding windows
// eg x = 3, we have i1, i2, i3, i4, i5
// suppose from i1 to i4 max elem = 3, but i1 i5 max elem = 10
// then (i1, i3), (i2, i4) all can, but cannot have start <= i4 and end >= 5
// start sliding windows at i5 onwards
class SegTree {
public:
    vector<int> tree;
    int size;

    SegTree() {

    }

    SegTree(vector<int>& nums) : tree(4 * nums.size(), 0) {
        size = nums.size();
        buildTree(0, 0, nums.size() - 1, nums);
    }

    void buildTree(int p, int s, int e, vector<int>& nums) {
        if (s == e) {
            tree[p] = nums[s];
        } else {
            int m = (s + e) / 2;
            buildTree(2 * p + 1, s, m, nums);
            buildTree(2 * p + 2, m + 1, e, nums);
            tree[p] = max(tree[2 * p + 1], tree[2 * p + 2]);
        }
    }

    int getMax(int p, int s, int e, int l, int r) {
        int m = (s + e) / 2;
        if (s == e) {
            return tree[p];
        } else if (s == l && e == r) {
            return tree[p];
        } else if (r <= m) {
            return getMax(2 * p + 1, s, m, l, r);
        } else if (l > m) {
            return getMax(2 * p + 2, m + 1, e, l, r);
        } else {
            int lmax = getMax(2 * p + 1, s, m, l, m);
            int rmax = getMax(2 * p + 2, m + 1, e, m + 1, r);
            return max(lmax, rmax);
        }
    }
};


class Solution {
public:
    unordered_map<int, vector<int>> indices;
    SegTree st;

    void process(vector<int>& nums) {
        st = SegTree(nums);
        for (int i = 0; i < nums.size(); i ++) {
            indices[nums[i]].push_back(i);
        }
    }

    long long nC2(int n) {
        long long y = (long long) n;
        return y * (y - 1) / 2;
    }

    long long helper(int n) {
        vector<int>& indice = indices[n];
        long long cnt = 0;
        int p1 = 0;
        int p2 = 0;
        while (p2 < indice.size()) {
            int maxElem = st.getMax(0, 0, st.size - 1, indice[p1], indice[p2]);
            if (maxElem <= n) {
                p2 ++;
                if (p2 == indice.size()) {
                    cnt += nC2(p2 - p1);
                    break;
                }
            } else {
                cnt += nC2(p2 - p1);
                p1 = p2;
                if (p2 == indice.size() - 1) break;
            }
        }
        return cnt;
    }

    long long numberOfSubarrays(vector<int>& nums) {
        long long sum = 0;
        process(nums);
        for (auto it = indices.begin(); it != indices.end(); it++) {
            sum += helper(it->first);
        }
        sum += nums.size();
        return sum;
    }



};

int main() {
    vector<int> array = {3,3,3};
    Solution sol;
    cout << sol.numberOfSubarrays(array);

}