#include <bits/stdc++.h>
using namespace std;

// use suffix array, lcp and dp
// dp(i, len) = how many non-decreasing sequence starting at idx i, and all elems must have length >= len
// dp(i, len) = dp(i, len + 1) + dp(i + len, len or len + 1)
// for the 2nd case to see if it is len or len + 1, we need to use lcp to check starting at idx i + len and taking len digits
// we can get a number greater than or equal to the number we get from starting at idx i and taking len digits
// same as asking if len of longest prefix of suffix i and suffix i + len is >= len
// use lcp and segment tree

struct Pair {
    int idx, r1, r2;
};

void compress(vector<Pair>& pairs) {
    vector<int> compressed(pairs.size(), 1);
    for (int i = 1; i < pairs.size(); i ++) {
        if (pairs[i].r1 == pairs[i - 1].r1 && pairs[i].r2 == pairs[i - 1].r2) {
            compressed[i] = compressed[i - 1];
        } else {
            compressed[i] = compressed[i - 1] + 1;
        }
    }

    for (int i = 0; i < pairs.size(); i ++) pairs[i].r1 = compressed[i];
}

void update(int strlen, int k, vector<Pair>& pairs) {
    vector<int> idxToPos(pairs.size(), 0);
    for (int i = 0; i < pairs.size(); i ++) idxToPos[pairs[i].idx] = i;

    for (Pair& p : pairs) {
        p.r2 = (p.idx + (1 << (k - 1)) >= strlen) ? 0 : pairs[idxToPos[p.idx + (1 << (k - 1))]].r1;
    }
}

vector<int> suffixArray(string& s) {
    auto cmp = [](Pair& p1, Pair& p2) {return p1.r1 < p2.r1 || (p1.r1 == p2.r1 && p1.r2 < p2.r2);};
    vector<Pair> pairs;
    for (int i = 0; i < s.size(); i ++) pairs.push_back({i, s[i], 0});
    sort(pairs.begin(), pairs.end(), cmp);

    int k = 1;
    while (1) {
        compress(pairs);
        update(s.size(), k, pairs);
        sort(pairs.begin(), pairs.end(), cmp);

        if ((1 << k) >= s.size()) break;
        k ++;
    }

    vector<int> out;
    for (Pair& p : pairs) out.push_back(p.idx);
    return out;
}

vector<int> longestCommonPrefix(string& s, vector<int>& sa) {
    vector<int> idxToPos(s.size(), 0);
    for (int i = 0;i < sa.size(); i ++) idxToPos[sa[i]] = i;

    vector<int> out(s.size(), 0);

    int h = 0;
    for (int i = 0; i < s.size(); i ++) {
        int pos = idxToPos[i];
        if (pos == 0) continue;

        int prevIdx = sa[pos - 1];
        int lim = min(s.size() - i, s.size() - prevIdx);
        while (h < lim && s[i + h] == s[prevIdx + h]) h ++;
        out[pos] = h;
        h = max(0, h - 1);
    }
    return out;
}

struct SegTree {
    int sz;
    vector<int> tree;

    SegTree(vector<int>& arr): sz(arr.size()), tree(4 * sz, 0) {
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
        tree[p] = min(tree[(p << 1) + 1], tree[(p << 1) + 2]);
    }

    int rangeMin(int p, int s, int e, int l, int r) {
        if (s == e || (s == l && e == r)) return tree[p];

        int m = (s + e) >> 1;
        if (r <= m) return rangeMin((p << 1) + 1, s, m, l, r);
        else if (l > m) return rangeMin((p << 1) + 2, m + 1, e, l, r);
        else return min(rangeMin((p << 1) + 1, s, m, l, m), rangeMin((p << 1) + 2, m + 1, e, m + 1, r));
    }

};


class Solution {
public:
    int MOD = 1000000007;
    vector<vector<int>> dp;

    int numberOfCombinations(string num) {
        vector<int> sa = suffixArray(num);
        vector<int> lcp = longestCommonPrefix(num, sa);
        SegTree st(lcp);
        vector<int> idxToPos(num.size(), 0);
        dp = vector(num.size(), vector(num.size() + 1, 0));

        for (int i = 0; i < sa.size(); i ++) {
            idxToPos[sa[i]] = i;
        }

        for (int i = num.size() - 1; i >= 0; i --) {
            if (num[i] == '0') continue; // 1st digit is 0, no solution

            dp[i][num.size() - i] = 1; // take everything

            for (int len = num.size() - i - 1; len >= 1; len --) {
                int j = i + len;
                int opt1 = 0;
                int opt2 = dp[i][len + 1];
                
                // no need to check if we can take a prefix of length len from suffix j
                // as if it exceeds, ans is 0 anyway
                // i.e dp(i, len) = 0 if num.size() - i < len

                int posJ = idxToPos[j];
                int posI = idxToPos[i];

                if (posJ > posI || st.rangeMin(0, 0, st.sz - 1, min(posI, posJ) + 1, max(posI, posJ)) >= len) {
                    opt1 = dp[j][len]; // can take because suffix j is lexicographically greater than suffix i
                                       // or prefix of length len starting at j is the same as prefix of length len
                                       // starting at i
                } else {
                    opt1 = dp[j][len + 1]; // take len + 1 digits confirm can
                }

                dp[i][len] = (opt1 + opt2) % MOD;
            }
        }

        int sum = dp[0][1];
       
        
        return sum;
        
    }
};

int main() {
    Solution sol;
    string s = "1234";
    cout << sol.numberOfCombinations(s) << endl;



}



