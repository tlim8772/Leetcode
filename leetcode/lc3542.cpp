#include <bits/stdc++.h>
using namespace std;

// there exists a optimal (min number of op) that wipes out the smallest elems,
// then the next smallest elems and so on
// proof: suppose not, the 1st op does not wipe the smallest elem. The smallest elem is wiped
// in an op somewhere else
// in the 1st op range, there is no elem with the smallest val, so we can bring the op that wipes the
// smallest elem right to the front, and it will not affect this op

// use segment tree to query whether [l, r] has a 0 i.e store a 1 when an elem becomes 0, then use sum query

struct SegTree {
    int len;
    vector<int> tree;

    SegTree() {}

    SegTree(int len): len(len), tree(4 * len, 0) {}

    void insert(int p, int s, int e, int i, int v) {
        if (s == e) {
            tree[p] = v;
            return;
        }

        int m = (s + e) >> 1;
        if (i <= m) {
            insert((p << 1) + 1, s, m, i, v);
        } else {
            insert((p << 1) + 2, m + 1, e, i, v);
        }
        tree[p] = tree[(p << 1) + 1] + tree[(p << 1) + 2];
    }   

    int query(int p, int s, int e, int l, int r) {
        if (s == e || (s == l && e == r)) {
            return tree[p];
        }

        int m = (s + e) >> 1;
        if (r <= m) {
            return query((p << 1) + 1, s, m, l, r);
        } else if (l > m) {
            return query((p << 1) + 2, m + 1, e, l, r);
        } else {
            return query((p << 1) + 1, s, m, l, m) + query((p << 1) + 2, m + 1, e, m + 1, r); 
        }
    }
};

class Solution {
public:
    set<int> ints;
    unordered_map<int, vector<int>> intPos;
    SegTree st;

    void process(vector<int>& nums) {
        ints = set(nums.begin(), nums.end());

        for (int i = 0; i < nums.size(); i++) {
            intPos[nums[i]].push_back(i);
        }
    }
    
    int minOperations(vector<int>& nums) {
        st = SegTree(nums.size());
        
        process(nums);

        int cnt = 0;
        auto ptr = ints.begin();
        
        int smallest = *ptr;
        
        for (int i : intPos[smallest]) {
            st.insert(0, 0, st.len - 1, i, 1);
        }
        if (smallest != 0) cnt++;
        
        ptr++;

        while (ptr != ints.end()) {
            vector<int>& positions = intPos[*ptr];
            int curr = 0;

            for (int i = 0; i < positions.size(); i++) {
                int haveZero = st.query(0, 0, st.len - 1, positions[curr], positions[i]);
                if (haveZero) {
                    curr = i;
                    cnt++;
                }
            }
            // for last range
            cnt++;
            
            // mark all positions as 0
            for (int x : positions) st.insert(0, 0, st.len - 1, x, 1);
            
            ptr++;
        }
        
        return cnt;
    }
};

int main() {
    Solution sol;

    vector<int> arr = {1,2,1,2,1};

    cout << sol.minOperations(arr) << endl;
}