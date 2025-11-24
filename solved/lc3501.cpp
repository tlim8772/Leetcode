#include <bits/stdc++.h>
using namespace std;

// segment tree
// only need care about the consecutive 1
// in 1 op we can add prev 0 arr length and next 0 arr length val to the total number of 1s
// when we restrict to [l, r], we only need to modify the 1's val at the 'edge'
// just need to carefully consider all cases

struct SegTree {
    int len;
    vector<int> tree;

    SegTree() {}

    SegTree(int len): len(len), tree(4 * len, 0) {}
    
    void add(int p, int s, int e, int i, int v) {
        if (s == e) {
            tree[p] += v;
            return;
        }

        int m = (s + e) >> 1;
        if (i <= m) {
            add((p << 1) + 1, s, m, i, v);
        } else { 
            add((p << 1) + 2, m + 1, e, i, v);
        }
        tree[p] = max(tree[(p << 1) + 1], tree[(p << 1) + 2]);
    }

    void set(int p, int s, int e, int i, int v) {
        if (s == e) {
            tree[p] = v;
            return;
        }

        int m = (s + e) >> 1;
        if (i <= m) {
            set((p << 1) + 1, s, m, i, v);
        } else { 
            set((p << 1) + 2, m + 1, e, i, v);
        }
        tree[p] = max(tree[(p << 1) + 1], tree[(p << 1) + 2]);
    }

    int getMax(int p, int s, int e, int l, int r) {
        if (s == e || (s == l && e == r)) {
            return tree[p];
        }

        int m = (s + e) >> 1;
        if (r <= m) {
            return getMax((p << 1) + 1, s, m, l, r);
        } else if (l > m) {
            return getMax((p << 1) + 2, m + 1, e, l, r);
        } else {
            return max(getMax((p << 1) + 1, s, m, l, m), getMax((p << 1) + 2, m + 1, e, m + 1, r));
        }
    } 

};

// a is what num (0 or 1), b is count, s is start, e is end
struct P2 {
    int a, b, s, e;
};


class Solution {
public:
    SegTree st;
    vector<P2> groups;
    vector<int> myGroup;
    vector<int> myVal;

    void group(string& s) {
        
        myGroup = vector<int>(s.size(), 0);

        int p = 0, cnt = 0;
        char c = s[0];
        while (p < s.size()) {
            if (s[p] == c) {
                myGroup[p] = groups.size();
                p ++;
                cnt ++;
            } else {
                groups.push_back({c - '0', cnt, p - cnt, p - 1});
                c = s[p];
                cnt = 1;
                
                myGroup[p] = groups.size();
                p ++;
            }
        }
        groups.push_back({c - '0', cnt, p - cnt, p - 1});
    }

    void process(string& s) {
        group(s);
        st = SegTree(groups.size());

        for (int i = 0; i < groups.size(); i ++) {
            P2& p = groups[i];
            if (p.a == 0) {
                st.add(0, 0, st.len - 1, i, 0);
                myVal.push_back(0);
            } else {
                int sum = (i != 0 && i != groups.size() - 1) ? groups[i - 1].b + groups[i + 1].b : 0;
                myVal.push_back(sum);
                st.add(0, 0, st.len - 1, i, sum);
            }
        }
    }

    int query(int l, int r) {
        int gl = myGroup[l];
        int gr = myGroup[r];

        if (groups[gl].a == 1) {
            // case 1: l is in a 1-group, then we have to zero this 1-group
            st.set(0, 0, st.len - 1, gl, 0);
        } else if (gl < groups.size() - 1) {
            // case 2: l is in a 0-group, then we hav to adjust the val of the right 1-group
            int toMinus = l - groups[gl].s;
            st.add(0, 0, st.len - 1, gl + 1, -toMinus);
        }

        
        if (groups[gr].a == 1) {
            st.set(0, 0, st.len - 1, gr, 0);
        } else if (gr > 0) {
            if (gr == gl + 1) { 

            } else {
                int toMinus = groups[gr].e - r;
                st.add(0, 0, st.len - 1, gr - 1, -toMinus);
            }
        }

        int ans = st.getMax(0, 0, st.len - 1, gl, gr);

        if (groups[gl].a == 1) {
            // case 1: l is in a 1-group, then we have to reset to original val
            st.set(0, 0, st.len - 1, gl, myVal[gl]);
        } else if (gl < groups.size() - 1) {
            // case 2: l is in a 0-group, then we have to add back the val we substracted
            int toMinus = l - groups[gl].s;
            st.add(0, 0, st.len - 1, gl + 1, toMinus);
        }

        if (groups[gr].a == 1) {
            st.set(0, 0, st.len - 1, gr, myVal[gr]);
        } else if (gr > 0) {
            if (gr == gl + 1) {

            } else {
                int toMinus = groups[gr].e - r;
                st.add(0, 0, st.len - 1, gr - 1, toMinus);
            }
        }

        return ans;


    }


    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        process(s);
        int sum1 = 0;
        for (char c : s) sum1 += c - '0';

        for (P2 p : groups) printf("%d %d %d %d\n", p.a, p.b, p.s, p.e);

        vector<int> ans;
        for (vector<int>& q : queries) {
            int res = query(q[0], q[1]);
            ans.push_back(sum1 + res);
        }
        return ans;
    }
};



int main() {
    Solution sol;

    string s = "001000";
    vector<vector<int>> queries = {{2,4},{1,3}};
    vector<int> ans = sol.maxActiveSectionsAfterTrade(s, queries);

    for (int x : ans) cout << x << endl;

}