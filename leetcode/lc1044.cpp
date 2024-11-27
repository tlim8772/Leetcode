#include <bits/stdc++.h>
using namespace std;

// suffix array + lcp
// empty string is the smallest
// invariants
// 1. rank 0 is for empty string, nothing else
// 2. if rank number are equal, means same string

// {start idx, rank 1, rank 2}
// sort in increasing order

vector<vector<vector<int>>> bins(30001, vector<vector<int>>());

void clear() {
    for (vector<vector<int>>& bin : bins) bin.clear();
}

void radixSort(vector<vector<int>>& ranks) {
    clear();

    // sort by rank 2 first then rank 1
    for (vector<int>& rank : ranks) {
        bins[rank[2]].push_back(rank);
    }

    int cnt = ranks.size() - 1;
    for (int i = bins.size() - 1; i >= 0; i --) {
        vector<vector<int>>& bin = bins[i];
        
        // pop from the back
        while (!bin.empty()) {
            ranks[cnt] = bin.back();
            bin.pop_back();
            cnt --;
        }
    }

    // sort by rank 1 now
    for (vector<int>& rank : ranks) {
        bins[rank[1]].push_back(rank);
    }

    cnt = ranks.size() - 1;
    for (int i = bins.size() - 1; i >= 0; i --) {
        vector<vector<int>>& bin = bins[i];

        while (!bin.empty()) {
            ranks[cnt] = bin.back();
            bin.pop_back();
            cnt --;
        }
    }
}

// when n = 10^5, just take the O(nlog^2n) algo, much faster
void radixSort2(vector<vector<int>>& ranks) {
    function<bool(vector<int>&, vector<int>&)> cmp = [] (vector<int>& a, vector<int>& b) {
        return a[1] < b[1] || (a[1] == b[1] && a[2] < b[2]);
    };

    sort(ranks.begin(), ranks.end(), cmp);
}

void compress(vector<vector<int>>& sortedPairs) {
    vector<int> out(sortedPairs.size(), 1);

    for (int i = 1; i < sortedPairs.size(); i ++) {
        if (sortedPairs[i][1] == sortedPairs[i - 1][1] && sortedPairs[i][2] == sortedPairs[i - 1][2]) {
            out[i] = out[i - 1];
        } else {
            out[i] = out[i - 1] + 1;
        }
    }

    for (int i = 0; i < sortedPairs.size(); i ++) {
        sortedPairs[i][1] = out[i];
    }
}

// k : we have the ranks for the prefixes of length 2^(k - 1)
// now we want to build the ranks for prefixes of len 2^(k)
void updateRanks(int strlen, int k, vector<vector<int>>& compressedPairs) {
    vector<int> idxToPos(compressedPairs.size(), 0);
    for (int i = 0; i < compressedPairs.size(); i ++) {
        idxToPos[compressedPairs[i][0]] = i;
    }

    for (vector<int>& pair : compressedPairs) {
        pair[2] = (pair[0] + (1 << (k - 1)) >= strlen) ? 0 : compressedPairs[idxToPos[pair[0] + (1 << (k - 1))]][1];
    }
}

vector<int> suffixArray(string& s) {
    vector<vector<int>> pairs;
    
    // sort with 2^0 char
    for (int i = 0; i < s.size(); i ++) {
        pairs.push_back({i, s[i], 0});
    }
    radixSort2(pairs);

    int k = 1; // sort with 2^k char
    while (1) {
        compress(pairs);
        updateRanks(s.size(), k, pairs);
        radixSort2(pairs);
        
        if ((1 << k) > s.size()) break; // must cover entire string, so break only when we exceed str.size() for the 1st time
        k ++;
    }

    vector<int> out;
    for (vector<int>& p : pairs) {
        out.push_back(p[0]);
    }
    return out;
}

// kasai algorithm
// we want to find lcp for suffix starting at 0 first, it can be e.g at pos 2
// so we start from begin, find lcp 
// for lcp for suffix starting at 1
// notice the result for suffix at 0
// e.g
// prev: 'abcde'
// s[0]: 'abcdefghi'  ---- lcp is 5
// for s[1] it is bcdefghi
// now invariant pf suffix array is that if sa[i] and sa[j] j > i have x common characters
// all strings in sa[k], i <= k <= j also have this x common characters
// so for s[1]: bcdefghi
// we have 'bcde' somewhere above 'bcdefghi'
// even if 'bcde' is not the precediing suffix, we can be sure the preceding suffix has 'bcde'
vector<int> LCP(string& s, vector<int>& sa) {
    vector<int> out(s.size(), 0);

    vector<int> idxToPos(s.size(), 0);
    for (int i = 0; i < sa.size(); i ++) {
        idxToPos[sa[i]] = i;
    }

    int h = 0; // the result of the prev comparison, prev means we want to know lcp for suffix starting at i - 1 
               // pos is somewhere else
    for (int i = 0; i < s.size(); i ++) {
        if (idxToPos[i] == 0) continue; // 0th suffix in sorted array, no need to do anything
        int prev = sa[idxToPos[i] - 1];

        int p = h;
        while (p < min(s.size() - i, s.size() - prev) && s[i + p] == s[prev + p]) p ++;

        out[idxToPos[i]] = p;
        h = max(0, p - 1);
    }

    return out;
}

class Solution {
public:
    string longestDupSubstring(string s) {
        vector<int> sa = suffixArray(s);
        vector<int> lcp = LCP(s, sa);
    
        int idx = 0;
        int best = 0;
        for (int i = 0; i < lcp.size(); i ++) {
            if (lcp[i] > best) {
                idx = sa[i];
                best = lcp[i];
            }
        }
        cout << idx << " " << best << endl;
        return (best == 0) ? "" : s.substr(idx, best);
    }
};


/*int main() {
    string s = "gatagaca";
    vector<int> out = suffixArray(s);
    for (int x : out) cout << x << " ";
    cout << endl;

    vector<int> lca = LCP(s, out);
    for (int x : lca) cout << x << " ";
    cout << endl;

}*/

int main() {
    string s = "xnahfslefuigqaaaaaaaaaaaaa";
    Solution sol;
    cout << sol.longestDupSubstring(s) << endl;
}





