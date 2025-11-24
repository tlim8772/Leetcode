#include <bits/stdc++.h>
using namespace std;

// problem: given n strings, find the length of longest common substring
// if longest common substring is l
// flatten all the strings into 1 giant string
// then in suffix array, the indices that the substring start from are contained in a contigous range
// where all entries of lcp is >= len
// so e.g. range is [s, e] then lcp[i] >= len s + 1 <= i <= e 
// use 2 pointer to check if there exist common sustring of size l
// then binary search

struct Pair {
    int idx, r1, r2;

    bool operator==(const Pair& p2) {
        return r1 == p2.r1 && r2 == p2.r2;
    }

    bool operator<(const Pair& p2) {
        return r1 < p2.r1 || (r1 == p2.r1 && r2 < p2.r2);
    }
};

class Solution {
public:

int N;
int minLen;
vector<int> whichPart; // for each idx of flattened array, which path did it start from
vector<int> endIdx; // to know the endIdx of the array for this section
vector<int> flattened;

vector<int> sa;
vector<int> lcp;

void processString(vector<vector<int>>& paths) {
    N = paths.size();
    int sz = accumulate(paths.begin(), paths.end(), 0, [](int accu, const vector<int>& arr) {return accu + arr.size();});
    minLen = accumulate(paths.begin(), paths.end(), 
        999999999, [](int accu, const vector<int>& arr) {return min(accu, (int) arr.size());});
    
    whichPart = vector(sz, 0);
    endIdx = vector(sz, 0);

    int sum = 0;
    for (int i = 0; i < paths.size(); i ++) {
        vector<int>& path = paths[i];
        int curr = sum;
        sum += path.size();
        
        for (int j = 0; j < path.size(); j ++) {
            whichPart[curr] = i;
            endIdx[curr] = sum;
            curr ++;
        }
        
        flattened.insert(flattened.end(), path.begin(), path.end());
    }
}

void compress(vector<Pair>& pairs) {
    int len = pairs.size();
    vector<int> compressed(pairs.size(), 1);

    for (int i = 1; i < len; i ++) {
        compressed[i] = (pairs[i] == pairs[i - 1]) ? compressed[i - 1] : compressed[i - 1] + 1;
    }

    for (int i = 0; i < len; i ++) {
        pairs[i].r1 = compressed[i];
    }
}

void updateRanks(int strlen, int k, vector<Pair>& pairs) {
    int len = pairs.size();
    vector<int> idxToPos(pairs.size(), 0);
    for (int i = 0; i < len; i ++) idxToPos[pairs[i].idx] = i;

    for (int i = 0; i < len; i ++) {
        pairs[i].r2 = (pairs[i].idx + (1 << (k - 1)) >= strlen) ? 0 : pairs[idxToPos[pairs[i].idx + (1 << (k - 1))]].r1;
    }
}

vector<int> suffixArray(vector<int>& arr) {
    vector<Pair> pairs;
    for (int i = 0; i < arr.size(); i ++) pairs.push_back({i, arr[i] + 1, 0});
    sort(pairs.begin(), pairs.end());
    
    int k = 1;
    while (1) {
        compress(pairs);
        updateRanks(arr.size(), k, pairs);
        sort(pairs.begin(), pairs.end());

        if ((1 << k) >= arr.size()) break;
        k ++;
    }

    vector<int> out;
    for (Pair& p : pairs) out.push_back(p.idx);

    return out;
}

vector<int> longestCommonPrefix(vector<int>& s, vector<int>& sa) {
    int len = sa.size();
    vector<int> out(s.size(), 0);
    vector<int> idxToPos(s.size(), 0);
    for (int i = 0; i < len; i ++) idxToPos[sa[i]] = i;

    int h = 0;
    for (int i = 0; i < len; i ++) {
        int pos = idxToPos[i];

        if (pos == 0) continue;

        int prevIdx = sa[pos - 1];
        int lim = min(len - i, len - prevIdx);
        while (h < lim && s[i + h] == s[prevIdx + h]) h ++;

        out[pos] = h;
        h = max(0, h - 1);
    }
    return out;
}


bool haveCommonPath(int len) {
    if (len == 0) return true;

    unordered_set<int> set;
    int s = 0;

    
    while (s < lcp.size()) {
        while (s < lcp.size() && lcp[s] < len) s ++;

        int p = s;
        if (endIdx[sa[p - 1]] - sa[p - 1] >= len) set.insert(whichPart[sa[p - 1]]);
        
        while (p < lcp.size() && lcp[p] >= len) {
            if (endIdx[sa[p]] - sa[p] >= len) set.insert(whichPart[sa[p]]);
            p ++;
        }

        if (set.size() >= N) return true;

        set.clear();
        s = p;
    }

    return false;
}



int longestCommonSubpath(int n, vector<vector<int>>& paths) {
    processString(paths);
    sa = suffixArray(flattened);
    lcp = longestCommonPrefix(flattened, sa);

    int s = 0;
    int e = minLen;

    while (s < e) {
        
        // if let say s, e have same parity e.g 3 4 5 6, m must be 5
        int m = ((s + e) >> 1) + 1 - ((e - s + 1) & 1);
        bool haveLen = haveCommonPath(m);

        if (haveLen) s = m;
        else e = m - 1;
    }

    return s;

}

};


int main() {
    vector<vector<int>> paths = {{0},{1},{2}};
    Solution sol;
    cout << sol.longestCommonSubpath(5, paths);
}
































/*int main() {
    vector<vector<int>> paths = {{1,2}, {4,5,6,7}, {1,2,3}};
    processString(paths);

    for (int x : whichPart) cout << x << " "; cout << endl;
    for (int x : endIdx) cout << x << " "; cout << endl;
    for (int x : flattened) cout << x << " "; cout << endl;
}*/


