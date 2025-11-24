#include <vector>
#include <iostream>
using namespace std;

class bitSwitchTree {
// accu: no. of switches from lazy propogation
// so we count the accu in the previous nodes, sum all them up
// if even, no change to tree[p]
// if odd, need to take (e -s + 1) tree[p]
public:

    vector<int> tree;
    vector<int> accum;
    //vector<long long> sumTree;
    int size;

    bitSwitchTree(vector<int>& array) {
        size = array.size();
        tree = vector(4 * size, 0);
        accum = vector(4 * size, 0);
        //sumTree = vector(4 * size, 0LL);
        build(0, 0, size - 1, array);
    }

    






    void build(int p, int s, int e, vector<int>& array) {
        if (s == e) {
            tree[p] = array[s];
        } else {
            int m = (s + e) / 2;
            build(2 * p + 1, s, m, array);
            build(2 * p + 2, m + 1, e, array);
            tree[p] = tree[2 * p + 1] + tree[2 * p + 2];
        }
    }

    /*void buildSum(int p, int s, int e, vector<int>& array) {
        if (s == e) {
            sumTree[p] = (long long) array[s];
        } else {
            int m = (s + e) / 2;
            buildSum(2 * p + 1, s, m, array);
            buildSum(2 * p + 2, m + 1, e, array);
            sumTree[p] = sumTree[2 * p + 1] + sumTree[2 * p + 2];
        }
    }*/

    
    
    // returns the correct number of 1 elements in the range [s, e]
    int rangeSwitch(int p, int s, int e, int l, int r, int accu) {
        int m = (s + e) / 2;
        if (s == e) {
            tree[p] = 1 - tree[p];
            accum[p] += 1;
            return (accu % 2 == 0) ? tree[p] : 1 - tree[p];
        } else if (l == s && r == e) {
            tree[p] = (e - s + 1) - tree[p];
            accum[p] += 1;
            return (accu % 2 == 0) ? tree[p] : (e - s + 1) - tree[p];
        } else if (r <= m) {
            int nextAccu = accu + accum[p];
            int leftCount = rangeSwitch(2 * p + 1, s, m, l, r, accu + accum[p]);
            int rightCount = (nextAccu % 2 == 0) ? tree[2 * p + 2] : (e - m) - tree[2 * p + 2];
            tree[p] = (accu % 2 == 0) ? leftCount + rightCount : (e - s + 1) - leftCount - rightCount;
            return leftCount + rightCount;
        } else if (l > m) {
            int nextAccu = accu + accum[p];
            int leftCount = (nextAccu % 2 == 0) ? tree[2 * p + 1] : (m - s + 1) - tree[2 * p + 1];
            int rightCount = rangeSwitch(2 * p + 2, m + 1, e, l, r, accu + accum[p]);
            tree[p] = (accu % 2 == 0) ? leftCount + rightCount : (e - s + 1) - leftCount - rightCount;
            return leftCount + rightCount;
        } else {
            int leftCount = rangeSwitch(2 * p + 1, s, m, l, m, accu + accum[p]);
            int rightCount = rangeSwitch(2 * p + 2, m + 1, e, m + 1, r, accu + accum[p]);
            tree[p] = (accu % 2 == 0) ? leftCount + rightCount : (e - s + 1) - leftCount - rightCount;
            return leftCount + rightCount;
        }
    }


    int count(int p, int s, int e, int l, int r, int accu) {
        int m = (s + e) / 2;
        if (s == e) {
            return (accu % 2 == 0) ? tree[p] : 1 - tree[p];
        } else if (l == s && r == e) {
            return (accu % 2 == 0) ? tree[p] : (e - s + 1) - tree[p];
        } else if (r <= m) {
            return count(2 * p + 1, s, m, l, r, accu + accum[p]);
        } else if (l > m) {
            return count(2 * p + 2, m + 1, e, l, r, accu + accum[p]);
        } else {
            return count(2 * p + 1, s, m, l, m, accu + accum[p]) 
                + count(2 * p + 2, m + 1, e, m + 1, r, accu + accum[p]);
        }
    }

};

class Solution {
public:
    bitSwitchTree* st;

    

   
    vector<long long> handleQuery(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        st = new bitSwitchTree(nums1);
        vector<long long> result;
        long long sum = 0;
        for (int i = 0; i < nums2.size(); i ++) {
            sum += (long long) nums2[i];
        }
        for (int i = 0; i < queries.size(); i ++) {
            vector<int>& q = queries[i];
            if (q[0] == 1) {
                (*st).rangeSwitch(0, 0, (*st).size - 1, q[1], q[2], 0);
            } else if (q[0] == 2) {
                int c = (*st).count(0, 0, (*st).size - 1, 0, (*st).size - 1, 0);
                long long toAdd = (long long) c * (long long) q[1];
                sum += toAdd;
            } else {
                //cout <<"query 3" << endl;
                result.push_back(sum);
            }
        }
        return result;

    }

};

template <typename T>

void printVector(const vector<T>& v) {
    for (int i = 0; i < v.size(); i ++) {
        cout << v[i] << " ";
    }
    cout << endl;
}

int main() {
    vector<int> nums1 = {1,0,1};
    vector<int> nums2 = {44,28,35};
    vector<vector<int>> queries = {
        {1, 0, 1},
        {2, 10, 0},
        {2, 2, 0},
        {2, 7, 0},
        {3, 0, 0},
        {3, 0, 0},
        
        {1, 2, 2},
        {1, 1, 2},
        {2, 1, 0},
        
        {1, 0, 2},
        {1, 2, 2},
        {1, 0, 2},
        
        {3, 0, 0},
        
        {1, 1, 2},
        
        {3, 0, 0},
        {1, 0, 1},
        {2, 21, 0},
        {1, 0, 1},
        {2, 26, 0},
        {1, 1, 1}
    };
    /*Solution s;
    vector<long long>&& ans = s.handleQuery(nums1, nums2, queries);
    printVector(ans);*/
    bitSwitchTree st(nums1);
    st.rangeSwitch(0, 0, st.size - 1, 0, 1, 0);
    st.rangeSwitch(0, 0, st.size - 1, 2, 2, 0);
    st.rangeSwitch(0, 0, st.size - 1, 1, 2, 0);
    //st.rangeSwitch(0, 0, st.size - 1, 0, 2, 0);
    //st.rangeSwitch(0, 0, st.size - 1, 2, 2, 0);
    //st.rangeSwitch(0, 0, st.size - 1, 0, 2, 0);
    //st.rangeSwitch(0, 0, st.size - 1, 1, 2, 0);
    cout << st.count(0, 0, st.size - 1, 0,2, 0) << endl;


}

