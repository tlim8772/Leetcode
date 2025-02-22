#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// store for each x coor, the respective y coor
// for each x coor, we only need to consider the 2 consective y coor
// then find the next greatest x coor with the same y-coors (use set)

// use persistant segment trees tofind out if there are points in the square bounded by (x1, x2) and (y1, y2)
// use each x segment trees store the freq count of the y coor, and the range sum

// failed due to MLE

// if node is null, means that sum from [s,e] is 0
struct Node {
    Node* l;
    Node* r;
    int sum;

    Node(): l(nullptr), r(nullptr), sum(0) {}

    static Node* getLeft(Node* n) {
        return (n == nullptr) ? nullptr : n->l;
    }

    static Node* getRight(Node* n) {
        return (n == nullptr) ? nullptr : n->r;
    }

    static int getSum(Node* n) {
        return (n == nullptr) ? 0 : n->sum;
    }

    // curr can be nullptr
    static Node* insert(Node* curr, int s, int e, int val) {
        Node* res = new Node();
        
        if (s == e) {
            res->sum = getSum(curr) + 1;
            return res;
        }

        int m = (s + e) >> 1;
        if (val <= m) {
            res->l = insert(getLeft(curr), s, m, val);
            res->r = getRight(curr);
        } else {
            res->l = getLeft(curr);
            res->r = insert(getRight(curr), m + 1, e, val);
        }
        res->sum = getSum(res->l) + getSum(res->r);
        return res;
    }

    // the segment tree is curr2 - curr1
    static int rangeSum(Node* curr1, Node* curr2, int s, int e, int l, int r) {
        if (s == e || (s == l && e == r)) {
            return getSum(curr2) - getSum(curr1);
        }

        int m = (s + e) >> 1;
        if (r <= m) {
            return rangeSum(getLeft(curr1), getLeft(curr2), s, m, l, r);    
        } else if (l > m) {
            return rangeSum(getRight(curr1), getRight(curr2), m + 1, e, l, r);
        } else {
            return rangeSum(getLeft(curr1), getLeft(curr2), s, m, l, m) + 
                rangeSum(getRight(curr1), getRight(curr2), m + 1, e, m + 1, r);
        }
    }

   

};

class Solution {
public:

    unordered_map<int, int> valToIdx;
    vector<int> idxToVal;
    vector<int>* xSets;
    vector<int>* ySets;
    Node** xSegtrees;


    void compress(vector<int>& arr) {
        sort(arr.begin(), arr.end());

        for (int n : arr) {
            if (valToIdx.count(n) != 0) continue;
            valToIdx[n] = idxToVal.size();
            idxToVal.push_back(n);
        }
    }

    // group the indices based on xcoor and ycoor, and sorts them (for xSets)
    void collect(vector<int>& xCoors, vector<int>& yCoors) {
        xSets = new vector<int>[idxToVal.size()];
        ySets = new vector<int>[idxToVal.size()];
        
        //  group according to x coor and y coor
        int len = xCoors.size();
        for (int i = 0; i < len; i ++) {
            int xIdx = valToIdx[xCoors[i]];
            int yIdx = valToIdx[yCoors[i]];
            xSets[xIdx].push_back(yIdx);
            ySets[yIdx].push_back(xIdx);
        }
        for (int i = 0; i < idxToVal.size(); i ++) {
            sort(xSets[i].begin(), xSets[i].end());
            sort(ySets[i].begin(), ySets[i].end());
        }
    }

    // returns the 1st elem in arr > key
    int binarySearch(vector<int>& arr, int key) {
        int s = 0;
        int e = arr.size() - 1;
        while (s < e) {
            int m = (s + e) >> 1;
            if (arr[m] > key) e = m;
            else s = m + 1;
        }
        return (arr[s] > key) ? arr[s] : -1;
    } 

    void buildSegTrees() {
        xSegtrees = new Node*[idxToVal.size()] {0};
        Node* curr = nullptr;
        for (int i = 0; i < idxToVal.size(); i ++) {
            vector<int>& arr = xSets[i];
            if (arr.empty()) continue;

            for (int y : arr) {
                curr = Node::insert(curr, 0, idxToVal.size() - 1, y);
            }

            xSegtrees[i] = curr;
        }
    }

    ll getSize(int xIdx, int yIdx1, int yIdx2) {
        int x1 = binarySearch(ySets[yIdx1], xIdx);
        int x2 = binarySearch(ySets[yIdx2], xIdx);
        if (x1 == -1 || x2 == -1 || x1 != x2) return -1;

        // check for points inside, and on the border of x2. We do not nee to get the next prev xIdx from x2
        // as points on line x2 (the border) is also a valid point that we need to check
        int inside = Node::rangeSum(xSegtrees[xIdx], xSegtrees[x2], 0, idxToVal.size() - 1, yIdx1, yIdx2);
        // inside is at least 2, as if we take into account x2, we have 2 points (x2, yIdx1), (x2, yIdx2)
        if (inside > 2) return -1; 

        ll xlen = idxToVal[x2] - idxToVal[xIdx];
        ll ylen = idxToVal[yIdx2] - idxToVal[yIdx1];
        return xlen * ylen;
    }







    long long maxRectangleArea(vector<int>& xCoord, vector<int>& yCoord) {
        vector<int> arr;
        arr.insert(arr.end(), xCoord.begin(), xCoord.end());
        arr.insert(arr.end(), yCoord.begin(), yCoord.end());
        
        compress(arr);
        collect(xCoord, yCoord);
        buildSegTrees();

        ll best = -1;
        for (int xidx = 0; xidx < idxToVal.size(); xidx ++) {
            vector<int>& yidxs = xSets[xidx];
            if (yidxs.size() < 2) continue;

            for (int i = 0; i < yidxs.size() - 1; i ++) {
                int y1 = yidxs[i];
                int y2 = yidxs[i + 1];
                ll res = getSize(xidx, y1, y2);
                best = max(best, res);
            }
        }
        return best;

        delete[] xSets;
        delete[] ySets;
        
        

       

    }
};

/*int main() {
    vector<Node*> arr(10, nullptr);
    arr[0] = Node::insert(nullptr, 0, 9, 0);

    for (int i = 1; i < arr.size(); i ++) {
        arr[i] = Node::insert(arr[i - 1], 0, 9, i);
    }

    cout << Node::rangeSum(nullptr, arr[9], 0, 9, 0, 9) << endl;
    cout << Node::rangeSum(arr[4], arr[9], 0, 9, 0, 4) << endl;
    cout << Node::rangeSum(arr[3], arr[9], 0, 9, 0, 4) << endl;

}*/

int main() {
    Solution sol;
    vector<int> xcoors = {1,1,3,3,2};
    vector<int> ycoors = {1,3,1,3,2};
    cout << sol.maxRectangleArea(xcoors, ycoors);
}