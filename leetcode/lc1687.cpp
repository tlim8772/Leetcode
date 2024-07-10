#include <vector>
#include <iostream>
using namespace std;

void print(vector<int> a) {
    for (int x : a) {
        cout << x << " ";
    }
    cout << endl;
}

class SegTree {
public:
    vector<int> minTree;
    vector<int> lazy;
    int size;

    SegTree(int n) {
        minTree = vector(4 * n, 0);
        lazy = vector(4 * n, 0);
        size = n;
    }


    // accu + minTree[p] return the actual min value, lazy propogation
    // returns min([s, e])
    int updateRange(int p, int s, int e, int l, int r, int val, int accu) {
        int m = (s + e) / 2;
        if (s == e) {
            minTree[p] += val;
            lazy[p] += val;
            return minTree[p] + accu;
        } else if (s == l && r == e) {
            lazy[p] += val;
            minTree[p] += val;
            return minTree[p] + accu;
        } else if (r <= m) {
            int leftMin = updateRange(2 * p + 1, s, m, l, r, val, accu + lazy[p]);
            int rightMin = minTree[2 * p + 2] + accu;
            int minimum = min(leftMin, rightMin);
            minTree[p] = minimum - accu;
            return minimum;
        } else if (l > m) {
            int leftMin = minTree[2 * p + 1] + accu;
            int rightMin = updateRange(2 * p + 2, m + 1, e, l, r, val, accu + lazy[p]);
            int minimum = min(leftMin, rightMin);
            minTree[p] = minimum - accu;
            return minimum;
        } else {
            int leftMin = updateRange(2 * p + 1, s, m, l, m, val, accu + lazy[p]);
            int rightMin = updateRange(2 * p + 2, m + 1, e, m + 1, r, val, accu + lazy[p]);
            int minimum = min(leftMin, rightMin);
            minTree[p] = minimum - accu;
            return minimum;
        }
    }

    // returns min([s, e])
    int findMin(int p, int s, int e, int l, int r, int accu) {
        int m = (s + e) / 2;
        if (s == e) {
            return minTree[p] + accu;
        } else if (s == l && r == e) {
            return minTree[p] + accu;
        } else if (r <= m) {
            return findMin(2 * p + 1, s, m, l, r, accu + lazy[p]);
        } else if (l > m) {
            return findMin(2 * p + 2, m + 1, e, l, r, accu + lazy[p]);
        } else {
            int leftMin = findMin(2 * p + 1, s, m, l, m, accu + lazy[p]);
            int rightMin = findMin(2 * p + 2, m + 1, e, m + 1, r, accu + lazy[p]);
            return min(leftMin, rightMin);
        }
    }

    // returns the min for [s, e] bafter setting index i to be val
    // sets index i to be val
    int setIndex(int p, int s, int e, int i, int val, int accu) {
        int m = (s + e) / 2;
        if (s == e) {
            minTree[p] = val - accu;
            return val;
        } else if (i <= m) {
            int leftMin = setIndex(2 * p + 1, s, m, i, val, accu + lazy[p]);
            int rightMin = accu + minTree[2 * p + 2];
            int minimum = min(leftMin, rightMin);
            minTree[p] = minimum - accu;
            return minimum;
        } else {
            int leftMin = accu + minTree[2 * p + 1];
            int rightMin = setIndex(2 * p + 2, m + 1, e, i, val, accu + lazy[p]);
            int minimum = min(leftMin, rightMin);
            minTree[p] = minimum - accu;
            return minimum;
        }
    }
};

class Solution {
    public:
    int boxDelivering(vector<vector<int>>& boxes, int portsCount, int maxBoxes, int maxWeight) {
        SegTree st(boxes.size() + 1);
        st.setIndex(0, 0, st.size - 1, boxes.size(), 2, 0);
        vector<int> dp(boxes.size(), 0);
        int sumWeight = 0;
        int numBoxes = 0;
        int j = boxes.size() - 1;
        
        // invariant index i + 1 to end contains the correct trips needed if ship collects all boxes from i to j - 1
        // return to storage at index j to continue
        for (int i = boxes.size() - 1; i >= 0; i --) {
            if (i == boxes.size() - 1) {
                sumWeight += boxes[i][1];
                numBoxes = 1;
                //st.setIndex(0, 0, st.size - 1, i, 2, 0);
                dp[i] = 2;
                st.setIndex(0, 0, st.size - 1, i, 4, 0);
                if (i - 1 >= 0 && boxes[i - 1][0] != boxes[i][0]) st.updateRange(0, 0, st.size - 1, i + 1, st.size - 1, 1, 0);
            } else {
                sumWeight += boxes[i][1];
                numBoxes += 1;
                while (j > i && (sumWeight > maxWeight || numBoxes > maxBoxes)) {
                    //cout << j << endl;
                    sumWeight -= boxes[j][1];
                    numBoxes --;
                    j --;
                    
                }
                int r =  j + 1;
                int ans = st.findMin(0, 0, st.size - 1, i + 1, r, 0);
                dp[i] = ans;
                
                if (i - 1 >= 0 && boxes[i - 1][0] != boxes[i][0]) st.updateRange(0, 0, st.size - 1, i + 1, st.size - 1, 1, 0);
                st.setIndex(0, 0, st.size - 1, i, ans + 2, 0);
            }
        }
        print(dp);
        return dp[0];
    }
};

int main() {
    vector<vector<int>> boxes = {{1,4},{1,2},{2,1},{2,1},{3,2},{3,4}};
    int portCnt = 3;
    int maxBoxes = 6;
    int maxWeight = 7;
    Solution sol;
    cout << sol.boxDelivering(boxes, portCnt, maxBoxes, maxWeight) << endl;
}




















/*int main() {
    SegTree st(10);
    st.setIndex(0, 0, st.size - 1, 5, 0, 0);
    st.setIndex(0, 0, st.size - 1, 4, 3, 0);
    cout << st.findMin(0, 0, st.size - 1, 0, 9, 0) << endl;
    st.updateRange(0, 0, st.size - 1, 5, 9, 10, 0);
    cout << st.findMin(0, 0, st.size - 1, 6, 7, 0) << endl;
    st.setIndex(0, 0, st.size - 1, 0, 0, 0);
    cout << st.findMin(0, 0, st.size - 1, 0, 5, 0) << endl;
    st.updateRange(0, 0, st.size - 1, 0, 4, 100, 0);
    cout << st.findMin(0, 0, st.size - 1, 0, 4, 0) << endl;
    cout << st.findMin(0, 0, st.size - 1, 4, 9, 0) << endl;
    

}*/