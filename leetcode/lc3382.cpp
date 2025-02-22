#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
    int l = 0, r = 0, sum = 0;
};

// persistent segment tree, to optimise, we store all nodes in an array
// the nullNode (i.e the nullptr) is at idx 0
struct PST {
    int sz;
    int cnt = 1; // arr[0] is the null node
    vector<Node> arr;
    
    PST() {}

    PST(int n): sz(n), arr(1, Node()) {
       
    }

    // returns the idx of the newly created node
    // no need to check for null node, because if it is null node, l,r = 0 (null node again) and sum is 0
    int insert(int curr, int s, int e, int val) {
        if (s == e) {
            arr.resize(cnt + 1);
            arr[cnt].sum = arr[curr].sum + 1;
            cnt ++;
            return cnt - 1;
        }

        int m = (s + e) >> 1;
        int l, r;
        if (val <= m) {
            l = insert(arr[curr].l, s, m, val);
            r = arr[curr].r;
        } else {
            l = arr[curr].l;
            r = insert(arr[curr].r, m + 1, e, val);
        }
        
        arr.resize(cnt + 1);
        arr[cnt].l = l;
        arr[cnt].r = r;
        arr[cnt].sum = arr[l].sum + arr[r].sum;
        cnt ++;
        return cnt - 1;
    }

    int rangeSum(int curr1, int curr2, int s, int e, int l, int r) {
        if (s == e || (s == l && e == r)) {
            return arr[curr2].sum - arr[curr1].sum;
        }

        int m = (s + e) >> 1;
        if (r <= m) {
            return rangeSum(arr[curr1].l, arr[curr2].l, s, m, l, r);
        } else if (l > m) {
            return rangeSum(arr[curr1].r, arr[curr2].r, m + 1, e, l, r);
        } else {
            return rangeSum(arr[curr1].l, arr[curr2].l, s, m, l, m) + rangeSum(arr[curr1].r, arr[curr2].r, m + 1, e, m + 1, r);
        }

    }

    ~PST() {
        //delete[] arr;
    }

    
};

class Solution {
public:

    unordered_map<int, int> valToIdx;
    vector<int> idxToVal;
    vector<int>* xSets; // vector<vector<int>> xSets
    vector<int>* ySets; // vector<vector<int>> ySets
    int* xSegtrees;
    PST pst;


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
        xSegtrees = new int[idxToVal.size()];
        pst = PST(70 * idxToVal.size());
        
        
        int curr = 0;
        for (int i = 0; i < idxToVal.size(); i ++) {
            vector<int>& arr = xSets[i];
            if (arr.empty()) continue;

            for (int y : arr) {
                curr = pst.insert(curr, 0, idxToVal.size() - 1, y);
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
        int inside = pst.rangeSum(xSegtrees[xIdx], xSegtrees[x2], 0, idxToVal.size() - 1, yIdx1, yIdx2);
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

        delete[] xSets;
        delete[] ySets;
        delete[] xSegtrees;

        return best;
    }
};

/*int main() {
    PST pst(100);
    vector<int> arr(10, 0);
    arr[0] = pst.insert(0, 0, 9, 0);
    for (int i = 1; i < 10; i ++) {
        arr[i] = pst.insert(arr[i - 1], 0, 9, i);
    }

    cout << pst.rangeSum(arr[0], arr[9], 0, 9, 0, 9) << endl;
    cout << pst.rangeSum(arr[4], arr[9], 0, 9, 0, 4) << endl;
    cout << pst.rangeSum(arr[3], arr[9], 0, 9, 0, 4) << endl;
}*/

int main() {
    Solution sol;
    vector<int> xcoors = {86,36,94,61,96,41,81,93,26,34,93,91,89,4,2,84,30,70,70,92,93,46,87,13,25,89,27,21,46,1,81,27,56,30,34,51,15,13,86,54,51,27,5,50,28,64,6,30,16,100,72,86,83,65,62,68,68,56,23,49,38,15,98,5,20,38,3,99,60,17,70,64,89,63,80,32,5,32,45,68,75,44,78,72,92,83,7,100,87,54,81,94,58,52,27,38,38,60,67,92,66,11,48,2,68,76,34,80,50,32,35,21,60,8,12,72,92,16,87,87,81,78,95,38,33,99,50,13,82,60,51,8,24,48,30,49,29,44,21,95,82,33,70,89,100,44,46,13,68,3,7,2,32,52,56,4,70,39,92,48,7,62,3,54,74,2,32,96,73,85,70,80,45,32,40,36,1,93,13,54,95,3,54,86,81,71,19,3,76,99,94,70,1,45,29,37,35,81,69,45,11,56,74,66,57,56,76,34,51,4,9,73,10,79,86,82,71,60,82,16,64,88,4,42,26,51,36,39,42,97,91,67,63,53,46,97,37,30,84,24,8,38,65,73,65,43,43,52,8,55,70,58,83,75,61,33,50,61,61,18,20,18,83,99,66,54,70,90,82,57,40,4,54,32,77,47,29,73,100,12,53,14,30,32,89,33,55,96,92,45,43,67,18,6,33,99,28,56,38,27,32,79,9,44,64,87,25,14,49,2,79,9,78,55,85,75,97,89,56,49,48,85,15,27,97,12,9,51,30,93,25,66,23,91,80,87,99,6,53,69,6,76,51,15,33,4,48,18,22,32,90,6,42,83,48,55,27,93,41,1,73,67,72,88,91,85,76,71,96,59,40,91,96,77,3,64,14,69,40,24,33,43,84,83,96,30,68,45,20,79,23,75,40,34,36,5,21,94,67,55,52,54,2,89,57,71,12,24,37,4,96,28,53,45,65,14,86,64,26,54,21,71,27,50,74,72,25,45,17,9,88,85,39,55,18,66,39,39,56,25,46,30,91,17,75,36,19,5,31,72,89,96,32,47,10,32,70,6,26,15,63,27,74,97,88,72,34,53,81,75,65,79,44,98,28,3,6,57,91,85,96,53,89,43,71,22,60,52,76,65,35,11,7,71,6,16,94,45,23,35,81,6,65,51,95,34,36,6,7,40,66,50,80,20,57,52,59,29,34,86,10,11,84,46,73,100,25,61,97,32,51,71,42,42,23,71,64,72,1,41,44,91,65,47,26,28,53,42,79,82,55,3,55,89,65,88,63,43,22,32,67,78,43,2,19,18,100,58,4,90,79,2,8,47,56,47,55,99,21,22,3,72,68,63,35,84,51,94,26,54,66,49,64,39,61,98,90,84,28,48,40,82,9,40,87,7,38,5,19,7,99,89,38,74,55,67,8,6,75,9,21,12,98,11,84,35,11,62,95,95,41,7,65,34,50,85,41,5,15,29,10,84,43,41,85,28,99,71,8,19,86,54,80,88,61,30,6,88,60,22,90,94,46,92,90,7,40,49,13,49,20,90,30,80,16,65,54,100,11,26,35,43,6,36,30,55,29,35,10,7,96,24,82,87,94,28,98,39,99,99,98,40,87,72,46,90,41,45,22,47,66,40,22,21,16,56,82,10,90,7,10,95,67,62,66,89,43,99,88,97,36,7,31,4,69,54,88,46,78,33,10,65,11,1,97,57,36,97,41,57,38,30,26,32,41,60,87,65,10,56};
    vector<int> ycoors = {80,56,76,12,28,10,19,9,67,79,57,27,38,72,2,8,58,75,74,53,59,38,55,18,25,22,100,75,12,19,35,99,5,36,88,11,76,69,96,90,77,17,32,38,56,64,13,40,2,36,21,76,11,55,67,8,66,69,72,14,87,42,10,81,9,43,68,75,43,59,59,22,58,73,59,44,3,83,56,57,98,90,26,87,47,80,58,4,21,23,86,17,21,91,34,25,49,84,9,12,48,54,87,41,16,11,82,22,85,6,47,65,25,30,94,36,89,77,62,87,75,47,89,34,61,26,37,70,66,7,46,12,49,77,3,6,39,94,44,29,73,48,30,83,34,69,71,88,91,4,13,49,24,87,100,69,2,30,67,67,2,38,60,59,45,28,27,67,35,54,84,8,14,35,93,53,14,96,78,32,74,34,14,9,97,28,43,58,45,17,70,79,6,6,97,78,49,12,95,13,81,65,34,98,100,53,31,31,31,8,98,76,62,62,29,53,15,61,4,79,33,57,79,38,91,3,91,40,19,8,42,51,18,19,8,70,33,97,14,32,5,23,50,10,58,89,96,32,69,23,12,93,2,87,87,87,70,37,62,51,28,16,52,18,51,13,83,37,83,46,79,61,77,28,58,39,100,47,81,40,64,7,15,64,11,51,12,73,66,19,30,28,85,15,39,22,39,3,18,56,96,64,36,65,34,22,56,23,66,11,25,47,91,20,83,70,31,94,1,7,36,86,3,91,72,100,61,94,39,38,33,24,56,83,67,78,52,16,13,36,20,41,58,49,89,98,57,97,63,26,100,48,75,4,73,71,69,98,83,51,52,66,5,91,12,81,73,21,94,38,3,55,17,81,30,51,63,61,12,44,31,55,71,41,59,60,85,29,63,68,80,36,62,45,2,54,29,96,89,66,28,51,68,5,93,92,60,97,88,4,21,95,53,86,47,22,88,62,3,65,50,81,26,96,11,25,21,53,49,92,12,25,71,41,79,57,58,53,14,9,79,90,32,35,21,39,1,34,78,13,55,6,29,64,88,57,29,47,58,64,25,66,79,48,45,91,59,3,15,100,77,61,74,77,5,46,73,19,71,37,84,32,75,92,19,47,3,12,24,26,57,74,96,51,60,57,42,41,84,23,84,100,40,52,13,50,92,18,1,99,45,51,29,64,77,72,64,6,23,78,4,55,22,87,54,52,71,60,69,25,13,63,8,78,99,34,4,92,83,65,63,56,43,28,84,73,33,49,70,26,67,97,42,72,18,32,13,9,69,2,29,93,61,66,83,87,50,24,56,3,96,80,76,52,26,61,94,32,22,68,38,80,18,23,91,65,17,89,34,86,54,24,16,26,40,32,17,21,62,2,64,42,29,23,65,62,6,48,58,44,68,40,62,25,59,99,40,74,49,90,11,77,58,20,75,73,92,4,17,73,92,23,80,57,71,89,45,87,85,99,92,16,87,18,39,27,81,62,23,70,5,92,33,99,14,72,35,49,11,5,45,22,3,98,96,18,71,96,95,44,81,19,31,75,9,38,89,80,27,45,50,29,75,60,24,13,56,74,87,29,40,39,59,66,35,7,26,19,95,91,53,18,81,48,6,5,57,83,49,2,73,82,22,46,50,61,55,71,50,11,95,57,7,89,33,69,24,87,24,59,4,66,73,16,92,40,67,59,49,78,74,70,85,54,92,51,13,35,86,60,11,81,56,87,97,60,99,15,34,67};
    cout << sol.maxRectangleArea(xcoors, ycoors);
}